#include "pwm.h"

#include <stdint.h>
#include <stddef.h>

#include "bcm2835_peripherals.h"
#include "clock.h"

peripheral pwm_peripheral = {PWM_BASE, PWM_BLOCK_SIZE, 0, NULL};

uint32_t *pwm_map(void) {                       // -- clock mapped too --
    if (peripheral_map(&pwm_peripheral) == NULL|| clock_map() == NULL) {
		return NULL;
	}
	pwm_base_pointer = (volatile uint32_t *)pwm_peripheral.map;
	return (uint32_t *)pwm_base_pointer;
}

void pwm_unmap(void) {
    peripheral_unmap(&pwm_peripheral);
    clock_unmap(); // <-----
}

void pwm_enable(pwm_channel channel) {
    if (channel == PWM_CHANNEL_0) {
        CTL |= 1;
    } else {
        CTL |= (1 << 8);
    }
}
void pwm_disable(pwm_channel channel) {
    if (channel == PWM_CHANNEL_0) {
        CTL &= ~1;
    } else {
        CTL &= ~(1 << 8);
    }
}

void pwm_configure(pwm_channel_config *config) {
    /*
    if (config->channel == PWM_CHANNEL_0) {
        CTL &= ~0b11111110; // Erstmal alles 0 machen

        uint32_t change = 0;
        if (config->mode == SERIALISER_MODE) {
            change |= (1 << 1);
        }
        if (config->repeat_last) {
            change |= (1 << 2);
        }
        if (config->sbit) {
            change |= (1 << 3);
        }
        if (config->polarity) {
            change |= (1 << 4);
        }
        if (config->use_fifo) {
            change |= (1 << 5);
        }
        if (config->msen) {
            change |= (1<< 7);
        }

        CTL |= change;
    } else {
        CTL &= (0b1111111 << 9); // Alle von channel 2 auf 0
    }
    */

    clock_configure(&CM_PWMCTL, CLOCK_OSC, 16, 0);
    clock_enable(&CM_PWMCTL);

	CTL |= 0x80;

	RNG1 = 1024;
	DAT1 = 1023;
}
