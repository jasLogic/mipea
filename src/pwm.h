/*
 * pwm.h
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

#ifndef _PWM_H_
#define _PWM_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define PWM_BASE		0x2020C000
#define PWM_BLOCK_SIZE	0x24

volatile uint32_t *pwm_base_ptr;

struct pwm_register_map {
    uint32_t CTL;
    uint32_t STA;
    uint32_t DMAC;
    uint32_t: 32;   /* address not implemented */
    uint32_t RNG1;
    uint32_t DAT1;
    uint32_t FIF1;
    uint32_t: 32;   /* address not implemented */
    uint32_t RNG2;
    uint32_t DAT2;
};
#define PWM     ((struct pwm_register_map *)pwm_base_ptr)

#define RNG_CHANNEL0    PWM->RNG1
#define DAT_CHANNEL0    PWM->DAT1
#define RNG_CHANNEL1    PWM->RNG2
#define DAT_CHANNEL1    PWM->DAT2

typedef enum {
    PWM_CHANNEL0, PWM_CHANNEL1
} pwm_channel_t;

typedef struct {
    pwm_channel_t channel;
    union {
        struct {
            uint32_t: 1;        /* use pwm_enable / pwm_disable */
            uint32_t mode: 1;
            uint32_t rptl: 1;
            uint32_t sbit: 1;
            uint32_t pola: 1;
            uint32_t usef: 1;
            uint32_t: 1;        /* unimplemented / unused */
            uint32_t msen: 1;
        };
        uint32_t ctl_register;
    };
    unsigned int divisor;
    uint32_t range;
} pwm_channel_config_t;

uint32_t *  pwm_map(void);
void        pwm_unmap(void);

void pwm_enable(pwm_channel_t channel);
void pwm_disable(pwm_channel_t channel);
void pwm_configure(pwm_channel_config_t *config);

/* ----- CTL Register bit values ----- */
#define PWM_CTL_MODE_PWM        0x0
#define PWM_CTL_MODE_SERIALISER 0x1
#define PWM_RPTL_STOP   0x0
#define PWM_RPTL_REPEAT 0x1
#define PWM_SBIT_LOW    0x0
#define PWM_SBIT_HIGH   0x1
#define PWM_POLA_DEFAULT    0x0
#define PWM_POLA_INVERTED   0x1
#define PWM_USEF_DATA   0x0
#define PWM_USEF_FIFO   0x1
#define PWM_MSEN_PWMALGORITHM   0x0
#define PWM_MSEN_MSRATIO        0x1

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PWM_H_ */
