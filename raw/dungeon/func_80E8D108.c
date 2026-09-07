#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct Node Node;

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern Node *D_800E3DE8[];
extern u8 D_801710F4[];
extern u8 D_80174F30;

void func_80172908(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;
    s32 one;
    s32 table_offset;
    s32 table_x;
    s32 table_y;
    u16 timer;

    table_offset = ((u16)FIELD(arg3, s16, 0x2A) >> 8) & 0xE;
    table_x = *(s16 *)((u8 *)&D_8006CCD8 + table_offset);
    table_y = *(s16 *)((u8 *)&D_8006CCE8 + table_offset);
    state = FIELD(arg0, u8, 0x9B);
    one = 1;
    if (state == one) {
        goto state_1;
    }
    if (!(state < 2)) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto state_0;
    }
    goto end;

state_ge_2:
    if (state == 2) {
        goto state_2;
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

    FIELD(arg2, u8 *, 0x2C) = &D_80174F30;
    func_80047784(arg2,
        *(&D_80174F30 +
          (((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7)),
        0);
    goto bump_state;

state_1:
    if ((FIELD(arg2, s8, 4) == state &&
         (FIELD(arg2, u16, 0x14) & 0x1000)) ||
        (FIELD(arg2, u16, 0x14) & 0x8000)) {
        func_800A56E0(0x808);
        FIELD(arg0, s32, 0x90) = 0;
        FIELD(arg0, u16, 0x98) |= 8;
        FIELD(arg1, s32, 0x14) = (s32)0xFFF50000;
        FIELD(arg0, u16, 0x96) = 4;
        FIELD(arg1, s32, 0x0C) = (table_x << 23) / 5;
        FIELD(arg1, s32, 0x10) = (table_y << 23) / 5;
        goto bump_state;
    }
    goto end;

bump_state:
    FIELD(arg0, u8, 0x9B)++;
    goto end;

state_2:
    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer;
    if ((s16)timer == 3) {
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
    }

    FIELD(arg1, s32, 0x14) += (5 - FIELD(arg0, s16, 0x96)) << 16;
    if (FIELD(arg0, s16, 0x96) < 3) {
        FIELD(arg1, s32, 0x14) = 0;
    }
    FIELD(arg1, s32, 0x0C) -= (FIELD(arg1, s32, 0x0C) << 2) / 5;
    FIELD(arg1, s32, 0x10) -= (FIELD(arg1, s32, 0x10) << 2) / 5;
    if (FIELD(arg0, s16, 0x96) > 0) {
        goto end;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg0, u8, 0x9B) = 0xFF;
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    goto end;

state_ff:
    {
        s32 coord = FIELD(arg2, u8, 0x24) << 6;
        s32 current = FIELD(arg1, s16, 2) - 0x20;

        FIELD(arg1, s32, 0x0C) = (coord - current) << 14;
    }
    {
        s32 coord = FIELD(arg2, u8, 0x25) << 6;
        s32 current = FIELD(arg1, s16, 6) - 0x20;

        FIELD(arg1, s32, 0x10) = (coord - current) << 14;
    }
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto end;
    }
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    func_800AD594(arg3, 0x100);
    FIELD(arg0, u8 *, 0x8C) = D_801710F4;
    D_8008346C = 0;
    func_800A4ACC(arg3);
    if (FIELD(arg3, s8, 0x6D) == 0) {
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
    } else {
        D_800E3DE8[0] = (Node *)((u8 *)arg3 - 0x20);
    }
end:
    return;
}
