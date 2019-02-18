/*
 * timer.h
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

#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define TIMER_OFFSET        0x003000
#define TIMER_BLOCK_SIZE    0x1C

volatile uint32_t *timer_base_ptr;

struct timer_register_map {
    uint32_t CS;
    uint32_t CLO;
    uint32_t CHI;
    uint32_t C0;
    uint32_t C1;
    uint32_t C2;
    uint32_t C3;
};
#define TIMER     ((struct timer_register_map *)timer_base_ptr)

uint32_t *  timer_map(void);
void        timer_unmap(void);

extern void timer_read(uint64_t *counter);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TIMER_H_ */
