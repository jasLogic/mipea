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

#endif//BCM2835_REGISTERS_H
