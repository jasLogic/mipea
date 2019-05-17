/*
 * mipea.c
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

#include "mipea.h"

int
mipea_map(void)
{
    if (!dma_map() || !gpio_map() || !pwm_map() || !spi_map()
        || !timer_map()) {
        return -1;
    }
    return 1;
}

void
mipea_unmap(void)
{
    dma_unmap();
    gpio_unmap();
    pwm_unmap();
    spi_unmap();
    timer_unmap();
}
