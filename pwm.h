#ifndef PWM_H
#define PWM_H

#include <stdint.h>
#include <stdbool.h>

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
    pwm_channel channel;
    pwm_modes mode;
    bool repeat_last;
    bool sbit;
    pwm_pol polarity;
    bool use_fifo;
    pwm_msen msen;
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
#define RNG1    *(pwm_base_pointer + 3)
#define DAT1    *(pwm_base_pointer + 4)
#define FIF1    *(pwm_base_pointer + 5)
#define RNG2    *(pwm_base_pointer + 6)
#define DAT2    *(pwm_base_pointer + 7)

#endif//PWM_H
