/*
 * dma.c
 * Copyright (C) 2018  jasLogic
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "dma.h"

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#include "peripherals.h"
#include "mailbox_mod.h"

uint32_t *
dma_map(void)
{
    if (!peripheral_ismapped((uint32_t *)dma_base_ptr, DMA_SIZE)) {
        // open /dev/vcio which is used in mailbox
        __mbox_fd = mbox_open();
        if (__mbox_fd < 0) {
            return NULL;
        }

        dma_base_ptr = (volatile uint32_t *)peripheral_map(PERIPHERAL_BASE +
            DMA_OFFSET, DMA_SIZE);
    }
    return (uint32_t *)dma_base_ptr;
}
void
dma_unmap(void)
{
    peripheral_unmap((uint32_t *)dma_base_ptr, DMA_SIZE);
    mbox_close(__mbox_fd); // close it again too
}

void
dma_configure(dma_channel_config_t *config)
{
    config->channel->CS = config->cs_register << 16;
}
void
dma_enable(struct dma_channel_register_map *channel)
{
    channel->CS |= 1;
}
void
dma_disable(struct dma_channel_register_map *channel)
{
    channel->CS &= ~1;
}

uint32_t
dma_virt_to_phy(dma_phy_mem_blk_t *block, void *addr)
{
    unsigned int offset = (uint8_t *)addr - (uint8_t *)block->mem;
	return block->bus_addr + offset;
}

void
dma_alloc_phy_mem(dma_phy_mem_blk_t *block, unsigned int size)
{
    block->size = (size / PAGE_SIZE + 1) * 4096; // round to 4096
    block->handle = mbox_alloc(__mbox_fd, block->size, PAGE_SIZE,
        MEM_FLAG_L1_NONALLOCATING | MEM_FLAG_ZERO);
    block->bus_addr = mbox_lock(__mbox_fd, block->handle);
    block->mem = mbox_map(BUS_TO_PHYS(block->bus_addr), block->size);
}

void
dma_free_phy_mem(dma_phy_mem_blk_t *block)
{
    mbox_unmap(block->mem, block->size);
    mbox_unlock(__mbox_fd, block->handle);
    mbox_free(__mbox_fd, block->handle);
    block->mem = NULL;
}
