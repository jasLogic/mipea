#include "bcm2835_peripherals.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

uint32_t *peripheral_map(peripheral *per) {
	//int mem_fd;
	//void *reg_map = NULL;

	if ((per->mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) {	/* RDWR: read and write, SYNC: synchron (nur einer) */
		fprintf(stderr, "Failed to open '/dev/mem'... Try sudo?\n");
		return NULL;
	}

	per->map = mmap(NULL, per->block_size, PROT_READ|PROT_WRITE, MAP_SHARED, per->mem_fd, per->v_addr);
	/* NULL: Kernel entscheidet, wo virtuelle Addresse, BLOCK_SIZE: Wie viel, Read/Write, MAP_SHARED: andere Prozesse können meine änderungen sehen, wovon gelesen werden soll, Addresse */
	if (per->map == MAP_FAILED) {
		fprintf(stderr, "Failed mmaping gpios...\n");
		close(per->mem_fd);
		return NULL;
	}

	return per->map;
}

void peripheral_unmap(peripheral *per) {
	munmap(per->map, per->block_size);
	close(per->mem_fd);
}
