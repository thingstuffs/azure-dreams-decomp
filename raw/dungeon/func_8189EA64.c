#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_8002436C(void) __attribute__((noreturn));
extern void func_80024370(void) __attribute__((noreturn));
extern void func_800243A4(void) __attribute__((noreturn));
extern void func_800478B8(void *arg0);

void func_80024264(void *arg0, s32 arg1, void *arg2)
{
    s16 state;
    void *owner;

    owner = FIELD(arg0, void *, 8);
    FIELD(owner, u16, 0x14)++;
    FIELD(arg0, u16, 2)++;
    func_800478B8(arg2);

    state = FIELD(arg0, s16, 0);
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        func_800243A4();
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    func_800243A4();

state_0: {
    u8 value;
    u16 upper;
    u16 lower;

    value = FIELD(arg2, u8, 0xE);
    upper = FIELD(arg2, u16, 0x1E);
    value++;
    FIELD(arg2, u8, 0xE) = value;
    FIELD(arg2, u8, 0xD) = value;
    FIELD(arg2, u8, 0xC) = value;
    lower = FIELD(arg2, u16, 0x1C);
    upper += 0x10;
    FIELD(arg2, u16, 0x1E) = upper;
    lower += 0x100;
    FIELD(arg2, u16, 0x1C) = lower;
    func_80024370();
}

state_1: {
    u8 value;
    u16 lower;
    s32 tail_value;

    value = FIELD(arg2, u8, 0xE);
    lower = FIELD(arg2, u16, 0x1C);
    value++;
    lower += 0x80;
    FIELD(arg2, u8, 0xE) = value;
    FIELD(arg2, u8, 0xD) = value;
    FIELD(arg2, u8, 0xC) = value;
    FIELD(arg2, u16, 0x1C) = lower;
    tail_value = FIELD(arg0, s16, 2) << 8;
    ASM_TAILSLOT_PIN_TIED(tail_value);
    func_8002436C();
}

state_2: {
    u8 value;
    s32 position;

    value = FIELD(arg2, u8, 0xE) + 6;
    FIELD(arg2, u8, 0xE) = value;
    FIELD(arg2, u8, 0xD) = value;
    FIELD(arg2, u8, 0xC) = value;
    position = FIELD(arg0, s16, 2);
    
    FIELD(arg2, u16, 0x1E) = (position + 0x10) << 8;
    if (FIELD(arg0, s16, 2) < FIELD(arg0, s16, 4)) {
        goto done;
    }
    FIELD(arg0, u16, 2) = 0;
    FIELD(arg0, u16, 0)++;
    func_800243A4();
}

state_3:
    func_800478B8(arg2);

done:
    return;
}

/* MECHANISM: Forward labels recover the retail dispatch/body order while preserving the 0x20 frame and s1/s0 holds.
   Case-scoped sibling locals reproduce the interleaved RMW loads without merging allocator live ranges.
   A scoped tied v0 tail-slot pin exposes the state-1 lh/j/sll continuation contract to maspsx.
   ASM_KEEP preserves the signed state-2 lh, and its explicit done edge fixes the final branch displacement. */
