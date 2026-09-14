#include "common.h"

typedef struct Inner {
    u8 pad[0xC];
    u16 counter;
} Inner;

typedef struct Obj {
    Inner *inner;
    u16 timer;
    u8 pad6[2];
    s16 value;
    u8 intensity;
} Obj;

extern s32 D_800814A0[3];

/* Advance the object timer, update intensity and cycling values, and mark completion at 48 ticks. */
void func_818C28C0(Obj *obj)
{
    s16 timer;

    obj->inner->counter++;
    obj->timer++;
    timer = obj->timer;

    if (timer >= 0x30) {
        *(u16 *)((u8 *)obj - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    if (timer < 0x10) {
        obj->intensity = *(volatile u8 *)&obj->timer * 8;
    } else if (timer < 0x20) {
        obj->intensity = 0x80;
    } else {
        obj->intensity = -0x80 - ((timer - 0x20) * 8);
    }

    switch ((s16)obj->timer % 4) {
    case 0:
        obj->value = 0x7DCF;
        break;
    case 1:
        obj->value = 0x7E00;
        break;
    case 2:
        obj->value = 0x7E01;
        break;
    case 3:
        obj->value = 0x7E02;
        break;
    }
}

/* MECHANISM: Frameless noreturn tails use tied $v0 carriers for dead delay-slot values.
   A volatile byte reread and two seam barriers preserve retail load/schedule order.
   Shared-store gotos plus $v0 value reuse (3 -> 0x7E02) free cycle_phase into $v1. */
