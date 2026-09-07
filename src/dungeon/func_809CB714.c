#include "common.h"

typedef struct S_80172F14_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 pad_29[0x41];
    u16 unk_6A;
} S_80172F14_0;   /* arg3 in func_80172F14 */

typedef struct S_80172F14_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172F14_1;   /* arg0 in func_80172F14 */

typedef struct S_80172F14_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172F14_2;   /* arg1 in func_80172F14 */

typedef struct S_80172F14_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80172F14_3;   /* arg2 in func_80172F14 */



extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_80170E54;
extern s32 D_80173CC4;

void func_80172F14(S_80172F14_1 *arg0, S_80172F14_2 *arg1, S_80172F14_3 *arg2, void *arg3)
{
    s16 timer;
    s32 direction;
    s32 limit;
    s32 value;
    s32 *state;

    direction = (((S_80172F14_0 *)arg3)->unk_6A >> 9) & 7;

    switch (arg0->unk_9B) {
    case 0:
        func_800AD4D0(arg3);
        arg1->unk_0C =
            *(s16 *)((u8 *)&D_8006CCD8 + direction * 2) << 19;
        arg1->unk_10 =
            *(s16 *)((u8 *)&D_8006CCE8 + direction * 2) << 19;
        arg0->unk_9B++;

        if (((S_80172F14_0 *)arg3)->unk_28 == 0) {
            arg1->unk_14 = 0;
            arg1->unk_10 = 0;
            arg1->unk_0C = 0;
            func_800AAA54(arg0, arg1, arg2, &D_80173CC4);
            return;
        }
        if (arg2->unk_14 & 0x8000) {
            arg0->unk_96.s = 0;
            arg0->unk_9B = 2;
            return;
        }

        timer = 5;
        if (((S_80172F14_0 *)arg3)->unk_1C & 0x228) {
            timer = 8;
        }
        arg0->unk_96.s = timer;

        {
            s32 velocity = arg1->unk_0C;
            arg1->unk_0C = velocity - velocity / 4;
        }
        {
            s32 velocity = arg1->unk_10;
            arg1->unk_10 = velocity - velocity / 4;
        }
        /* fall through */

    case 1:
        limit = 0x7FFF;
        {
            s32 velocity = arg1->unk_0C;
            s32 magnitude = velocity;

            if (magnitude < 0) {
                ASM_KEEP(magnitude);   /* MATCH pin: retail register colouring depends on it */
                magnitude = 0 - magnitude;
            }
            if (limit < magnitude) {
                arg1->unk_0C = velocity -
                    (*(s16 *)((u8 *)&D_8006CCD8 + direction * 2) << 15);
            }
        }
        {
            s32 velocity = arg1->unk_10;
            s32 magnitude = velocity;

            if (magnitude < 0) {
                ASM_KEEP(magnitude);   /* MATCH pin: retail register colouring depends on it */
                magnitude = 0 - magnitude;
            }
            if (limit < magnitude) {
                arg1->unk_10 = velocity -
                    (*(s16 *)((u8 *)&D_8006CCE8 + direction * 2) << 15);
            }
        }
        ASM_KEEP(direction);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

        if (arg0->unk_96.s > 0) {
            arg0->unk_96.s = arg0->unk_96.u - 1;
            goto check_timer;
        }
        if (arg2->unk_14 & 0x6000) {
            arg0->unk_96.s = 0;
        }

        if (((S_80172F14_0 *)arg3)->unk_28 != 0) {
            {
                s32 coord = arg2->unk_24 << 6;
                s32 current = arg1->unk_02 - 0x20;

                arg1->unk_0C = (coord - current) << 15;
            }
            {
                s32 coord = arg2->unk_25 << 6;
                s32 current = arg1->unk_06 - 0x20;

                arg1->unk_10 = (coord - current) << 15;
            }
        } else {
            arg1->unk_0C = 0;
            arg1->unk_10 = 0;
        }

check_timer:
        if (arg0->unk_96.s != 0) {
            return;
        }
        if (((S_80172F14_0 *)arg3)->unk_28 == 0) {
            arg1->unk_14 = 0;
            func_800AAA54(arg0, arg1, arg2, &D_80173CC4);
            return;
        }
        arg0->unk_96.s = 8;
        arg0->unk_9B++;
        return;

    case 2:
        if (arg0->unk_96.s != 0) {
            {
                s32 coord = arg2->unk_24 << 6;
                s32 current = arg1->unk_02 - 0x20;

                arg1->unk_0C = (coord - current) << 16;
            }
            {
                s32 coord = arg2->unk_25 << 6;
                s32 current = arg1->unk_06 - 0x20;

                arg1->unk_10 = (coord - current) << 16;
            }
        }

        timer = arg0->unk_96.u - 1;
        arg0->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        arg1->unk_14 = 0;
        arg1->unk_10 = 0;
        arg1->unk_0C = 0;
        func_800A2B04(arg1, arg2->unk_24,
                      arg2->unk_25);

        state = &D_80083460;
        value = state[4];
        if (value == (s32)((u8 *)arg3 - 0x20)) {
            state[4] = value & 0x7FFFFFFF;
        }
        arg0->unk_8C = &D_80170E54;
        return;

    default:
        return;
    }
}

/* MECHANISM: A 40-byte frame holds arg0/arg1/direction/arg2/arg3 in s1/s0/s2/s3/s4.
   The positive-timer arm rejoins check_timer instead of returning directly.
   Last-use keeps fix direction coloring and preserve the two v0 copy/negate idioms. */
