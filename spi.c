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
