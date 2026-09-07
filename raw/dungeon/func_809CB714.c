#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_80170E54;
extern s32 D_80173CC4;

void func_80172F14(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s16 timer;
    s32 direction;
    s32 limit;
    s32 value;
    s32 *state;

    direction = (FIELD(arg3, u16, 0x6A) >> 9) & 7;

    switch (FIELD(arg0, u8, 0x9B)) {
    case 0:
        func_800AD4D0(arg3);
        FIELD(arg1, s32, 0x0C) =
            *(s16 *)((u8 *)&D_8006CCD8 + direction * 2) << 19;
        FIELD(arg1, s32, 0x10) =
            *(s16 *)((u8 *)&D_8006CCE8 + direction * 2) << 19;
        FIELD(arg0, u8, 0x9B)++;

        if (FIELD(arg3, u8, 0x28) == 0) {
            FIELD(arg1, s32, 0x14) = 0;
            FIELD(arg1, s32, 0x10) = 0;
            FIELD(arg1, s32, 0x0C) = 0;
            func_800AAA54(arg0, arg1, arg2, &D_80173CC4);
            return;
        }
        if (FIELD(arg2, u16, 0x14) & 0x8000) {
            FIELD(arg0, s16, 0x96) = 0;
            FIELD(arg0, u8, 0x9B) = 2;
            return;
        }

        timer = 5;
        if (FIELD(arg3, s32, 0x1C) & 0x228) {
            timer = 8;
        }
        FIELD(arg0, s16, 0x96) = timer;

        {
            s32 velocity = FIELD(arg1, s32, 0x0C);
            FIELD(arg1, s32, 0x0C) = velocity - velocity / 4;
        }
        {
            s32 velocity = FIELD(arg1, s32, 0x10);
            FIELD(arg1, s32, 0x10) = velocity - velocity / 4;
        }
        /* fall through */

    case 1:
        limit = 0x7FFF;
        {
            s32 velocity = FIELD(arg1, s32, 0x0C);
            s32 magnitude = velocity;

            if (magnitude < 0) {
                ASM_KEEP(magnitude);
                magnitude = 0 - magnitude;
            }
            if (limit < magnitude) {
                FIELD(arg1, s32, 0x0C) = velocity -
                    (*(s16 *)((u8 *)&D_8006CCD8 + direction * 2) << 15);
            }
        }
        {
            s32 velocity = FIELD(arg1, s32, 0x10);
            s32 magnitude = velocity;

            if (magnitude < 0) {
                ASM_KEEP(magnitude);
                magnitude = 0 - magnitude;
            }
            if (limit < magnitude) {
                FIELD(arg1, s32, 0x10) = velocity -
                    (*(s16 *)((u8 *)&D_8006CCE8 + direction * 2) << 15);
            }
        }
        ASM_KEEP(direction);

        if (FIELD(arg0, s16, 0x96) > 0) {
            FIELD(arg0, s16, 0x96) = FIELD(arg0, u16, 0x96) - 1;
            goto check_timer;
        }
        if (FIELD(arg2, u16, 0x14) & 0x6000) {
            FIELD(arg0, s16, 0x96) = 0;
        }

        if (FIELD(arg3, u8, 0x28) != 0) {
            {
                s32 coord = FIELD(arg2, u8, 0x24) << 6;
                s32 current = FIELD(arg1, s16, 2) - 0x20;

                FIELD(arg1, s32, 0x0C) = (coord - current) << 15;
            }
            {
                s32 coord = FIELD(arg2, u8, 0x25) << 6;
                s32 current = FIELD(arg1, s16, 6) - 0x20;

                FIELD(arg1, s32, 0x10) = (coord - current) << 15;
            }
        } else {
            FIELD(arg1, s32, 0x0C) = 0;
            FIELD(arg1, s32, 0x10) = 0;
        }

check_timer:
        if (FIELD(arg0, s16, 0x96) != 0) {
            return;
        }
        if (FIELD(arg3, u8, 0x28) == 0) {
            FIELD(arg1, s32, 0x14) = 0;
            func_800AAA54(arg0, arg1, arg2, &D_80173CC4);
            return;
        }
        FIELD(arg0, s16, 0x96) = 8;
        FIELD(arg0, u8, 0x9B)++;
        return;

    case 2:
        if (FIELD(arg0, s16, 0x96) != 0) {
            {
                s32 coord = FIELD(arg2, u8, 0x24) << 6;
                s32 current = FIELD(arg1, s16, 2) - 0x20;

                FIELD(arg1, s32, 0x0C) = (coord - current) << 16;
            }
            {
                s32 coord = FIELD(arg2, u8, 0x25) << 6;
                s32 current = FIELD(arg1, s16, 6) - 0x20;

                FIELD(arg1, s32, 0x10) = (coord - current) << 16;
            }
        }

        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, s16, 0x96) = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24),
                      FIELD(arg2, u8, 0x25));

        state = &D_80083460;
        value = state[4];
        if (value == (s32)((u8 *)arg3 - 0x20)) {
            state[4] = value & 0x7FFFFFFF;
        }
        FIELD(arg0, void *, 0x8C) = &D_80170E54;
        return;

    default:
        return;
    }
}

/* MECHANISM: A 40-byte frame holds arg0/arg1/direction/arg2/arg3 in s1/s0/s2/s3/s4.
   The positive-timer arm rejoins check_timer instead of returning directly.
   Last-use keeps fix direction coloring and preserve the two v0 copy/negate idioms. */
