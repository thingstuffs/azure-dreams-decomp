#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((s8 *)(ptr) + (off)))

extern s32 D_800814A0;

void func_80023F6C(void *arg0) {
    void *object;
    s16 state;
    u16 old_state;
    s32 value;

    object = FIELD(arg0, void *, 4);
    state = FIELD(arg0, s16, 0);
    old_state = FIELD(arg0, u16, 0);

    switch (state) {
    case 0:
        if (FIELD(object, s16, 0) == 0) {
            FIELD(arg0, u16, 0) = old_state + 1;
        }
        break;

    case 1:
        value = FIELD(arg0, s32, 8) + 0xFFF7F7F8U;
        FIELD(arg0, s32, 8) = value;
        if (value <= 0x80808) {
            FIELD(arg0, u16, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
        break;

    default:
        break;
    }

    ASM_KEEP(arg0);
}

/* MECHANISM: This is a frameless leaf: both apparent func_80023FF0 jumps are
   rowbase-local edges to the shared jr-ra epilogue. A natural two-case switch
   preserves the pointer/state loads, jump-delay store, and direct global RMW. */
