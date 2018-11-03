/*
 * spi_example.h
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

// This program uses SPI to communicate with the MCP3002 ADC

 #include <stdio.h>
 #include <stdint.h>
 #include <unistd.h>

 #include "src/gpio.h"
 #include "src/spi.h"

 union spi_mcp3002_transfer {
    struct bits {
        uint8_t dntc:4; // Don't care
        uint8_t odd:1;  // ODD/!SGN bit
        uint8_t sgl:1;  // SGL/!DIFF bit
        uint8_t lst:2;  // Leading zero and starting bit
    } bits;
    uint8_t val;
} spi_mcp3002_transfer;

int main(void) {
    if (gpio_map() == NULL || spi_map() == NULL) { // map peripherals
        return 1; // return if mapping fails
    }

    uint32_t sclk = 11;    // connected to CLK
	uint32_t mosi = 10;    // connected to D_in
	uint32_t miso = 9;     // connected to D_out
	uint32_t ce0 = 8;      // connected to !CS/SHDN

    // tell the GPIOs to use SPI on them
	gpio_func(sclk, ALT0);
	gpio_func(mosi, ALT0);
	gpio_func(miso, ALT0);
	gpio_func(ce0, ALT0);

	spi_channel_config conf = {
		CE0,    // which chip enable line to use
        0,      // data on clock leading (0) or trailing (1) edge
        0,      // clock polarity: rest state low (0) or high (1)
        0,      // chip select polarity: active low (0) or high (1) -> I tested
                // this on CE0 and CE1 and it did NOT have any affect on
                // the polarity of the chip select. But I would set this
                // bit anyway just to be save.
        0,      // CE0 polarity: active low (0) or high (1)
        0,      // CE1 similar to CE0
        0,      // CE2 similar to CE0
        1000    // clock divisor: the RaspberryPi Zero runs at 1GHz and the
                // MCP3002 has a maximum clock frequency of 1Mhz
                // => when looking at the signal with a logic analyser it
                // appears that the clock is only running at 250Mhz although
                // cpuinfo_cur_freq returns 1000000 ?
	};

	spi_configure(&conf);

    union spi_mcp3002_transfer t;
    t.bits.lst = 0b01; // Leading zero and starting bit
    t.bits.sgl = 1;
    t.bits.odd = 0;

    uint16_t adc = 0x300;   // Because only the last 2 bit of the first
                            // transmission are important we set adc to
                            // 0b000000110000000 and AND the first result
                            // to it. If there are some errors in the
                            // first 6 bits we do not have errors in the result.

    while(adc > 1) {
        adc = 0x300;
        spi_transfer_start();           // Start a new transfer -> CS
        adc &= spi_transfer_byte(t.val) << 8; // Transfer the first byte
                                             // and return the MS 2 bits
        adc |= spi_transfer_byte(0);    // Send don't care and recive the last byte
        spi_transfer_stop();

        printf("ADC: %d\n", adc);
        usleep(100000);
    }

}
