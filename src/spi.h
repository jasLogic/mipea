/*
 * spi.h
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

#ifndef SPI_H
#define SPI_H

#include <stdint.h>

volatile uint32_t *spi_base_pointer;

typedef enum chip_select {
    CE0, CE1, CE2
} chip_select;

typedef struct spi_channel_config {
    uint32_t cs:2;
    uint32_t cpha:1;
    uint32_t cpol:1;
    uint32_t cspol:1;   // Not changing anything?
    uint32_t cspol0:1;
    uint32_t cspol1:1;
    uint32_t cspol2:1;

    uint16_t divisor;
} spi_channel_config;

uint32_t *spi_map(void);
void spi_unmap(void);

void spi_configure(spi_channel_config *config);

extern void spi_transfer_start(void);
extern void spi_transfer_stop(void);
extern uint8_t spi_transfer_byte(uint8_t data);

extern uint8_t spi_send2_recv1(uint8_t data0, uint8_t data1);

/* ----- SPI Registers ----- */
#define SPI_BASE		0x20204000
#define SPI_BLOCK_SIZE	0x14

#define CS      *spi_base_pointer
#define FIFO    *(spi_base_pointer + 1)
#define CLK     *(spi_base_pointer + 2)
#define DLEN    *(spi_base_pointer + 3)
#define LTOH    *(spi_base_pointer + 4)
#define DC      *(spi_base_pointer + 5)

#endif//SPI_H
