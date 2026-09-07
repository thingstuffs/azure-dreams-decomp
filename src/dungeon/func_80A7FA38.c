#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_80167238_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80167238_1;   /* arg0 in func_80167238 */

typedef struct S_80167238_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80167238_2;   /* arg1 in func_80167238 */




extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80164E54;
extern u8 D_80168150[];
extern u8 D_80168178[];

void func_80167238(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;
    s32 direction;
    s16 timer;
    s32 value;
    s32 *global;

    direction = (((Rec_D_800E3D7C *)arg3)->unk_6A.as_u16 >> 9) & 7;
    state = ((S_80167238_1 *)arg0)->unk_9B;
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
    ((S_80167238_2 *)arg1)->unk_0C = ((s16 *)&D_8006CCD8)[direction] << 18;
    ((S_80167238_2 *)arg1)->unk_10 = ((s16 *)&D_8006CCE8)[direction] << 18;
    ((S_80167238_1 *)arg0)->unk_9B++;

    if (((Rec_D_800E3D7C *)arg3)->unk_28 == 0) {
        goto stop_motion;
    }
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
        ((S_80167238_1 *)arg0)->unk_96.s = 0;
        ((S_80167238_1 *)arg0)->unk_9B = 3;
        goto done;
    }

    if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x228) {
        timer = 8;
    } else {
        timer = -1;
    }
    ((S_80167238_1 *)arg0)->unk_96.s = timer;

    ((S_80167238_2 *)arg1)->unk_0C -= ((S_80167238_2 *)arg1)->unk_0C / 4;
    ((S_80167238_2 *)arg1)->unk_10 -= ((S_80167238_2 *)arg1)->unk_10 / 4;

state_one:
    ((S_80167238_2 *)arg1)->unk_0C -= ((s16 *)&D_8006CCD8)[direction] << 14;
    ((S_80167238_2 *)arg1)->unk_10 -= ((s16 *)&D_8006CCE8)[direction] << 14;

    if (((S_80167238_1 *)arg0)->unk_96.s > 0) {
        ((S_80167238_1 *)arg0)->unk_96.s = ((S_80167238_1 *)arg0)->unk_96.u - 1;
    } else if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000) {
        ((S_80167238_1 *)arg0)->unk_96.s = 0;
    }

    if (((S_80167238_1 *)arg0)->unk_96.s != 0) {
        goto done;
    }
    if (((Rec_D_800E3D7C *)arg3)->unk_28 != 0) {
        goto continue_state_one;
    }

stop_motion:
    ((S_80167238_2 *)arg1)->unk_14 = 0;
    ((S_80167238_2 *)arg1)->unk_10 = 0;
    ((S_80167238_2 *)arg1)->unk_0C = 0;
    func_800AAA54(arg0, arg1, arg2, D_80168178);
    goto done;

continue_state_one:
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80168150;
    func_80047784(
        arg2,
        D_80168150[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    ((S_80167238_1 *)arg0)->unk_9B++;
    goto done;

state_two:
    ((S_80167238_2 *)arg1)->unk_0C -= ((s16 *)&D_8006CCD8)[direction] << 14;
    ((S_80167238_2 *)arg1)->unk_10 -= ((s16 *)&D_8006CCE8)[direction] << 14;
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000)) {
        goto done;
    }

    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80168150;
    func_80047784(
        arg2,
        D_80168150[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    ((S_80167238_1 *)arg0)->unk_96.s = 8;
    ((S_80167238_1 *)arg0)->unk_9B++;
    goto done;

state_three:
    timer = ((S_80167238_1 *)arg0)->unk_96.s;
    if (timer != 0) {
        {
            s32 coord = ((Rec_D_80082E80 *)arg2)->unk_24 << 6;
            s32 current = ((S_80167238_2 *)arg1)->unk_00.at02.v - 0x20;
            ((S_80167238_2 *)arg1)->unk_0C = ((coord - current) << 15) / timer;
        }
        {
            s32 coord = ((Rec_D_80082E80 *)arg2)->unk_25 << 6;
            s32 current = ((S_80167238_2 *)arg1)->unk_04.at02.v - 0x20;
            ((S_80167238_2 *)arg1)->unk_10 =
                ((coord - current) << 15) / ((S_80167238_1 *)arg0)->unk_96.s;
        }
    }

    timer = ((S_80167238_1 *)arg0)->unk_96.u - 1;
    ((S_80167238_1 *)arg0)->unk_96.s = timer;
    if ((s32)(timer << 16) > 0) {
        goto done;
    }

    ((S_80167238_2 *)arg1)->unk_14 = 0;
    ((S_80167238_2 *)arg1)->unk_10 = 0;
    ((S_80167238_2 *)arg1)->unk_0C = 0;
    ((S_80167238_2 *)arg1)->unk_00.at00.v = ((((Rec_D_80082E80 *)arg2)->unk_24 << 6) + 0x20) << 16;
    ((S_80167238_2 *)arg1)->unk_04.at00.v = ((((Rec_D_80082E80 *)arg2)->unk_25 << 6) + 0x20) << 16;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);

    global = &D_80083460;
    value = global[4];
    if (value == (s32)((u8 *)arg3 - 0x20)) {
        global[4] = value & 0x7FFFFFFF;
    }
    ((S_80167238_1 *)arg0)->unk_8C = &D_80164E54;

done:
    return;
}
