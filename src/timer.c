#include "timer.h"

#include <stdint.h>
#include <stddef.h>

#include "peripherals.h"
#include "../config.h" // for inline

int timer_map(void)
{
    return peripheral_map(&timer_base_ptr, TIMER_OFFSET, TIMER_SIZE);
}

void timer_unmap(void)
{
    peripheral_unmap(timer_base_ptr, TIMER_SIZE);
}

inline void timer_read(uint64_t *counter)
{
    *counter = TIMER->CHI;
    *counter = *counter << 32;
    *counter |= TIMER->CLO;
}
