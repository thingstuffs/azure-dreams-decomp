#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_80172F14_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172F14_1;   /* arg0 in func_80172F14 */





extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_80170E54;
extern s32 D_80173CC4;

void func_80172F14(S_80172F14_1 *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, void *arg3)
{
    s16 timer;
    s32 direction;
    s32 limit;
    s32 value;
    s32 *state;

    direction = (((Rec_D_800E3D7C *)arg3)->unk_6A.as_u16 >> 9) & 7;

    switch (arg0->unk_9B) {
    case 0:
        func_800AD4D0(arg3);
        arg1->unk_0C.as_s32 =
            *(s16 *)((u8 *)&D_8006CCD8 + direction * 2) << 19;
        arg1->unk_10.at00_s32.v =
            *(s16 *)((u8 *)&D_8006CCE8 + direction * 2) << 19;
        arg0->unk_9B++;

        if (((Rec_D_800E3D7C *)arg3)->unk_28 == 0) {
            arg1->unk_14.as_s32 = 0;
            arg1->unk_10.at00_s32.v = 0;
            arg1->unk_0C.as_s32 = 0;
            func_800AAA54(arg0, arg1, arg2, &D_80173CC4);
            return;
        }
        if (arg2->unk_14.at00_u16.v & 0x8000) {
            arg0->unk_96.s = 0;
            arg0->unk_9B = 2;
            return;
        }

        timer = 5;
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x228) {
            timer = 8;
        }
        arg0->unk_96.s = timer;

        {
            s32 velocity = arg1->unk_0C.as_s32;
            arg1->unk_0C.as_s32 = velocity - velocity / 4;
        }
        {
            s32 velocity = arg1->unk_10.at00_s32.v;
            arg1->unk_10.at00_s32.v = velocity - velocity / 4;
        }
        /* fall through */

    case 1:
        limit = 0x7FFF;
        {
            s32 velocity = arg1->unk_0C.as_s32;
            s32 magnitude = velocity;

            if (magnitude < 0) {
                ASM_KEEP(magnitude);   /* MATCH pin: retail register colouring depends on it */
                magnitude = 0 - magnitude;
            }
            if (limit < magnitude) {
                arg1->unk_0C.as_s32 = velocity -
                    (*(s16 *)((u8 *)&D_8006CCD8 + direction * 2) << 15);
            }
        }
        {
            s32 velocity = arg1->unk_10.at00_s32.v;
            s32 magnitude = velocity;

            if (magnitude < 0) {
                ASM_KEEP(magnitude);   /* MATCH pin: retail register colouring depends on it */
                magnitude = 0 - magnitude;
            }
            if (limit < magnitude) {
                arg1->unk_10.at00_s32.v = velocity -
                    (*(s16 *)((u8 *)&D_8006CCE8 + direction * 2) << 15);
            }
        }
        ASM_KEEP(direction);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

        if (arg0->unk_96.s > 0) {
            arg0->unk_96.s = arg0->unk_96.u - 1;
            goto check_timer;
        }
        if (arg2->unk_14.at00_u16.v & 0x6000) {
            arg0->unk_96.s = 0;
        }

        if (((Rec_D_800E3D7C *)arg3)->unk_28 != 0) {
            {
                s32 coord = arg2->unk_24 << 6;
                s32 current = arg1->unk_00.at02_s16.v - 0x20;

                arg1->unk_0C.as_s32 = (coord - current) << 15;
            }
            {
                s32 coord = arg2->unk_25 << 6;
                s32 current = arg1->unk_04.at02_s16.v - 0x20;

                arg1->unk_10.at00_s32.v = (coord - current) << 15;
            }
        } else {
            arg1->unk_0C.as_s32 = 0;
            arg1->unk_10.at00_s32.v = 0;
        }

check_timer:
        if (arg0->unk_96.s != 0) {
            return;
        }
        if (((Rec_D_800E3D7C *)arg3)->unk_28 == 0) {
            arg1->unk_14.as_s32 = 0;
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
                s32 current = arg1->unk_00.at02_s16.v - 0x20;

                arg1->unk_0C.as_s32 = (coord - current) << 16;
            }
            {
                s32 coord = arg2->unk_25 << 6;
                s32 current = arg1->unk_04.at02_s16.v - 0x20;

                arg1->unk_10.at00_s32.v = (coord - current) << 16;
            }
        }

        timer = arg0->unk_96.u - 1;
        arg0->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        arg1->unk_14.as_s32 = 0;
        arg1->unk_10.at00_s32.v = 0;
        arg1->unk_0C.as_s32 = 0;
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
