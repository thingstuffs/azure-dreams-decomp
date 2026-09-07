#include "common.h"

typedef struct Inner_800B45A0 {
    u8 pad0[8];
    s16 field8;
} Inner_800B45A0;

typedef struct Obj_800B45A0 {
    u8 pad0[4];
    s32 field4;
    void *field8;
    void *fieldC;
    u8 pad10[0x3C - 0x10];
    Inner_800B45A0 *field3C;
    u8 pad40[0x54 - 0x40];
    void **field54;
} Obj_800B45A0;

extern void func_8004E994(void *arg0, void *arg1);
extern void func_8004B1A4(void *arg0);
extern s32 D_800814A0[3];

void func_800B1D00(Obj_800B45A0 *arg0)
{
    Inner_800B45A0 *inner;
    u16 old;
    s32 value;
    s32 adjustment;

    inner = arg0->field3C;
    old = inner->field8;
    value = old + 4;
    adjustment = (s16)old;
    adjustment += 4;
    adjustment -= arg0->field4;
    adjustment >>= 2;
    value += adjustment;
    inner->field8 = value;

    if (arg0->field4 + 0x80 < arg0->field3C->field8) {
        func_8004E994(*arg0->field54, inner);
        func_8004B1A4(arg0->field8);
        func_8004B1A4(arg0->fieldC);
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

/* MECHANISM: A 0x18 frame naturally holds arg0 in s0 across all three calls.
   Separate ordered s32 adjustment statements prevent reassociation of +4 into
   the field4 load, restoring retail's load-delay nop and v0/v1/a0 lifetimes. */
