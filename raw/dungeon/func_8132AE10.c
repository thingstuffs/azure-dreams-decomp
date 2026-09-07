#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, s32, s32);
extern void func_800478B8(void *);
extern void func_800A020C(void *, void *);

extern s32 D_800814A0;
extern u8 D_80083160[];
extern s16 D_80083228;
extern s8 D_800DCECC[];
extern u8 D_80174C6C[];

void func_80172610(void *arg0, void *arg1, void *arg2)
{
    u8 *actor;
    u8 *output;
    u8 *context;
    u8 *owner;
    u8 *base;
    register u8 *saved_base;
    u8 *linked;
    u8 *source;
    u8 *state;
    s32 first_index;
    s32 work;
    s32 effect_index;
    s32 global_flags;
    s16 compare_index;
    s32 effect;
    s16 old_position;
    s16 new_position;
    u16 new_position_bits;

    actor = arg0;
    output = arg1;
    context = arg2;
    owner = FIELD(actor, u8 *, 0xAC);
    linked = FIELD(owner, u8 *, 0xC);
    source = FIELD(owner, u8 *, 8);
    base = owner + 0x20;
    saved_base = base;

    if (FIELD(actor, u8, 0x9A) != 0) {
        return;
    }

    func_800A020C(FIELD(base, void *, 0x1C), context + 0xC);
    if ((FIELD(base, u32, 0x1C) & 0x20) == 0) {
        func_800478B8(context);
    }

    if (FIELD(linked, u8 *, 0x2C) == D_80174C6C) {
        func_800478B8(context);
        func_800478B8(context);
    }

    old_position = FIELD(actor, s16, 0x2A);
    new_position = FIELD(base, s16, 0x2A);
    new_position_bits = FIELD(base, u16, 0x2A);
    if (old_position != new_position) {
        FIELD(actor, u16, 0x2A) = new_position_bits;
        first_index = ((D_80083228 + new_position + 0x100) >> 9) & 7;
        func_80047784(context, FIELD(FIELD(context, u8 *, 0x2C), u8, first_index), 0);
    }

    state = D_80083160;
    work = ((FIELD(state, s16, 0xC8) + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7;
    compare_index = work;
    if (FIELD(actor, s16, 0x94) != compare_index) {
        func_80047784(context, FIELD(FIELD(context, u8 *, 0x2C), u8, compare_index), 0);
        FIELD(actor, u16, 0x94) = work;
    }

    FIELD(context, u16, 0x14) = FIELD(linked, u16, 0x14);
    FIELD(output, u16, 2) = FIELD(source, u16, 2);
    FIELD(output, u16, 6) = FIELD(source, u16, 6);
    FIELD(output, u16, 0xA) = FIELD(source, u16, 0xA);

    effect_index = ((FIELD(state, s16, 0xC8) + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7;
    effect = D_800DCECC[effect_index];
    FIELD(context, s16, 6) = effect << 2;
    FIELD(context, u16, 0x1C) = FIELD(linked, u16, 0x1C);
    FIELD(context, u16, 0x1E) = FIELD(linked, u16, 0x1E);
    FIELD(context, u16, 0x12) = FIELD(linked, u16, 0x12);

    if (FIELD(owner, u16, 0x1E) & 0x8000) {
        FIELD(actor, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

    if (FIELD(saved_base, u8, 0x9A) == 0x13) {
        FIELD(actor, u8, 0x9A)++;
        FIELD(actor, u16, -2) |= 0x8000;
        global_flags = D_800814A0;
        FIELD(actor, u16, 0x96) = 0;
        D_800814A0 = global_flags | 0x8000;
    }
}
