#ifndef SPI_H
#define SPI_H

#include <stdint.h>

volatile uint32_t *spi_base_pointer;

uint32_t *spi_map(void);
void spi_unmap(void);

/* ----- SPI Registers ----- */
#define CS      *spi_base_pointer
#define FIFO    *(spi_base_pointer + 1)
#define CLK     *(spi_base_pointer + 2)
#define DLEN    *(spi_base_pointer + 3)
#define LTOH    *(spi_base_pointer + 4)
#define DC      *(spi_base_pointer + 5)

#endif//SPI_H
