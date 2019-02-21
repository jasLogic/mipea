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

#include "peripherals.h"

uint32_t *
dma_map(void)
{
    dma_peripheral = (peripheral_t) {PERIPHERAL_BASE + DMA_OFFSET,
                                        DMA_BLOCK_SIZE, 0, NULL};

    if (peripheral_map(&dma_peripheral) == NULL) {
		return NULL;
	}
	dma_base_ptr = (volatile uint32_t *)dma_peripheral.map;
	return (uint32_t *)dma_base_ptr;
}

void
dma_unmap(void)
{
    peripheral_unmap(&dma_peripheral);
}
