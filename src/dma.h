/*
 * dma.h
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

#ifndef _DMA_H_
#define _DMA_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#define	PERIPHERAL_BASE_PHY	0x7E000000

#define DMA_OFFSET	0x007000 // TODO: add channel 15
#define DMA_SIZE	0xff4

volatile uint32_t *dma_base_ptr;

struct dma_channel_register_map {
    uint32_t CS;
    uint32_t CONBLK_AD;
    uint32_t TI;
    uint32_t SOURCE_AD;
    uint32_t DEST_AD;
    uint32_t TXFR_LEN;
    uint32_t STRIDE;
    uint32_t NEXTCONBK;
    uint32_t DEBUG;
};
#define DMA_0   ((volatile struct dma_channel_register_map *)dma_base_ptr)
#define DMA_1   ((volatile struct dma_channel_register_map *)(dma_base_ptr + 0x40))
#define DMA_2   ((volatile struct dma_channel_register_map *)(dma_base_ptr + 0x80))
#define DMA_3   ((volatile struct dma_channel_register_map *)(dma_base_ptr + 0xc0))
#define DMA_4   ((volatile struct dma_channel_register_map *)(dma_base_ptr + 0x100))
#define DMA_5   ((volatile struct dma_channel_register_map *)(dma_base_ptr + 0x140))
#define DMA_6   ((volatile struct dma_channel_register_map *)(dma_base_ptr + 0x180))
#define DMA_7   ((volatile struct dma_channel_register_map *)(dma_base_ptr + 0x1c0))
#define DMA_8   ((volatile struct dma_channel_register_map *)(dma_base_ptr + 0x200))
#define DMA_9   ((volatile struct dma_channel_register_map *)(dma_base_ptr + 0x240))
#define DMA_10  ((volatile struct dma_channel_register_map *)(dma_base_ptr + 0x280))
#define DMA_11  ((volatile struct dma_channel_register_map *)(dma_base_ptr + 0x2c0))
#define DMA_12  ((volatile struct dma_channel_register_map *)(dma_base_ptr + 0x300))
#define DMA_13  ((volatile struct dma_channel_register_map *)(dma_base_ptr + 0x340))
#define DMA_14  ((volatile struct dma_channel_register_map *)(dma_base_ptr + 0x380))

struct dma_register_map {
    uint32_t INT_STATUS;
    uint32_t: 32;
    uint32_t: 32;
    uint32_t: 32;
    uint32_t ENABLE;
};
#define DMA     ((struct dma_register_map *)(dma_base_ptr + 0x3f8))

typedef struct {
    uint32_t TI;
    uint32_t SOURCE_AD;
    uint32_t DEST_AD;
    uint32_t TXFR_LEN;
    uint32_t STRIDE;
    uint32_t NEXTCONBK;
    uint32_t: 32; // not needed?
    uint32_t: 32;
} dma_cb_t;

typedef struct {
    uint32_t handle;
    uint32_t bus_addr;
    void *mem;
    unsigned int size;
} dma_phy_mem_blk_t;

typedef struct {
    struct dma_channel_register_map *channel;
    union {
        struct {
            uint32_t DISDEBUG: 1;
            uint32_t WTOUTWRT: 1; // wait for outstanding writes
            uint32_t: 4; // reserved
            uint32_t PANIC_PRIORITY: 4;
            uint32_t PRIOTITY: 4;
        };
        uint32_t cs_register;
    };
} dma_channel_config_t;

uint32_t *  dma_map(void);
void        dma_unmap(void);

void    dma_configure(dma_channel_config_t *config);
void    dma_enable(volatile struct dma_channel_register_map *channel);
void    dma_disable(volatile struct dma_channel_register_map *channel);

uint32_t dma_virt_to_phy(dma_phy_mem_blk_t *block, void *addr);

void dma_alloc_phy_mem(dma_phy_mem_blk_t *block, unsigned int size);
void dma_free_phy_mem(dma_phy_mem_blk_t *block);

int _mbox_fd;

#ifdef  __cplusplus
}
#endif//__cplusplus

#endif//_DMA_H_
