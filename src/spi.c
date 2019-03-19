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

#include "peripherals.h"

uint32_t *
spi_map(void)
{
    spi_base_ptr = (volatile uint32_t *)peripheral_map(PERIPHERAL_BASE +
        SPI_OFFSET, SPI_SIZE);

    return (uint32_t *)spi_base_ptr;
}

void
spi_unmap(void)
{
    peripheral_unmap((uint32_t *)spi_base_ptr, SPI_SIZE);
}

void
spi_configure(spi_channel_config_t *config)
{
    SPI->CS = config->cs_register;
    SPI->CLK = config->divisor;
}

inline void
spi_transfer_start(void)
{
    SPI->CS |= 0x80; /* set TA */
}

inline void
spi_transfer_stop(void)
{
    while(!(SPI->CS & 0x10000)) {} /* wait for DONE */
    SPI->CS &= ~0x80; /* clear TA */
}

inline uint8_t
spi_transfer_byte(uint8_t data)
{
    SPI->CS |= 0x30; /* Clear FIFO */
    SPI->FIFO = data;
    while(!(SPI->CS & 0x20000)) {} /* wait for data in RX FIFO */
    return (uint8_t) SPI->FIFO;
}

/* send 2 bytes and return the data from the last transmission */
inline uint8_t
spi_send2_recv1(uint8_t data0, uint8_t data1)
{
    spi_transfer_start();
    spi_transfer_byte(data0);
    uint8_t ret = spi_transfer_byte(data1);
    spi_transfer_stop();
    return ret;
}
