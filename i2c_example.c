/*
 * i2c_example.h
 * Copyright (C) 2019  jasLogic
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

/*
 * This program uses I2C to communicate with the L3GD20H gyro
 * To compile use:
 * gcc -o i2c_example -Wall i2c_example.c -lmipea
 */

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include <mipea/gpio.h>
#include <mipea/i2c.h>

int
main(void)
{
    if (gpio_map() == NULL || i2c_map() == NULL) { // map peripherals
        return 1; // return if mapping fails
    }

    uint32_t sda = 2;
    uint32_t scl = 3;

    // tell the GPIOs to use I2C on them
    gpio_func(sda, ALT0);
    gpio_func(scl, ALT0);

    i2c_config_t conf = {
        0x6a,   // address
        4000    // clock divider -> clk must be < 100kHz
    };
    i2c_configure(&conf);

    i2c_write_byte(0x20); // write to ctrl1 register
    i2c_write_byte(0xF); // turn the power on

    while(1) {
        int data_length = 6;
        uint8_t data[data_length];

        i2c_write_byte(0x28 | 0x80); /* we want to read from address 0x28
                                        0x80 for consecutive reads */
        i2c_read_data(data, data_length);

        printf("X: %d\nY: %d\nZ: %d\n\n", data[0] | (data[1] << 8),
            data[2] | (data[3] << 8), data[4] | (data[5] << 8));

        usleep(100000);
    }

    i2c_stop();

    gpio_unmap();
    i2c_unmap();
}
