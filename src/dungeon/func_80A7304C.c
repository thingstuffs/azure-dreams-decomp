#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80047784();
extern void func_8009C12C();
extern void func_800A2B04();
extern void func_800A4ACC();
extern void func_800A56E0();
extern void func_800AD594();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228[];
extern s32 D_8008346C[];
extern void *D_800E3DE8[];
extern u8 D_80170E54;
extern u8 D_80174140;
extern u8 D_80174170;

void func_8017284C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s16 timer;
    s32 table_y;
    s32 index;
    s32 wrapped;
    s32 decay_x;
    s32 decay_y;
    s32 z_velocity;
    s32 scaled;
    s32 state_value;
    s32 state;
    register u8 increment_value ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state1;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state0;
        }
        goto done;
    }
    if (state == 2) {
        goto state2;
    }
    if (state == 3) {
        goto state3;
    }
    goto done;

state0:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 3;
        FIELD(arg0, s16, 0x96) = 0;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        goto done;
    }

    state_value = ((u16)FIELD(arg3, s16, 0x2A) >> 9) & 7;
    index = state_value + 4;
    wrapped = index;
    if (index < 0) {
        wrapped = state_value + 11;
    }
    index -= wrapped & 0x18;
    FIELD(arg1, s32, 0xC) =
        FIELD(&D_8006CCD8, s16, index * 2) * 0x60000;
    table_y = FIELD(&D_8006CCE8, s16, index * 2);
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = table_y * 0x60000;
    FIELD(arg2, void *, 0x2C) = &D_80174140;
    func_80047784(arg2,
        FIELD(&D_80174140, u8,
            ((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7),
        0);
    increment_value = FIELD(arg0, u8, 0x9B);
    FIELD(arg0, s16, 0x96) = 0;
    goto increment_state;

state1:
    decay_x = FIELD(arg1, s32, 0xC);
    decay_y = FIELD(arg1, s32, 0x10);
    FIELD(arg1, s32, 0xC) = decay_x - (decay_x >> 2);
    FIELD(arg1, s32, 0x10) = decay_y - (decay_y >> 2);
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        FIELD(arg2, void *, 0x2C) = &D_80174170;
        func_80047784(arg2,
            FIELD(&D_80174170, u8,
                ((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7),
            0);
        increment_value = FIELD(arg0, u8, 0x9B);
        FIELD(arg0, s16, 0x96) = 0x14;
        goto increment_state;
    }
    goto done;

state2:
    timer = FIELD(arg0, u16, 0x96) - 1;
    z_velocity = FIELD(arg1, s32, 0x14);
    FIELD(arg0, s16, 0x96) = timer;
    if (timer < 12) {
        z_velocity += 0x1400;
    } else {
        z_velocity += 0x20000;
    }
    FIELD(arg1, s32, 0x14) = z_velocity;
    FIELD(arg0, s32, 0x90) += z_velocity;

    if (FIELD(arg0, s16, 0x96) == 0x11) {
        func_800A56E0(0x808);
        index = ((u16)FIELD(arg3, s16, 0x2A) >> 9) & 7;
        scaled = FIELD(&D_8006CCD8, s16, index * 2) * 0x30000;
        FIELD(arg1, s32, 0xC) = scaled + (scaled >> 2);
        scaled = FIELD(&D_8006CCE8, s16, index * 2) * 0x30000;
        FIELD(arg1, s32, 0x10) = scaled + (scaled >> 2);
    }

    if (((FIELD(arg2, s8, 4) == 3) &&
         (FIELD(arg2, u16, 0x14) & 0x1000)) ||
        (FIELD(arg2, u16, 0x14) & 0x8000)) {
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
    }

    if (((FIELD(arg2, s8, 4) == 5) &&
         (FIELD(arg2, u16, 0x14) & 0x1000)) ||
        (FIELD(arg2, u16, 0x14) & 0x8000)) {
        FIELD(arg1, s32, 0xC) =
            ((((FIELD(arg2, u8, 0x24) << 6) + 0x20) << 16) -
             FIELD(arg1, s32, 0)) / FIELD(arg0, s16, 0x96);
        FIELD(arg1, s32, 0x10) =
            ((((FIELD(arg2, u8, 0x25) << 6) + 0x20) << 16) -
             FIELD(arg1, s32, 4)) / FIELD(arg0, s16, 0x96);
    }

    if ((FIELD(arg0, s16, 0x96) <= 0) ||
        (FIELD(arg2, u16, 0x14) & 0x8000)) {
        increment_value = FIELD(arg0, u8, 0x9B);
        goto increment_state;
    }
    goto done;

increment_state:
    increment_value++;
    FIELD(arg0, u8, 0x9B) = increment_value;
    goto done;

state3:
    if ((FIELD(arg0, s16, 0x96) <= 0) ||
        (FIELD(arg2, u16, 0x14) & 0x8000)) {
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        func_800AD594(arg3, 0x100);
        FIELD(arg0, void *, 0x8C) = &D_80170E54;
        D_8008346C[0] = 0;
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        func_800A4ACC(arg3);
        if (FIELD(arg3, s8, 0x6D) == 0) {
            FIELD(arg3, u16, 0x46) &= 0x7FFF;
            goto done;
        }
        D_800E3DE8[0] = (u8 *)arg3 - 0x20;
    }
    goto done;

done:
    return;
}
