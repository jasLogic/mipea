#include "timer.h"

#include <stdint.h>
#include <stddef.h>

#include "peripherals.h"

uint32_t *
timer_map(void)
{
    timer_base_ptr = (volatile uint32_t *)peripheral_map(PERIPHERAL_BASE +
        TIMER_OFFSET, TIMER_SIZE);
    return (uint32_t *)timer_base_ptr;
}

void
timer_unmap(void)
{
    peripheral_unmap((uint32_t *)timer_base_ptr, TIMER_SIZE);
}

inline void
timer_read(uint64_t *counter)
{
    *counter = TIMER->CHI;
    *counter = *counter << 32;
    *counter |= TIMER->CLO;
}
