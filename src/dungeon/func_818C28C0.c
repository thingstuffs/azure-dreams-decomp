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
    s8 intensity;
} Obj;

extern void func_80024154(void) __attribute__((noreturn));
extern void func_800241C8(void) __attribute__((noreturn));
extern void func_800241CC(void) __attribute__((noreturn));
extern s32 D_800814A0[3];

void func_818C28C0(Obj *arg0)
{
    s16 timer;
    s16 rem;
    s16 value;

    arg0->inner->counter++;
    arg0->timer++;
    timer = arg0->timer;

    if (timer >= 0x30) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        func_800241CC();
        return;
    }

    if (timer < 0x10) {
        s32 ret;

        ret = *(volatile u8 *)&arg0->timer * 8;
        ASM_TAILSLOT_PIN_TIED(ret);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80024154();
        return;
    }

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (timer < 0x20) {
        s32 ret;

        ret = 0x80;
        ASM_TAILSLOT_PIN_TIED(ret);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80024154();
        return;
    }

    arg0->intensity = -0x80 - ((timer - 0x20) * 8);
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    rem = (s16)arg0->timer % 4;
    if (rem == 1) {
        goto rem_one;
    }
    if (rem < 2) {
        value = 0x7DCF;
        if (rem != 0) {
            func_800241CC();
        }
        goto store_value;
    }
    if (rem == 2) {
        goto rem_two;
    }
    value = 3;
    if (rem == value) {
        value = 0x7E02;
        goto store_value;
    }
    func_800241CC();

rem_one:
    {
        s32 ret;

        ret = 0x7E00;
        ASM_TAILSLOT_PIN_TIED(ret);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_800241C8();
    }

rem_two:
    value = 0x7E01;
store_value:
    
    arg0->value = value;
}

/* MECHANISM: Frameless noreturn tails use tied $v0 carriers for dead delay-slot values.
   A volatile byte reread and two seam barriers preserve retail load/schedule order.
   Shared-store gotos plus $v0 value reuse (3 -> 0x7E02) free rem into $v1. */
