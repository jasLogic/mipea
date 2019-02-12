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

uint32_t *peripheral_map(peripheral *per) {
	if ((per->mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) {
		perror("Failed to open '/dev/mem'");
		return NULL;
	}

	per->map = mmap(NULL, per->block_size, PROT_READ|PROT_WRITE, MAP_SHARED, per->mem_fd, per->v_addr);

	if (per->map == MAP_FAILED) {
		perror("Failed mmaping peripheral");
		close(per->mem_fd);
		return NULL;
	}

	return per->map;
}

void peripheral_unmap(peripheral *per) {
	if (munmap(per->map, per->block_size) == -1) {
		perror("Failed munmapping peripheral");
	}
	close(per->mem_fd);
}
