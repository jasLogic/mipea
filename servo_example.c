// To compile use:
//  gcc -o servo_example servo_example.c gpio.c pwm.c clock.c bcm2835_peripherals.c
//                                       --- pwm.c makes use of clock.c ---

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "gpio.h"
#include "pwm.h"

int main(void) {
    if (gpio_map() == NULL || pwm_map() == NULL) { // Map peripherals
        return 1; // return if mapping fails
    }

    int servo = 18; // this and pin 12 are the PWM0 pins, there is a servo wired to this pin
    gpio_func(servo, ALT5); // pin 18 uses alternate function 5 for pwm

    pwm_channel_config ch = {
        PWM_CHANNEL_0,  // Which channel to use 0/1
        PWM_MODE,       // use pwm mode or a serial mode, where serial data is sent
        false,          // if serial mode: repeat the last data if there is no new
        false,          // what polarity the output should have, if there is no transmission
        POL_DEFAULT,    // do not invert the output
        false,          // if serial mode: use fifo?
        MSEN_MS_RATIO,  // pwm algorithm: distribute the pwm as even as possible, not useful for servo control
        1953,           // clock divisor
        5120             // the range of the counter
    };
    /* Explanation of clock divisor and range value:
        - the input clock of the pwm is 500MHz
        - we need 50Hz
        -> 500Mhz / (range * divisor) = 50Hz

        - we want to have exactly one byte accuracy for the servo (more than enough)
        -> 50Hz => 20ms
        -> one step is exactly (20ms / range) long
        - pwm is between 1ms and 2ms pulselength
        - so we delta = 1ms of time to cover
        - we want to cover 1ms with 256 steps
        - becuase our pulse is always minimum of 1ms (maximum of 2ms) we also want 256 steps in this 1ms
        -> (20ms / range) * 256 = 0.001ms or (20ms / range) * 2 * 256 = 0.002ms
        => solves to: range = 5120

        - putting this value into the function at the top
        -> 100Mhz / (5120 * divisor) = 50Hz
        => solves to: divisor = 1953.125
    */

    pwm_configure(&ch);
    pwm_enable(PWM_CHANNEL_0);

    bool going_up = true;
    unsigned char num = 0;

    for (int i = 0; i < 10;) {
        if (going_up) {
            if (num == 255) {
                going_up = false;
                ++i;
            } else {
                ++num;
            }
        } else {
            if (num == 0) {
                going_up = true;
            } else {
                --num;
            }
        }
        DAT1 = num + 256;
        usleep(10000);
    }

    gpio_unmap();
    pwm_unmap();

    return 0;
}
