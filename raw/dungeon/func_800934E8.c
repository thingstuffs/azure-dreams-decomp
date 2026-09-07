#include "common.h"

extern void func_80098C78(void) __attribute__((noreturn));

s32 func_80098C48(s32 arg0) {
    s32 count;
    s8 *ptr;

    count = 0x13;
    ptr = (s8 *)0x80010294;
    do {
        if ((s32)ptr == arg0) {
            s32 dead = (s16)count;

            ASM_TAILSLOT_PIN_TIED(dead);
            func_80098C78();
        }
        ASM_SCHED_BARRIER();
        count -= 1;
        ptr -= 4;
    } while (count >= 0);
    return -1;
}

/* MECHANISM: A fixed-address literal gives retail's lui/ori base and natural v0/v1 loop roles.
   The noreturn dispatcher plus tied tail-slot pin sinks the signed counter into the tail-j slot.
   A merge scheduling barrier prevents count-- hoisting and its compensating addiu. */
