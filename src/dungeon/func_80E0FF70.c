#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80173770_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; volatile s16 p; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173770_0;   /* arg0 in func_80173770 */






extern void func_800A2B04(void *, u8, u8);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_80171094;
extern u8 D_801764B0;

void func_80173770(S_80173770_0 *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, void *arg3)
{
    s16 timer;
    s32 value;
    s32 value2;
    s32 adjusted;
    s32 state;
    s32 countdown;

    state = arg0->unk_9B;
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
    arg1->unk_0C.as_s32 =
        *(s16 *)((u8 *)&D_8006CCD8 +
            ((((Rec_D_800E3D7C *)arg3)->unk_6A.as_u16 >> 8) & 0xE)) << 19;
    arg1->unk_10.at00_s32.v =
        *(s16 *)((u8 *)&D_8006CCE8 +
            ((((Rec_D_800E3D7C *)arg3)->unk_6A.as_u16 >> 8) & 0xE)) << 19;
    arg0->unk_9B++;

    if (((Rec_D_800E3D7C *)arg3)->unk_28 == 0) {
        goto reset_motion;
    }
    if (arg2->unk_14.at00_u16.v & 0x8000) {
        arg0->unk_96.s = 0;
        arg0->unk_9B = 2;
        return;
    }
    timer = -1;
    if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x228) {
        timer = 8;
    }
    arg0->unk_96.s = timer;

state_1:
    value = arg1->unk_0C.as_s32;
    adjusted = value;
    if (value < 0) {
        adjusted = value + 3;
    }
    value2 = arg1->unk_10.at00_s32.v;
    arg1->unk_0C.as_s32 = value - (adjusted >> 2);

    adjusted = value2;
    if (value2 < 0) {
        adjusted = value2 + 3;
    }
    arg1->unk_10.at00_s32.v = value2 - (adjusted >> 2);

    if (arg0->unk_96.s > 0) {
        arg0->unk_96.u = arg0->unk_96.u - 1;
    } else if (arg2->unk_14.at00_u16.v & 0x6000) {
        arg0->unk_96.s = 0;
    }

    if (arg0->unk_96.s != 0) {
        return;
    }
    if (((Rec_D_800E3D7C *)arg3)->unk_28 != 0) {
        goto increment_state;
    }

reset_motion:
    arg1->unk_14.as_s32 = 0;
    arg1->unk_10.at00_s32.v = 0;
    arg1->unk_0C.as_s32 = 0;
    func_800AAA54(arg0, arg1, arg2, &D_801764B0);
    return;

increment_state:
    arg0->unk_96.s = 8;
    arg0->unk_9B++;
    return;

state_2:
    timer = arg0->unk_96.s;
    if (timer > 0) {
        s32 coord;
        s32 current;

        coord = arg2->unk_24 << 6;
        current = arg1->unk_00.at02_s16.v;
        current -= 0x20;
        arg1->unk_0C.as_s32 = ((coord - current) << 16) / timer;

        current = arg1->unk_04.at02_s16.v;
        current -= 0x20;
        coord = arg2->unk_25 << 6;
        arg1->unk_10.at00_s32.v =
            ((coord - current) << 16) / arg0->unk_96.s;
    }

    countdown = arg0->unk_96.u - 1;
    arg0->unk_96.p = countdown;
    if ((countdown << 16) > 0) {
        return;
    }

    arg1->unk_14.as_s32 = 0;
    arg1->unk_10.at00_s32.v = 0;
    arg1->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, arg2->unk_24,
        arg2->unk_25);
    {
        s32 *global;

        global = &D_80083460;
        value = global[4];
        if (value == (s32)((u8 *)arg3 - 0x20)) {
            global[4] = value & 0x7FFFFFFF;
        }
    }
    arg0->unk_8C = &D_80171094;
}
