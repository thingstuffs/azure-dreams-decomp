#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_8009A66C();
extern s16 func_800A0818();
extern s32 func_80173678();

extern s16 D_80083228;
extern u16 D_80083462;
extern s32 D_80175DC4;
extern s32 D_80175DCC;
extern s32 D_80175DD4;

void func_80172CC0(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    register void *state ASM_REG("$17") = arg3;
    s32 call_mode;
    register s32 result ASM_REG("$16");
    s16 step;
    s32 x;
    s32 y;
    s32 kind;
    s32 count;
    unsigned long table_index;
    u8 *selected;
    u8 *current;
    u8 *entry;

    if (FIELD(state, s8, 0x71) <= 0) {
        return;
    }
    count = FIELD(state, u8, 0x71);
    if (!(FIELD(state, s16, 0x8A) < count)) {
        return;
    }

    kind = FIELD(state, u8, 0x48);
    if (kind == 0xE) {
        goto kind_0e;
    }
    if ((s32)kind < 0xF) {
        if (kind == 0xD) {
            goto kind_0d;
        }
        goto setup;
    }
    if (kind == 0xF) {
        goto kind_0f;
    }
    goto setup;

kind_0d:
    current = FIELD(arg2, u8 *, 0x2C);
    selected = (u8 *)&D_80175DC4;
    goto selected_kind;

kind_0e:
    current = FIELD(arg2, u8 *, 0x2C);
    selected = (u8 *)&D_80175DCC;
    goto selected_kind;

kind_0f:
    current = FIELD(arg2, u8 *, 0x2C);
    selected = (u8 *)&D_80175DD4;

selected_kind:
    if (current != selected) {
        FIELD(arg2, u8 *, 0x2C) = selected;
        table_index =
            ((D_80083228 + FIELD(state, s16, 0x2A) + 0x100) >> 9) & 7;
        table_index += (unsigned long)selected;
        func_80047784(arg2, *(u8 *)table_index, 0);
    }

setup:
    call_mode = 0x3000;
    x = FIELD(arg2, u8, 0x24);
    y = FIELD(arg2, u8, 0x25);
    if (FIELD(state, s32, 0x1C) & 0x2000) {
        call_mode = 0x300;
    }
    func_8009A3D0(x, y, call_mode);

    step = func_800A0818(x, y,
        FIELD((u8 *)state + FIELD(state, s16, 0x8A), u8, 0x74),
        FIELD((u8 *)state + FIELD(state, s16, 0x8A), u8, 0x7C),
        (u8 *)arg0 + 0x98);
    result = (s16)func_8009A66C(step, arg2, state, 0x20);

    entry = (u8 *)state + FIELD(state, s16, 0x8A);
    FIELD(arg2, u8, 0x24) = FIELD(entry, u8, 0x74);
    call_mode = 0x3000;
    entry = (u8 *)state + FIELD(state, s16, 0x8A);
    FIELD(arg2, u8, 0x25) = FIELD(entry, u8, 0x7C);
    FIELD(state, u16, 0x8A)++;
    {
        s32 next_x = FIELD(arg2, u8, 0x24);
        s32 next_y = FIELD(arg2, u8, 0x25);

        if (FIELD(state, s32, 0x1C) & 0x2000) {
            call_mode = 0x300;
        }
        func_8009A21C(next_x, next_y, call_mode);
    }

    ASM_KEEP(result);
    FIELD(state, s16, 0x2A) = step;
    if (result == 3) {
        if (!(D_80083462 & 0x80) && !(FIELD(arg2, u16, 0x14) & 0x8000)) {
            func_80173678(arg0, arg1, arg2, state);
            FIELD(arg0, s32, 0x8C) = 0;
            goto finish_state;
        }
    }

    FIELD(arg0, u8, 0x9A) = 0xF;
    FIELD(arg0, s32, 0x8C) = 0;

finish_state:
    FIELD(state, s32, 0x1C) |= 0x40000000;
    if (D_80083462 & 0x80) {
        FIELD(arg0, s16, 0x96) = 0;
        return;
    }

    FIELD(arg0, s16, 0x96) = 8;
    x = FIELD(state, u8, 0x71);
    if (x > 0) {
        FIELD(arg0, s16, 0x96) = 8 / x;
    }
    ASM_KEEP(state);
}

/* MECHANISM: The 0x38 frame comes from the held s1 state and a guarded s0 signed result from the s16 callee.
   Scoped coordinate reloads and mode initialization reproduce the post-call schedule without the +4-word cascade.
   An unsigned-long index compound assignment selects retail's index+base addu operand order. */
