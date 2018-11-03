#ifndef PWM_H
#define PWM_H

#include <stdint.h>

volatile uint32_t *pwm_base_pointer;

typedef enum pwm_channel {
    PWM_CHANNEL_0, PWM_CHANNEL_1
} pwm_channel;

typedef enum pwm_modes {
    PWM_MODE, SERIALISER_MODE
} pwm_modes;

typedef enum pwm_pol {
    POL_DEFAULT, POL_INVERTED
} pwm_pol;

typedef enum pwm_msen {
    MSEN_PWM_ALGORITHM, MSEN_MS_RATIO
} pwm_msen;

typedef struct pwm_channel_config {
    uint32_t mode:1;
    uint32_t rptl:1;
    uint32_t sbit:1;
    uint32_t pola:1;
    uint32_t usef:1;
    uint32_t msen:1;

    pwm_channel channel;

    unsigned int divisor;
    unsigned int range;
} pwm_channel_config;

uint32_t *pwm_map(void);
void pwm_unmap(void);

void pwm_enable(pwm_channel channel);
void pwm_disable(pwm_channel channel);
void pwm_configure(pwm_channel_config *config);

/* ----- PWM Registers ----- */
#define CTL     *pwm_base_pointer
#define STA     *(pwm_base_pointer + 1)
#define DMAC    *(pwm_base_pointer + 2)
#define RNG1    *(pwm_base_pointer + 4) // <--- not chronological ---
#define DAT1    *(pwm_base_pointer + 5)
#define FIF1    *(pwm_base_pointer + 6)
#define RNG2    *(pwm_base_pointer + 8) // <--- same ---
#define DAT2    *(pwm_base_pointer + 9)

#define RNG_CHANNEL0    RNG1
#define DAT_CHANNEL0    DAT1
#define RNG_CHANNEL1    RNG2
#define DAT_CHANNEL1    DAT2

#endif//PWM_H
