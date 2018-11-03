/*
 * clock.h
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

#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>

volatile uint32_t *clock_base_pointer;

#define CM_PASSWD    0x5A000000

typedef enum clock_source {
    CLOCK_GND, CLOCK_OSC, CLOCK_TST0, CLOCK_TST1, CLOCK_PLLA, CLOCK_PLLC, CLOCK_PLLD, CLOCK_HDMI
} clock_source;

uint32_t *clock_map(void);
void clock_unmap(void);

void clock_enable(volatile uint32_t *reg);
void clock_disable(volatile uint32_t *reg);
void clock_configure(volatile uint32_t *reg, clock_source src, unsigned int divisor, unsigned int mash);

/* ----- CLOCK Registers ----- */
#define CM_GP0CTL   *(clock_base_pointer + 28)
#define CM_GP0DIV   *(clock_base_pointer + 29)
#define CM_GP1CTL   *(clock_base_pointer + 30)
#define CM_GP1DIV   *(clock_base_pointer + 31)
#define CM_GP2CTL   *(clock_base_pointer + 32)
#define CM_GP3DIV   *(clock_base_pointer + 33)

#define CM_PCMCTL   *(clock_base_pointer + 38)
#define CM_PCMDIV   *(clock_base_pointer + 39)

#define CM_PWMCTL   *(clock_base_pointer + 40)
#define CM_PWMDIV   *(clock_base_pointer + 41)

#endif//CLOCK_H
