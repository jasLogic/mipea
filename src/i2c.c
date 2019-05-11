#include "i2c.h"

#include <stdint.h>

#include "peripherals.h"

uint32_t *
i2c_map(void)
{
    if (!peripheral_ismapped((void *)i2c_base_ptr, I2C_SIZE)) {
        i2c_base_ptr = (volatile uint32_t *) peripheral_map(PERIPHERAL_BASE +
            I2C_OFFSET, I2C_SIZE);
    }
	return (uint32_t *)i2c_base_ptr;
}

void
i2c_unmap(void)
{
    peripheral_unmap((void *)i2c_base_ptr, I2C_SIZE);
}

void
i2c_configure(i2c_config_t *config)
{
    I2C->A = config->addr;
    I2C->DIV = config->div;
}

void
i2c_start(void)
{
    I2C->C |= 0x10 | 0x8000; // clear fifo, enable bsc controller
    I2C->S = 0x50; // reset flag register
}
void
i2c_stop(void)
{
    while(!(I2C->S & 0x2)); // wait for last transmission to be completed
    I2C->C &= ~0x8000; // disable bsc controller
}

inline void
i2c_write_byte(uint8_t byte)
{
    I2C->DLEN = 1; // one byte transfer
    I2C->S |= 0x02; // clear done flag -> if???
    I2C->C |= 0x10; // clear fifo
    I2C->C &= ~0x01; // clear read bit -> write

    I2C->FIFO = byte;
    I2C->C |= 0x80; // start transfer

    while(!(I2C->S & 0x02)); // wait for done
    I2C->S |= 0x02; // clear done flag
}

inline uint8_t
i2c_read_byte(void)
{
    I2C->DLEN = 1; // one byte transfer
    I2C->S |= 0x02; // clear done flag -> if???
    I2C->C |= 0x01 | 0x10; // set read bit, clear FIFO

    I2C->C |= 0x80; // start transfer
    while(!(I2C->S & 0x02)); // wait for done
    I2C->S |= 0x02; // clear done flag

    return I2C->FIFO;
}

inline void
i2c_write_data(const uint8_t *data, uint16_t length)
{
    uint16_t i;

    I2C->DLEN = length;
    I2C->S |= 0x02; // clear done flag -> if???
    I2C->C |= 0x10; // clear fifo
    I2C->C &= ~0x01; // clear read bit -> write

    // fill fifo before starting transfer
    for (i = 0; i < length && i < 16; ++i) {
        I2C->FIFO = data[i];
    }
    I2C->C |= 0x80; // start transfer
    while(i < length && I2C->S & 0x10) { // write data to fifo while there is data and space
        I2C->FIFO = data[i++];
    }
    while(!(I2C->S & 0x02)); // wait for done
    I2C->S |= 0x02; // clear done flag
}

inline void
i2c_read_data(uint8_t *data, uint16_t length)
{
    uint16_t i = 0;

    I2C->DLEN = length;
    I2C->S |= 0x02; // clear done flag -> if???
    I2C->C |= 0x01 | 0x10; // set read bit, clear FIFO

    I2C->C |= 0x80; // start transfer

    while(!(I2C->S & 0x02)) { // while not done
        while(i < length && I2C->S & 0x20) { // while data left and fifo not empty
            data[i++] = I2C->FIFO;
        }
    }
    while(i < length && I2C->S & 0x20) { // remaining data in fifo
        data[i++] = I2C->FIFO;
    }
    I2C->S |= 0x02; // clear done flag
}
