#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80158E7C;
extern u8 D_8015CC44[];
extern u8 D_8015CC74[];

void func_8015B234(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;
    s16 timer;
    s32 value;
    s32 *global;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    goto done;

state_zero:
    func_800AD4D0(arg3);
    FIELD(arg1, s32, 0xC) =
        -((s16 *)&D_8006CCD8)[(FIELD(arg3, u16, 0x6A) >> 9) & 7] << 15;
    FIELD(arg1, s32, 0x10) =
        -((s16 *)&D_8006CCE8)[(FIELD(arg3, u16, 0x6A) >> 9) & 7] << 15;
    FIELD(arg0, u8, 0x9B)++;

    if (FIELD(arg3, u8, 0x28) == 0) {
        goto stop_motion;
    }
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, s16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B) = 3;
        goto done;
    }

    if (FIELD(arg3, u32, 0x1C) & 0x228) {
        timer = 8;
    } else {
        timer = -1;
    }
    FIELD(arg0, s16, 0x96) = timer;

    FIELD(arg1, s32, 0xC) -= FIELD(arg1, s32, 0xC) / 4;
    FIELD(arg1, s32, 0x10) -= FIELD(arg1, s32, 0x10) / 4;

state_one:
    FIELD(arg1, s32, 0xC) +=
        ((s16 *)&D_8006CCD8)[(FIELD(arg3, u16, 0x6A) >> 9) & 7] << 14;
    FIELD(arg1, s32, 0x10) +=
        ((s16 *)&D_8006CCE8)[(FIELD(arg3, u16, 0x6A) >> 9) & 7] << 14;

    if (FIELD(arg0, s16, 0x96) > 0) {
        FIELD(arg0, s16, 0x96) = FIELD(arg0, u16, 0x96) - 1;
    } else if (FIELD(arg2, u16, 0x14) & 0x6000) {
        FIELD(arg0, s16, 0x96) = 0;
    }

    if (FIELD(arg0, s16, 0x96) != 0) {
        goto done;
    }
    if (FIELD(arg3, u8, 0x28) != 0) {
        goto continue_state_one;
    }

stop_motion:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800AAA54(arg0, arg1, arg2, D_8015CC74);
    goto done;

continue_state_one:
    FIELD(arg2, u8 *, 0x2C) = D_8015CC44;
    func_80047784(
        arg2,
        D_8015CC44[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_two:
    FIELD(arg1, s32, 0xC) +=
        ((s16 *)&D_8006CCD8)[(FIELD(arg3, u16, 0x6A) >> 9) & 7] << 14;
    FIELD(arg1, s32, 0x10) +=
        ((s16 *)&D_8006CCE8)[(FIELD(arg3, u16, 0x6A) >> 9) & 7] << 14;
    if (!(FIELD(arg2, u16, 0x14) & 0x6000)) {
        goto done;
    }

    FIELD(arg2, u8 *, 0x2C) = D_8015CC44;
    func_80047784(
        arg2,
        D_8015CC44[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, s16, 0x96) = 8;
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_three:
    timer = FIELD(arg0, s16, 0x96);
    if (timer != 0) {
        {
            s32 coord = FIELD(arg2, u8, 0x24) << 6;
            s32 current = FIELD(arg1, s16, 2) - 0x20;
            FIELD(arg1, s32, 0xC) = ((coord - current) << 15) / timer;
        }
        {
            s32 coord = FIELD(arg2, u8, 0x25) << 6;
            s32 current = FIELD(arg1, s16, 6) - 0x20;
            FIELD(arg1, s32, 0x10) =
                ((coord - current) << 15) / FIELD(arg0, s16, 0x96);
        }
    }

    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, s16, 0x96) = timer;
    if ((s32)(timer << 16) > 0) {
        goto done;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    FIELD(arg1, s32, 0) = ((FIELD(arg2, u8, 0x24) << 6) + 0x20) << 16;
    FIELD(arg1, s32, 4) = ((FIELD(arg2, u8, 0x25) << 6) + 0x20) << 16;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));

    global = &D_80083460;
    value = global[4];
    if (value == (s32)((u8 *)arg3 - 0x20)) {
        global[4] = value & 0x7FFFFFFF;
    }
    FIELD(arg0, u8 *, 0x8C) = &D_80158E7C;

done:
    return;
}
