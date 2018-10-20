#include "clock.h"

#include <stdint.h>
#include <stddef.h>

#include "bcm2835_peripherals.h"

peripheral clock_peripheral = {CLOCK_BASE, CLOCK_BLOCK_SIZE, 0, NULL};

uint32_t *clock_map(void) {
    if (peripheral_map(&clock_peripheral) == NULL) {
		return NULL;
	}
	clock_base_pointer = (volatile uint32_t *)clock_peripheral.map;
	return (uint32_t *)clock_base_pointer;
}

void clock_unmap(void) {
    peripheral_unmap(&clock_peripheral);
}


void clock_enable(volatile uint32_t *reg) {
    *reg |= CM_PASSWD | 0x10;
}

void clock_disable(volatile uint32_t *reg) {
    if (*reg & 0x80) {
		//*reg = CM_PASSWD | 0x01; // Kill clock?
		//*reg |= CM_PASSWD | (1 << 5); // Kill clock
		*reg = CM_PASSWD | (*reg & ~0x10); // Disable clock
		//usleep(110); // Not needed?
		while(*reg & 0x80); // Wait for busy flag to turn off
	}
}

void clock_configure(volatile uint32_t *reg, clock_source src, unsigned int divisor, unsigned int mash) {
    clock_disable(reg);

    *(reg + 1) = CM_PASSWD | divisor << 12;
    *reg |= CM_PASSWD | mash << 9;
    *reg |= CM_PASSWD | src;
}
