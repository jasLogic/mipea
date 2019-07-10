#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

struct timer_register_map {
    uint32_t CS;
    uint32_t CLO;
    uint32_t CHI;
    uint32_t C0;
    uint32_t C1;
    uint32_t C2;
    uint32_t C3;
};

extern volatile struct timer_register_map *TMR;

int     timer_map(void);
void    timer_unmap(void);

extern void timer_read(uint64_t *counter);

#ifdef __cplusplus
}
#endif//__cplusplus

#endif//_TIMER_H_
