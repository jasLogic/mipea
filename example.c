#include <unistd.h>

#include "gpio.h"

int main(void) {
    if (gpio_map() == NULL) { // Mapping is required or else there is a segmentation fault
        return 1; // return if mapping fails
    }

    int out_pin = 18; // LED on pin 18
    int in_pin = 19; // Button wired to GND on pin 19

    gpio_out(out_pin); // Make gpio 18 an output

    gpio_inp(in_pin); // Make gpio 19 an input
    gpio_pud(in_pin, PUD_UP); // Enable the internal pullup on pin 19

    while(gpio_tst(in_pin) != 0) { // While pin 19 is high (because of the internal pullup)
        gpio_set(out_pin); // Set pin 18
        sleep(1);
        gpio_clr(out_pin); // Clear pin 18
        sleep(1);
    }

    gpio_unmap();
    return 0;
}
