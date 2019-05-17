# I don't want to use recusrsion
ACLOCAL_AMFLAGS=-I m4

lib_LTLIBRARIES=libmipea.la
libmipea_la_SOURCES=src/clock_manager.c src/dma.c src/gpio.c src/i2c.c src/mailbox_mod.c src/mipea.c src/peripherals.c src/pwm.c src/spi.c src/timer.c
libmipea_la_LDFLAGS=-version-info 2:0:0

pkginclude_HEADERS=src/clock_manager.h src/dma.h src/gpio.h src/i2c.h src/mailbox_mod.h src/mipea.h src/peripherals.h src/pwm.h src/spi.h src/timer.h
