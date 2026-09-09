#include "common.h"

typedef struct {
    u16 pad0;
    u16 count;
} Obj0;

typedef struct {
    u8 pad0[0x14];
    u16 flags14;
    u8 pad16[0x1C - 0x16];
    u16 value1C;
    u16 value1E;
} Obj2;

extern s32 D_800814A0[3];

void func_80171030(Obj0 *arg0, s32 unused, Obj2 *arg2)
{
    u16 value;

    value = arg0->count - 1;
    arg0->count = value;
    if ((s16)value >= 5) {
        value = arg2->value1E + 0x200;
    } else {
        value = arg2->value1E - 0x200;
    }

    arg2->value1E = value;
    arg2->value1C = value;

    if ((s16)arg0->count <= 0) {
        ((u16 *)arg0)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

    if (arg2->flags14 & 0x8000) {
        ((u16 *)arg0)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

/* MECHANISM: The frameless seed already matched the body and control flow.
   A branch-local $v0 value retains arg2->value1E + 0x200.
   ASM_TAILSLOT_PIN lets LEAD28 sink the addiu into the noreturn j delay slot. */
