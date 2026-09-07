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

/* Advance the object timer, update intensity and cycling values, and mark completion at 48 ticks. */
void func_818C28C0(Obj *obj)
{
    s16 timer;
    s16 cycle_phase;
    s16 cycle_value;

    obj->inner->counter++;
    obj->timer++;
    timer = obj->timer;

    if (timer >= 0x30) {
        *(u16 *)((u8 *)obj - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        func_800241CC();
        return;
    }

    if (timer < 0x10) {
        s32 intensity;

        intensity = *(volatile u8 *)&obj->timer * 8;
        ASM_TAILSLOT_PIN_TIED(intensity);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80024154();
        return;
    }

    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    if (timer < 0x20) {
        s32 intensity;

        intensity = 0x80;
        ASM_TAILSLOT_PIN_TIED(intensity);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80024154();
        return;
    }

    obj->intensity = -0x80 - ((timer - 0x20) * 8);
    ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    cycle_phase = (s16)obj->timer % 4;
    if (cycle_phase == 1) {
        goto phase_one;
    }
    if (cycle_phase < 2) {
        cycle_value = 0x7DCF;
        if (cycle_phase != 0) {
            func_800241CC();
        }
        goto store_value;
    }
    if (cycle_phase == 2) {
        goto phase_two;
    }
    cycle_value = 3;
    if (cycle_phase == cycle_value) {
        cycle_value = 0x7E02;
        goto store_value;
    }
    func_800241CC();

phase_one:
    {
        s32 next_value;

        next_value = 0x7E00;
        ASM_TAILSLOT_PIN_TIED(next_value);   /* MATCH pin: retail delay-slot contents depend on it */
        func_800241C8();
    }

phase_two:
    cycle_value = 0x7E01;
store_value:
    obj->value = cycle_value;
}

/* MECHANISM: Frameless noreturn tails use tied $v0 carriers for dead delay-slot values.
   A volatile byte reread and two seam barriers preserve retail load/schedule order.
   Shared-store gotos plus $v0 value reuse (3 -> 0x7E02) free cycle_phase into $v1. */
