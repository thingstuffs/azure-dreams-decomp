#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

extern void func_800A2B04(void *, u8, u8);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_80171094;
extern u8 D_801764B0;

void func_80173770(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s16 timer;
    s32 value;
    s32 value2;
    s32 adjusted;
    s32 state;
    s32 countdown;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_1;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    return;

state_0:
    func_800AD4D0(arg3);
    FIELD(arg1, s32, 0xC) =
        *(s16 *)((u8 *)&D_8006CCD8 +
            ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 19;
    FIELD(arg1, s32, 0x10) =
        *(s16 *)((u8 *)&D_8006CCE8 +
            ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 19;
    FIELD(arg0, u8, 0x9B)++;

    if (FIELD(arg3, u8, 0x28) == 0) {
        goto reset_motion;
    }
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, s16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B) = 2;
        return;
    }
    timer = -1;
    if (FIELD(arg3, s32, 0x1C) & 0x228) {
        timer = 8;
    }
    FIELD(arg0, s16, 0x96) = timer;

state_1:
    value = FIELD(arg1, s32, 0xC);
    adjusted = value;
    if (value < 0) {
        adjusted = value + 3;
    }
    value2 = FIELD(arg1, s32, 0x10);
    FIELD(arg1, s32, 0xC) = value - (adjusted >> 2);

    adjusted = value2;
    if (value2 < 0) {
        adjusted = value2 + 3;
    }
    FIELD(arg1, s32, 0x10) = value2 - (adjusted >> 2);

    if (FIELD(arg0, s16, 0x96) > 0) {
        FIELD(arg0, u16, 0x96) = FIELD(arg0, u16, 0x96) - 1;
    } else if (FIELD(arg2, u16, 0x14) & 0x6000) {
        FIELD(arg0, s16, 0x96) = 0;
    }

    if (FIELD(arg0, s16, 0x96) != 0) {
        return;
    }
    if (FIELD(arg3, u8, 0x28) != 0) {
        goto increment_state;
    }

reset_motion:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800AAA54(arg0, arg1, arg2, &D_801764B0);
    return;

increment_state:
    FIELD(arg0, s16, 0x96) = 8;
    FIELD(arg0, u8, 0x9B)++;
    return;

state_2:
    timer = FIELD(arg0, s16, 0x96);
    if (timer > 0) {
        s32 coord;
        s32 current;

        coord = FIELD(arg2, u8, 0x24) << 6;
        current = FIELD(arg1, s16, 2);
        current -= 0x20;
        FIELD(arg1, s32, 0xC) = ((coord - current) << 16) / timer;

        current = FIELD(arg1, s16, 6);
        current -= 0x20;
        coord = FIELD(arg2, u8, 0x25) << 6;
        FIELD(arg1, s32, 0x10) =
            ((coord - current) << 16) / FIELD(arg0, s16, 0x96);
    }

    countdown = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, volatile s16, 0x96) = countdown;
    if ((countdown << 16) > 0) {
        return;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24),
        FIELD(arg2, u8, 0x25));
    {
        s32 *global;

        global = &D_80083460;
        value = global[4];
        if (value == (s32)((u8 *)arg3 - 0x20)) {
            global[4] = value & 0x7FFFFFFF;
        }
    }
    FIELD(arg0, void *, 0x8C) = &D_80171094;
}
