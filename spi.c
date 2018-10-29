#include "spi.h"

#include <stdint.h>
#include <stddef.h>

#include "bcm2835_peripherals.h"

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

    while(!(CS & 0x10000)) {} // wait for DONE
    return FIFO;
}


inline uint8_t spi_send2_recv1(uint8_t data0, uint8_t data1) { // dirty
    uint8_t ret = 0;

    CS |= (3 << 4); // Clear FIFO

    CS |= 0x80; // set TA

    while(!(CS & 0x40000)) {} // wait for space in TX FIFO
    FIFO = data0;
    while(!(CS & 0x40000)) {} // wait for space in TX FIFO
    FIFO = 85; // garbage, don't care

    while(!(CS & 0x10000)) {} // wait for DONE

    while (CS & 0x20000) {
        ret = FIFO;
    }

    CS &= ~0x80; // clear TA

    return ret;
}
