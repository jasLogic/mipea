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

#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

int peripheral_map(volatile uint32_t **map, uint32_t offset, uint32_t size);
void peripheral_unmap(volatile uint32_t *map, uint32_t size);

int peripheral_ismapped(volatile uint32_t *map, uint32_t size);

#ifdef __cplusplus
}
#endif//__cplusplus

#endif//_PERIPHERALS_H_
