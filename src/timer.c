#include "timer.h"

#include <stdint.h>
#include <stddef.h>

#include "peripherals.h"
#include "../config.h" // for inline

uint32_t *timer_map(void)
{
    if (!peripheral_ismapped((uint32_t *)timer_base_ptr, TIMER_SIZE)) {
        timer_base_ptr = (volatile uint32_t *)peripheral_map(TIMER_OFFSET, TIMER_SIZE);
    }
    return (uint32_t *)timer_base_ptr;
}

void timer_unmap(void)
{
        peripheral_unmap((uint32_t *)timer_base_ptr, TIMER_SIZE);
}

inline void timer_read(uint64_t *counter)
{
    *counter = TIMER->CHI;
    *counter = *counter << 32;
    *counter |= TIMER->CLO;
}
