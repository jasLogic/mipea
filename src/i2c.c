#include "i2c.h"

#include <stdint.h>
#include <stddef.h>

#include "peripherals.h"

static peripheral_t i2c_peripheral = {I2C_BASE, I2C_BLOCK_SIZE, 0, NULL};

uint32_t *
i2c_map(void)
{
    if (peripheral_map(&i2c_peripheral) == NULL) {
		return NULL;
	}
	i2c_base_ptr = (volatile uint32_t *)i2c_peripheral.map;
	return (uint32_t *)i2c_base_ptr;
}

void
i2c_unmap(void)
{
    peripheral_unmap(&i2c_peripheral);
}

void
i2c_configure(i2c_config_t *config)
{
    I2C->A = config->addr;
    I2C->DIV = config->div;
}

inline void
i2c_transfer_start(void)
{
    I2C->C |= 0x8000; /* enable bsc controller */
    I2C->S |= 0x2 | 0x100 | 0x200; /* clear flags */
}
inline void
i2c_transfer_stop(void)
{
    while(!(I2C->S & 0x2)); /* wait for last transmission to be completed */
    I2C->C &= ~0x8000; /* disable bsc controller */
}
