/*
 * clock_manager.h
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

#ifndef _CLOCK_MANAGER_H_
#define _CLOCK_MANAGER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define CLOCK_MANAGER_OFFSET        0x101000
#define CLOCK_MANAGER_BLOCK_SIZE    0xA4

#define CM_PASSWD    0x5A000000

volatile uint32_t *clock_manager_base_ptr;

struct clock_manager_register_map {
    uint32_t GP0CTL;
    uint32_t GP0DIV;
    uint32_t GP1CTL;
    uint32_t GP1DIV;
    uint32_t GP2CTL;
    uint32_t GP2DIV;
    uint32_t: 32;
    uint32_t: 32;
    uint32_t: 32;
    uint32_t: 32;
    uint32_t PCMCTL;
    uint32_t PCMDIV;
    uint32_t PWMCTL;
    uint32_t PWMDIV;
};
#define CM  ((struct clock_manager_register_map *)(clock_manager_base_ptr + 28))

typedef enum {
    CLOCK_GND,
    CLOCK_OSC,
    CLOCK_TST0,
    CLOCK_TST1,
    CLOCK_PLLA,
    CLOCK_PLLC,
    CLOCK_PLLD,
    CLOCK_HDMI
} clock_source_t;

uint32_t *  clock_map(void);
void        clock_unmap(void);

void clock_enable(volatile uint32_t *reg);
void clock_disable(volatile uint32_t *reg);
void clock_configure(volatile uint32_t *reg, clock_source_t src,
                    unsigned int divisor, unsigned int mash);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CLOCK_MANAGER_H_ */
