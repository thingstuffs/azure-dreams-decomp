#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_80171728;
extern u8 D_80174DEC[];
extern u8 D_80174DFC[];
extern u8 D_80174E24[];

void func_80173964(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;
    s16 timer;
    u16 counter;
    u8 next_state;
    s32 ax;
    s32 dy;
    s32 ax2;
    s32 dy2;
    s32 global_value;
    s32 *global_base;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_1;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto done;

state_0:
    func_800AD4D0(arg3);
    FIELD(arg0, s16, 0x96) = 12;
    FIELD(arg0, u8, 0x9B)++;
    if (FIELD(arg3, u8, 0x28) == 0) {
        goto initialize;
    }
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, s16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B) = 3;
    }
    goto done;

state_1:
    counter = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = counter;
    timer = counter;
    if (timer >= 11) {
        FIELD(arg1, s32, 0x0C) =
            *(s16 *)((u8 *)&D_8006CCD8 +
                     ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 20;
        FIELD(arg1, s32, 0x10) =
            *(s16 *)((u8 *)&D_8006CCE8 +
                     ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 20;
        FIELD(arg2, u16, 0x14) |= 0x800;
        goto done;
    }
    if (timer >= 7) {
        FIELD(arg1, s32, 0x0C) /= 4;
        FIELD(arg1, s32, 0x10) /= 4;
        goto done;
    }
    if (timer >= 2) {
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        goto done;
    }
    if (timer == state) {
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        goto done;
    }
    if (timer != 0) {
        goto done;
    }
    next_state = FIELD(arg0, u8, 0x9B);
    timer = 4;
    FIELD(arg0, s16, 0x96) = timer;
    goto increment_state;

state_2:
    if (FIELD(arg3, u8, 0x28) != 0) {
        goto calculate;
    }

initialize:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800AAA54(arg0, arg1, arg2, D_80174E24);
    goto done;

calculate:
    timer = FIELD(arg0, s16, 0x96);
    if (timer != 0) {
        ax = FIELD(arg2, u8, 0x24) << 6;
        dy = FIELD(arg1, s16, 2) - 0x20;
        FIELD(arg1, s32, 0x0C) = ((ax - dy) << 16) / timer;
        ax2 = FIELD(arg2, u8, 0x25) << 6;
        dy2 = FIELD(arg1, s16, 6) - 0x20;
        FIELD(arg1, s32, 0x10) =
            ((ax2 - dy2) << 16) / FIELD(arg0, s16, 0x96);
    }
    counter = FIELD(arg0, u16, 0x96);
    FIELD(arg0, u16, 0x96) = counter - 1;
    if ((s32)(counter << 16) > 0) {
        goto done;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    next_state = FIELD(arg0, u8, 0x9B);

increment_state:
    FIELD(arg0, u8, 0x9B) = next_state + 1;
    goto done;

state_3:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    if (FIELD(arg2, void *, 0x2C) == D_80174DFC) {
        FIELD(arg2, void *, 0x2C) = D_80174DEC;
        func_80047784(
            arg2,
            D_80174DEC[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }
    global_base = &D_80083460;
    global_value = global_base[4];
    if (global_value == (s32)((u8 *)arg3 - 0x20)) {
        global_base[4] = global_value & 0x7FFFFFFF;
    }
    FIELD(arg0, void *, 0x8C) = &D_80171728;

done:
    return;
}

/* MECHANISM: Four live arguments naturally produce the 0x28 frame and s1/s0/s2/s3 save roles.
   A distinct u8 next_state plus timer-held constant 4 fixes v0/v1 lifetimes and the bgtz store slot.
   The named D_80083460 pointer forces retail's split lui/addiu base before the final field load. */
