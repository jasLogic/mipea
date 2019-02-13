/*
 * peripherals.h
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

#ifndef _PERIPHERALS_H
#define _PERIPHERALS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct {
	unsigned long v_addr;
	unsigned int block_size;
	int mem_fd;
	void *map;
} peripheral_t;

uint32_t *	peripheral_map(peripheral_t *per);
void 		peripheral_unmap(peripheral_t *per);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PERIPHERALS_H */
