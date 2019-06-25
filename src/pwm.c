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

int pwm_map(void)
{
    if (clock_map() < 0) {
        return -1;
    }

    return peripheral_map(&pwm_base_ptr, PWM_OFFSET, PWM_SIZE);
}

void pwm_unmap(void)
{
    pwm_disable(PWM_CHANNEL0);
    pwm_disable(PWM_CHANNEL1);
    clock_disable(&CM->PWMCTL);

    peripheral_unmap(pwm_base_ptr, PWM_SIZE);
    clock_unmap(); // unmap clock too
}

void pwm_enable(enum pwm_channel_num channel)
{
    if (channel == PWM_CHANNEL0) {
        PWM->CTL |= 1;
    } else {
        PWM->CTL |= 0x100;
    }
}

void pwm_disable(enum pwm_channel_num channel)
{
    if (channel == PWM_CHANNEL0) {
        PWM->CTL &= ~1;
    } else {
        PWM->CTL &= ~0x100;
    }
}

void pwm_configure(enum pwm_channel_num channel, pwm_channel_config *config)
{
    clock_configure(&CM->PWMCTL, CLOCK_PLLD, config->divisor, 0);
    clock_enable(&CM->PWMCTL);

    if (channel == PWM_CHANNEL0) {
        PWM->CTL &= ~0xff; // clear all pwm0 bits
        PWM->CTL |= config->ctl_register;

        PWM->RNG1 = config->range;

    } else {
        PWM->CTL &= ~0xff00; // clear all pwm1 bits
        PWM->CTL |= config->ctl_register << 8;

        PWM->RNG2 = config->range;
    }
}
