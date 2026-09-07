#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, u8, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern u8 D_80170E7C;
extern u8 D_80174D7C;
extern u8 D_80174D84;
extern u8 D_80174D8C;

void func_80172664(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 table_x;
    s32 table_y;
    s32 table_offset;
    s32 state;
    register s32 next_state ASM_REG("$2");

    table_offset = ((u16)FIELD(arg3, s16, 0x2A) >> 8) & 0xE;
    table_x = *(s16 *)((u8 *)&D_8006CCD8 + table_offset);
    table_y = *(s16 *)((u8 *)&D_8006CCE8 + table_offset);
    FIELD(arg0, u16, 0x96)--;
    state = FIELD(arg0, u8, 0x9B);

    if (state == 2) {
        goto state_2;
    }
    if ((s32)state < 3) {
        if (state == 0) {
            goto state_0;
        }
        if (state == 1) {
            goto state_1;
        }
        goto end;
    }
    if (state == 4) {
        goto state_4;
    }
    if ((s32)state < 4) {
        goto state_3;
    }
    if (state == 0xFF) {
        goto state_ff;
    }
    goto end;

state_0:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 0xFF;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        goto end;
    }

    FIELD(arg2, u8 *, 0x2C) = &D_80174D7C;
    func_80047784(
        arg2,
        *(&D_80174D7C +
          (((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7)),
        0);
    {
        s32 shifted_x = table_x << 19;
        FIELD(arg1, s32, 0x0C) = (table_x << 17) - shifted_x;
    }
    {
        s32 shifted_y = table_y << 19;
        FIELD(arg1, s32, 0x10) = (table_y << 17) - shifted_y;
    }
    FIELD(arg0, u16, 0x98) |= 8;
    FIELD(arg3, s32, 0x1C) &= 0xF7FFFFFF;
    FIELD(arg0, u16, 0x96) = 4;
    FIELD(arg1, s32, 0x14) = (s32)0xFFFC0000;
    goto increment_state;

state_1:
    FIELD(arg0, s32, 0x90) += FIELD(arg1, s32, 0x14);
    FIELD(arg1, s32, 0x14) += FIELD(arg1, s32, 0x14) >> 2;
    if (FIELD(arg0, s16, 0x96) > 0) {
        goto end;
    }

    FIELD(arg2, u8 *, 0x2C) = &D_80174D84;
    func_80047784(
        arg2,
        *(&D_80174D84 +
          (((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7)),
        0);
    next_state = FIELD(arg0, u8, 0x9B);
    FIELD(arg0, u16, 0x96) = 8;
    goto increment_loaded_state;

state_2:
    {
        s32 value_x = FIELD(arg1, s32, 0x0C);
        s32 value_y = FIELD(arg1, s32, 0x10);
        s32 value_z = FIELD(arg1, s32, 0x14);

        FIELD(arg1, s32, 0x0C) = value_x - (value_x >> 3);
        FIELD(arg1, s32, 0x10) = value_y - (value_y >> 3);
        FIELD(arg1, s32, 0x14) = value_z - (value_z >> 3);
    }
    if (FIELD(arg0, s16, 0x96) == 4) {
        FIELD(arg1, s32, 0x0C) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x14) = 0;
    }
    if (FIELD(arg0, s16, 0x96) > 0) {
        goto end;
    }
    FIELD(arg0, u16, 0x96) = 4;
    FIELD(arg1, s32, 0x0C) = table_x << 18;
    FIELD(arg1, s32, 0x10) = table_y << 18;
    func_800A56E0(0x809);
    goto increment_state;

state_3:
    FIELD(arg0, s32, 0x90) += 0xC0000;
    FIELD(arg1, s32, 0x0C) += table_x << 18;
    FIELD(arg1, s32, 0x10) += table_y << 18;
    if (FIELD(arg0, s16, 0x96) > 0) {
        goto end;
    }
    func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);

increment_state:
    next_state = FIELD(arg0, u8, 0x9B);
increment_loaded_state:
    ASM_USE(next_state);
    FIELD(arg0, u8, 0x9B) = next_state + 1;
    goto end;

state_4:
    FIELD(arg0, s32, 0x90) += 0xC0000;
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto end;
    }
    FIELD(arg2, u8 *, 0x2C) = &D_80174D8C;
    func_80047784(
        arg2,
        *(&D_80174D8C +
          (((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7)),
        0);
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg0, s32, 0x90) = 0;
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    FIELD(arg3, s32, 0x1C) |= 0x08000000;
    FIELD(arg0, u8, 0x9B) = 0xFF;
    goto end;

state_ff:
    {
        s32 coord = FIELD(arg2, u8, 0x24) << 6;
        s32 current = FIELD(arg1, s16, 2) - 0x20;
        FIELD(arg1, s32, 0x0C) = ((coord - current) << 15) >> 1;
    }
    {
        s32 coord = FIELD(arg2, u8, 0x25) << 6;
        s32 current = FIELD(arg1, s16, 6) - 0x20;
        FIELD(arg1, s32, 0x10) = ((coord - current) << 15) >> 1;
    }
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto end;
    }
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    func_800AD594(arg3, 0x100);
    FIELD(arg0, u8 *, 0x8C) = &D_80170E7C;
    D_8008346C = 0;
    func_800A4ACC(arg3);
    if (FIELD(arg3, s8, 0x6D) == 0) {
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
    } else {
        D_800E3DE8 = (u8 *)arg3 - 0x20;
    }

end:
    return;
}
