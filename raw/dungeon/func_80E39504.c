#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

extern void func_800A2B04(void *, u8, u8);
extern s32 func_800A6D30(void);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);
extern void func_8017516C(void *, void *, void *, void *);
extern void func_80176480(void *, void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_80170EE4[];
extern u8 D_80176640[];

void func_80172D04(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s16 timer;
    s32 value;
    s32 value2;
    s32 adjusted;
    s32 state;
    s32 random;
    s32 one;

    state = FIELD(arg0, u8, 0x9B);
    one = 1;
    if (state == one) {
        goto state_1;
    }
    if (state < 2) {
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
    func_80176480(arg1, arg2);
    func_800AD4D0(arg3);
    FIELD(arg1, s32, 0xC) =
        -*(s16 *)((u8 *)&D_8006CCD8 +
            ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 15;
    FIELD(arg1, s32, 0x10) =
        -*(s16 *)((u8 *)&D_8006CCE8 +
            ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 15;
    FIELD(arg0, u8, 0x9B)++;

    if (FIELD(arg3, u8, 0x28) == 0) {
        goto reset_motion;
    }
    random = func_800A6D30() & 3;
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        if (random == 0) {
            func_8017516C(arg0, arg1, arg2, arg3);
        }
        FIELD(arg0, s16, 0xA8) = -1;
        FIELD(arg0, s16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B) = 2;
        return;
    }
    timer = -1;
    if (FIELD(arg3, s32, 0x1C) & 0x228) {
        timer = 8;
    }
    FIELD(arg0, s16, 0x96) = timer;
    if (random != 0) {
        FIELD(arg0, s16, 0xA8) = -1;
        goto state_1;
    }
    FIELD(arg0, u16, 0xA8) = one;

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

    timer = FIELD(arg0, u16, 0xA8) - 1;
    FIELD(arg0, u16, 0xA8) = timer;
    if ((timer << 16) == 0) {
        func_8017516C(arg0, arg1, arg2, arg3);
    }

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
    func_800AAA54(arg0, arg1, arg2, D_80176640);
    return;

increment_state:
    FIELD(arg0, s16, 0x96) = 8;
    FIELD(arg0, u8, 0x9B)++;
    return;

state_2:
    timer = FIELD(arg0, s16, 0x96);
    if (timer != 0) {
        s32 sub, m;
        m = FIELD(arg2, u8, 0x24);
        m <<= 6;
        sub = FIELD(arg1, s16, 2) - 0x20;
        FIELD(arg1, s32, 0xC) = ((m - sub) << 15) / timer;
        sub = FIELD(arg1, s16, 6) - 0x20;
        FIELD(arg1, s32, 0x10) =
            (((FIELD(arg2, u8, 0x25) << 6) - sub) << 15) /
            FIELD(arg0, s16, 0x96);
    }

    timer = FIELD(arg0, u16, 0xA8) - 1;
    FIELD(arg0, u16, 0xA8) = timer;
    if ((timer << 16) == 0) {
        func_8017516C(arg0, arg1, arg2, arg3);
    }

    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, s16, 0x96) = timer;
    if ((timer << 16) > 0) {
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
        value = *(s32 *)((u8 *)global + 0x10);
        if (value == (s32)((u8 *)arg3 - 0x20)) {
            *(s32 *)((u8 *)global + 0x10) = value & 0x7FFFFFFF;
        }
    }
    FIELD(arg0, void *, 0x8C) = D_80170EE4;
}
