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
    clock_configure(&CM_PWMCTL, CLOCK_PLLD, config->divisor, 0);
    clock_enable(&CM_PWMCTL);

    if (config->channel == PWM_CHANNEL_0) {
        CTL &= ~0xFF; // Change all the pwm0 bits to 0

        if (config->mode == SERIALISER_MODE) {
            CTL |= 0x2;
        }
        if (config->repeat_last) {
            CTL |= 0x4;
        }
        if (config->sbit) {
            CTL |= 0x8;
        }
        if (config->polarity == POL_INVERTED) {
            CTL |= 0x10;
        }
        if (config->use_fifo) {
            CTL |= 0x20;
        }
        if (config->msen == MSEN_MS_RATIO) {
            CTL |= 0x80;
        }
        RNG1 = config->range;

    } else {
        CTL &= ~(0xFF << 8); // Change all the pwm1 bits to 0

        if (config->mode == SERIALISER_MODE) {
            CTL |= (0x2 << 8);
        }
        if (config->repeat_last) {
            CTL |= (0x4 << 8);
        }
        if (config->sbit) {
            CTL |= (0x8 << 8);
        }
        if (config->polarity == POL_INVERTED) {
            CTL |= (0x10 << 8);
        }
        if (config->use_fifo) {
            CTL |= (0x20 << 8);
        }
        if (config->msen == MSEN_MS_RATIO) {
            CTL |= (0x80 << 8);
        }
        RNG2 = config->range;
    }

	//RNG1 = 1000000;
	DAT1 = 100000;
}
