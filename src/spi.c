/*
 * spi.c
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

#include "spi.h"

#include <stdint.h>
#include <stddef.h>

#include "core/bcm2835_peripherals.h"

peripheral spi_peripheral = {SPI_BASE, SPI_BLOCK_SIZE, 0, NULL};

uint32_t *spi_map(void) {
    if (peripheral_map(&spi_peripheral) == NULL) {
		return NULL;
	}
	spi_base_pointer = (volatile uint32_t *)spi_peripheral.map;
	return (uint32_t *)spi_base_pointer;
}

void spi_unmap(void) {
    peripheral_unmap(&spi_peripheral);
}

void spi_configure(spi_channel_config *config) {
    CS &= 0b11; // Clear lowest 2 bits
    CS |= config->cs;

    if (config->cpha) {
        CS |= 0x4;
    }
    if (config->cpol) {
        CS |= 0x8;
    }
    if (config->cspol) {
        CS |= 0x40;
    }
    if (config->cspol0) {
        CS |= 0x800000;
    }
    if (config->cspol1) {
        CS |= 0x400000;
    }
    if (config->cspol2) {
        CS |= 0x200000;
    }

    CLK = config->divisor;
}

inline void spi_transfer_start(void) {
    CS |= 0x80; // set TA
}
inline void spi_transfer_stop(void) {
    while(!(CS & 0x10000)) {} // wait for DONE
    CS &= ~0x80; // clear TA
}
inline uint8_t spi_transfer_byte(uint8_t data) {
    CS |= 0x30; // Clear FIFO

    while(!(CS & 0x40000)) {} // wait for space in TX FIFO
    FIFO = data;

    while(!(CS & 0x20000)) {} // wait for data in RX FIFO
    return (uint8_t) FIFO;
}


inline uint8_t spi_send2_recv1(uint8_t data0, uint8_t data1) { // send 2 bytes and return the data from the last transmission
    uint8_t ret;

    CS |= 0x80; // set TA
    CS |= 0x30; // Clear FIFO

    while(!(CS & 0x40000)) {} // wait for space in TX FIFO
    FIFO = data0;
    while(!(CS & 0x40000)) {} // wait for space in TX FIFO
    FIFO = data1;

    while(!(CS & 0x10000)) {} // wait for DONE
    while(CS & 0x20000) { // Read data from FIFO till the last byte arrives
        ret = FIFO;
    }

    CS &= ~0x80; // clear TA

    return ret;
}
