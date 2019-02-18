/*
 * timer.c
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

#include "timer.h"

#include <stdint.h>
#include <stddef.h>

#include "peripherals.h"

static peripheral_t timer_peripheral = {PERIPHERAL_BASE + TIMER_OFFSET,
                                        TIMER_BLOCK_SIZE, 0, NULL};

uint32_t *
timer_map(void)
{
    if (peripheral_map(&timer_peripheral) == NULL) {
		return NULL;
	}
	timer_base_ptr = (volatile uint32_t *)timer_peripheral.map;
	return (uint32_t *)timer_base_ptr;
}

void
timer_unmap(void)
{
    peripheral_unmap(&timer_peripheral);
}

inline void
timer_read(uint64_t *counter)
{
    *counter = TIMER->CHI;
    *counter = *counter << 32;
    *counter |= TIMER->CLO;
}
