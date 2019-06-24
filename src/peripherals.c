/*
 * peripherals.c
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

#include "peripherals.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "../config.h"

#if defined(BCM2835)
	#define PERIPHERAL_BASE PERIPHERAL_BASE_BCM2835
#elif defined(BCM2836_7)
	#define PERIPHERAL_BASE PERIPHERAL_BASE_BCM2836_7
#else
	#error "No SoC specified"
#endif//BCM2835

#define perror_inf()	fprintf(stderr, "%s:%d: In function %s:\n", __FILE__,  \
	__LINE__, __func__)

int peripheral_map(volatile uint32_t **map, uint32_t offset, uint32_t size)
{
	if (peripheral_ismapped(*map, size)) {
		return 1; // already mapped
	}

	int fd = open("/dev/mem", O_RDWR | O_SYNC);
	if (fd < 0) {
		perror_inf();
		perror("Failed to open /dev/mem");
		return -1;
	}

	*map = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd,
		PERIPHERAL_BASE + offset);

	close(fd);

	if (*map == MAP_FAILED) {
		perror_inf();
		perror("Failed mmaping peripheral");
		return -1;
	}

	return 0;
}

void peripheral_unmap(volatile uint32_t *map, uint32_t size)
{
	if (peripheral_ismapped(map, size)) {
		if (munmap((void *)map, size) == -1) {
			perror_inf();
			perror("Failed munmapping peripheral");
		}
	}
}

int peripheral_ismapped(volatile uint32_t *map, uint32_t size)
{
	if (map == NULL) return 0;
	if (msync((void *)map, size, 0) == -1) return 0;
	return 1;
}
