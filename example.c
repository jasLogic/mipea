/*
 * example.c
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

#include <unistd.h>

#include "src/gpio.h"

int
main(void)
{
    if (gpio_map() == NULL) { /* map peripherals */
        return 1; /* return if mapping fails */
    }

    int out_pin = 18; /* LED on pin 18 */
    int in_pin = 19; /* Button wired to GND on pin 19 */

    gpio_out(out_pin); /* Make gpio 18 an output */

    gpio_inp(in_pin); /* Make gpio 19 an input */
    gpio_pud(in_pin, PUD_UP); /* Enable the internal pullup on pin 19 */

    while(gpio_tst(in_pin) != 0) { /* While pin 19 is high */
        gpio_set(out_pin); /* Set pin 18 */
        sleep(1);
        gpio_clr(out_pin); /* Clear pin 18 */
        sleep(1);
    }

    gpio_unmap();
    return 0;
}
