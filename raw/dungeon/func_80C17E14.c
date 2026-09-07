#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_800A2FE0();
M2C_UNK func_800A32A4();
M2C_UNK func_800A56E0();
M2C_UNK func_800ACF88();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_800814A0;
extern s32 D_80083460;
extern s16 D_8008346A;

void func_80173614(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 table_offset;
    s32 table_x;
    s32 table_y;
    s32 state;

    table_offset = (FIELD(arg3, u16 *, 0x6A) >> 8) & 0xE;
    table_x = *(s16 *)((u8 *)&D_8006CCD8 + table_offset);
    table_y = *(s16 *)((u8 *)&D_8006CCE8 + table_offset);
    state = FIELD(arg0, u8 *, 0x9B);

    if (state == 1) {
        goto state_1;
    }
    if (state >= 2) {
        goto high_states;
    }
    if (state == 0) {
        goto state_0;
    }
    goto done;

high_states:
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto done;

state_0:
    FIELD(arg1, s32 *, 0xC) = table_x << 16;
    FIELD(arg1, s32 *, 0x10) = table_y << 16;
    FIELD(arg1, s32 *, 0x14) = 0x8000;
    if (D_8008346A != 0) {
        goto done;
    }
    FIELD(arg0, u8 *, 0x9B) = FIELD(arg0, u8 *, 0x9B) + 1;

state_1:
    {
        s32 flags14;
        u32 flags;
        u32 mask_a0;
        u32 mask_v1;
        u16 field98;

        flags14 = FIELD(arg3, s32 *, 0x14);
        if (!(flags14 & 0x4000)) {
            goto flags_done;
        }
        if (flags14 & 0x20000000) {
            goto flags_done;
        }
        func_800ACF88(arg3);
flags_done:
        func_800A56E0(0x805);

        mask_a0 = 0xF7FFFFFF;
        field98 = FIELD(arg0, u16 *, 0x98);
        mask_v1 = 0xFFFBFFFF;
        field98 |= 8;
        FIELD(arg0, u16 *, 0x98) = field98;
        flags = FIELD(arg3, u32 *, 0x1C);
        flags &= mask_a0;
        flags &= mask_v1;
        FIELD(arg3, u32 *, 0x1C) = flags;
        FIELD(arg2, s16 *, 0x10) = 0x60;
        FIELD(arg2, u16 *, 0x12) = 0xFF80;
        FIELD(arg2, u16 *, 0x14) |= 0xC;
        FIELD(arg0, u8 *, 0x9B) = FIELD(arg0, u8 *, 0x9B) + 1;
        goto done;
    }

state_2:
    if (!(FIELD(arg2, u16 *, 0x14) & 0x6000)) {
        goto done;
    }
    FIELD(arg0, u16 *, 0x96) = 0x80;
    FIELD(arg0, u8 *, 0x9B) = FIELD(arg0, u8 *, 0x9B) + 1;
    goto done;

state_3:
    {
        s32 call_a2;
        u32 flags;
        u32 sound_x;
        u32 sound_y;
        u16 value;
        u8 byte;
        s32 *global_ptr;

        FIELD(arg3, u32 *, 0x1C) |= 0x10000000;
        byte = FIELD(arg0, u8 *, 0x96);
        FIELD(arg2, u8 *, 0xE) = byte;
        FIELD(arg2, u8 *, 0xD) = byte;
        FIELD(arg2, u8 *, 0xC) = byte;
        value = FIELD(arg0, u16 *, 0x96) - 0x10;
        FIELD(arg0, u16 *, 0x96) = value;
        if ((s16)value >= 0x10) {
            goto done;
        }

        global_ptr = &D_80083460;
        if (FIELD(global_ptr, s32 *, 0x10) == (s32)((u8 *)arg3 - 0x20)) {
            FIELD(global_ptr, s32 *, 0x10) &= 0x7FFFFFFF;
        }
        func_800A2FE0(arg3);
        func_800A32A4(arg3);

        flags = FIELD(arg3, u32 *, 0x1C);
        sound_x = FIELD(arg2, u8 *, 0x24);
        sound_y = FIELD(arg2, u8 *, 0x25);
        call_a2 = 0x3000;
        if (flags & 0x2000) {
            call_a2 = 0x300;
        }
        func_8009A3D0(sound_x, sound_y, call_a2);
        func_8009A028(arg3);
        FIELD(arg3, u16 *, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

done:
    return;
}
