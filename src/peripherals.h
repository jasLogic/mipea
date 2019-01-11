/*
 * bcm2835_peripherals.h
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

#ifndef BCM2835_REGISTERS_H
#define BCM2835_REGISTERS_H

#include <stdint.h>

#define PERIPHERAL_BASE	0x20000000

typedef struct peripheral {
	unsigned long v_addr;
	unsigned int block_size;
	int mem_fd;
	void *map;
} peripheral;

uint32_t *peripheral_map(peripheral *per);
void peripheral_unmap(peripheral *per);

#define GPIO_BASE		(PERIPHERAL_BASE + 0x200000)
#define GPIO_BLOCK_SIZE	0xB0

#define PWM_BASE		(PERIPHERAL_BASE + 0x20C000)
#define PWM_BLOCK_SIZE	0x24

#define CLOCK_BASE			(PERIPHERAL_BASE + 0x101000)
#define CLOCK_BLOCK_SIZE	0xA4

#define SPI_BASE		(PERIPHERAL_BASE + 0x204000)
#define SPI_BLOCK_SIZE	0x14

#endif//BCM2835_REGISTERS_H
