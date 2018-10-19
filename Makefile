CC=gcc
CFLAGS=-Wall

test: test.c gpio.c pwm.c clock.c bcm2835_peripherals.c
	gcc -Wall -o test test.c gpio.c pwm.c clock.c bcm2835_peripherals.c

clean:
	rm test
