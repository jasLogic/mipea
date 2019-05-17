/*
 * pwm.c
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

#include "pwm.h"

#include <stdint.h>
#include <stddef.h>

#include "peripherals.h"
#include "clock_manager.h"

uint32_t *
pwm_map(void)
{
    if (!peripheral_ismapped((uint32_t *)pwm_base_ptr, PWM_SIZE)) {
        if (clock_map() == NULL) {
            return NULL;
        }

        pwm_base_ptr = (volatile uint32_t *)peripheral_map(PWM_OFFSET, PWM_SIZE);
    }
    return (uint32_t *)pwm_base_ptr;
}

void
pwm_unmap(void)
{
    pwm_disable(PWM_CHANNEL0);
    pwm_disable(PWM_CHANNEL1);
    clock_disable(&CM->PWMCTL);

    if (peripheral_ismapped((uint32_t *)pwm_base_ptr, PWM_SIZE)) {
        peripheral_unmap((uint32_t *)pwm_base_ptr, PWM_SIZE);
    }
    clock_unmap(); // unmap clock too
}

void
pwm_enable(pwm_channel_t channel)
{
    if (channel == PWM_CHANNEL0) {
        PWM->CTL |= 1;
    } else {
        PWM->CTL |= 0x100;
    }
}

void
pwm_disable(pwm_channel_t channel)
{
    if (channel == PWM_CHANNEL0) {
        PWM->CTL &= ~1;
    } else {
        PWM->CTL &= ~0x100;
    }
}

void
pwm_configure(pwm_channel_config_t *config)
{
    clock_configure(&CM->PWMCTL, CLOCK_PLLD, config->divisor, 0);
    clock_enable(&CM->PWMCTL);

    if (config->channel == PWM_CHANNEL0) {
        PWM->CTL &= ~0xff; // clear all pwm0 bits
        PWM->CTL |= config->ctl_register;

        PWM->RNG1 = config->range;

    } else {
        PWM->CTL &= ~0xff00; // clear all pwm1 bits
        PWM->CTL |= config->ctl_register << 8;

        PWM->RNG2 = config->range;
    }
}
