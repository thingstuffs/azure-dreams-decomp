#include "common.h"

typedef struct S_80023F6C_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u8 pad_02[0x2];
    void * unk_04;
    s32 unk_08;
} S_80023F6C_0;   /* arg0 in func_80023F6C */

typedef struct S_80023F6C_1 {
    s16 unk_00;
} S_80023F6C_1;   /* object in func_80023F6C */



extern s32 D_800814A0;

void func_80023F6C(void *arg0) {
    void *object;
    s16 state;
    u16 old_state;
    s32 value;

    object = ((S_80023F6C_0 *)arg0)->unk_04;
    state = ((S_80023F6C_0 *)arg0)->unk_00.s;
    old_state = ((S_80023F6C_0 *)arg0)->unk_00.u;

    switch (state) {
    case 0:
        if (((S_80023F6C_1 *)object)->unk_00 == 0) {
            ((S_80023F6C_0 *)arg0)->unk_00.u = old_state + 1;
        }
        break;

    case 1:
        value = ((S_80023F6C_0 *)arg0)->unk_08 + 0xFFF7F7F8U;
        ((S_80023F6C_0 *)arg0)->unk_08 = value;
        if (value <= 0x80808) {
            (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
        break;

    default:
        break;
    }

    ASM_KEEP(arg0);   /* MATCH pin: load-bearing for the whole function shape */
}

/* MECHANISM: This is a frameless leaf: both apparent func_80023FF0 jumps are
   rowbase-local edges to the shared jr-ra epilogue. A natural two-case switch
   preserves the pointer/state loads, jump-delay store, and direct global RMW. */
