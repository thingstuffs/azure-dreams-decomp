#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_8017345C_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017345C_1;   /* arg0 in func_8017345C */




extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_80170E94;
extern u8 D_80174ABC[];


void func_8017345C(S_8017345C_1 *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, void *arg3)
{
    s16 timer;
    s32 value;
    s32 *state;
    s32 table_index;

    table_index = (((Rec_D_800E3D7C *)arg3)->unk_6A.as_u16 >> 9) & 7;

    switch (arg0->unk_9B) {
    case 0:
        func_800AD4D0(arg3);
        arg1->unk_0C.as_s32 = ((s16 *)&D_8006CCD8)[table_index] << 17;
        arg1->unk_10.at00_s32.v = ((s16 *)&D_8006CCE8)[table_index] << 17;
        arg0->unk_9B++;

        if (((Rec_D_800E3D7C *)arg3)->unk_28 == 0) {
            goto start_action;
        }
        if (arg2->unk_14.at00_u16.v & 0x8000) {
            arg0->unk_96.s = 0;
            arg0->unk_9B = 2;
            return;
        }
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        arg0->unk_96.s = timer;
        arg1->unk_0C.as_s32 -= arg1->unk_0C.as_s32 / 4;
        arg1->unk_10.at00_s32.v -= arg1->unk_10.at00_s32.v / 4;
        /* fall through */

    case 1:
        arg1->unk_0C.as_s32 -=
            ((s16 *)&D_8006CCD8)[table_index] << 14;
        arg1->unk_10.at00_s32.v -=
            ((s16 *)&D_8006CCE8)[table_index] << 14;
        if (arg0->unk_96.s > 0) {
            arg0->unk_96.s = arg0->unk_96.u - 1;
        } else if (arg2->unk_14.at00_u16.v & 0x6000) {
            arg0->unk_96.s = 0;
        }
        if (arg0->unk_96.s != 0) {
            return;
        }
        if (((Rec_D_800E3D7C *)arg3)->unk_28 != 0) {
            goto increment_state;
        }
        goto start_action;

start_action:
        arg1->unk_14.as_s32 = 0;
        arg1->unk_10.at00_s32.v = 0;
        arg1->unk_0C.as_s32 = 0;
        func_800AAA54(arg0, arg1, arg2, D_80174ABC);
        return;

increment_state:
        arg0->unk_96.s = 8;
        arg0->unk_9B++;
        return;

    case 2:
        timer = arg0->unk_96.s;
        if (timer != 0) {
            {
                s32 coord = arg2->unk_24 << 6;
                s32 current = arg1->unk_00.at02_s16.v - 0x20;
                arg1->unk_0C.as_s32 =
                    ((coord - current) << 15) / timer;
            }
            {
                s32 coord = arg2->unk_25 << 6;
                s32 current = arg1->unk_04.at02_s16.v - 0x20;
                arg1->unk_10.at00_s32.v =
                    ((coord - current) << 15) /
                    arg0->unk_96.s;
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
        arg0->unk_8C = &D_80170E94;
        return;

    default:
        return;
    }
}
