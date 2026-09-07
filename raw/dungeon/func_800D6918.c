#include "common.h"

extern void func_800DC0A0(void) __attribute__((noreturn));

void func_800DC078(void *arg0, s32 arg1) {
    register s32 value ASM_REG("$3") = (s16)arg1;

    if (value < 0x80) {
        register s32 half ASM_REG("$2") = value / 2;

        ASM_KEEP(half);
        value = half + 1;
        ASM_TAILSLOT_PIN_TIED(value);
        func_800DC0A0();
    }

    value = 0x40;
    ASM_KEEP(value);
    *(s8 *)((u8 *)arg0 + 2) = 0x57 - value;
    *(s8 *)((u8 *)arg0 + 0xA) = value;
}

/* MECHANISM: A zero-argument noreturn tail contract lets maspsx elide the ra-only frame.
   Guarded $v1/$v0 locals preserve the narrowed value and signed-half register roles.
   The tied tail-slot pin sinks the final addiu into the dispatcher jump delay slot. */
