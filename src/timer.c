#include "timer.h"

#include <stdint.h>
#include <stddef.h>

#include "peripherals.h"

static peripheral_t timer_peripheral = {TIMER_BASE, TIMER_BLOCK_SIZE, 0, NULL};

uint32_t *
timer_map(void)
{
    if (peripheral_map(&timer_peripheral) == NULL) {
		return NULL;
	}
	timer_base_ptr = (volatile uint32_t *)timer_peripheral.map;
	return (uint32_t *)timer_base_ptr;
}

void
timer_unmap(void)
{
    peripheral_unmap(&timer_peripheral);
}

inline void
timer_read(uint64_t *counter)
{
    *counter = TIMER->CHI;
    *counter = *counter << 32;
    *counter |= TIMER->CLO;
}
