#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"



typedef struct S_80172998_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
    s16 unk_A4;
} S_80172998_0;   /* arg0 in func_80172998 */





extern s32 func_800644B8(s32);
extern s32 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s32 D_80083460;
extern M2C_UNK D_80170E94;

void func_80172998(S_80172998_0 *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, Rec_D_800E3D7C *arg3)
{
    s32 scratch;
    s32 state;
    u32 flags;

    state = arg0->unk_9B;
    switch (state) {
    case 0:
        arg0->unk_98 |= 8;
        arg3->unk_1C.as_u32 &= 0xF7FFFFFF;
        arg0->unk_A4 = 7;
        arg0->unk_A0 = 0;
        arg0->unk_9B++;

    case 1:
        arg0->unk_90 -= arg0->unk_A0;
        if (arg0->unk_A4 != 0) {
            {
                s32 coord = arg2->unk_24 << 6;
                s32 current = arg1->unk_00.at02_s16.v - 32;

                arg1->unk_0C.as_s32 =
                    ((coord - current) << 16) / arg0->unk_A4;
            }
            {
                s32 coord = arg2->unk_25 << 6;
                s32 current = arg1->unk_04.at02_s16.v - 32;

                arg1->unk_10.at00_s32.v =
                    ((coord - current) << 16) / arg0->unk_A4;
            }
            arg0->unk_A0 =
                (-func_800644B8(arg0->unk_A4 * 292)) << 9;
        }

        arg0->unk_90 += arg0->unk_A0;
        arg3->unk_1C.as_u32 &= 0xF7FFFFFF;
        arg0->unk_A4--;
        if (arg0->unk_A4 >= 0) {
            goto phase_two;
        }

        arg0->unk_90 = 0;
        arg0->unk_98 &= 0xFFF7;
        arg3->unk_1C.as_u32 |= 0x08000000;
        arg0->unk_9B++;

    case 2:
phase_two:
    if (arg3->unk_1C.as_u32 & 0x08000000) {
        arg0->unk_98 &= 0xFFF7;
        arg1->unk_14.as_s32 = 0;
        arg1->unk_10.at00_s32.v = 0;
        arg1->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
        arg0->unk_9B++;
    }

    default:
        break;
    }

    arg0->unk_96--;
    if (arg0->unk_96 > 0) {
        return;
    }

    arg1->unk_14.as_s32 = 0;
    arg1->unk_10.at00_s32.v = 0;
    arg1->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
    func_800AD594(arg3, 5);
    func_800A4ACC(arg3);

    {
        s16 *counter = (s16 *)&D_80083460;

        if (counter[4] != 0) {
            ((u16 *)counter)[4]--;
        }
    }

    flags = arg3->unk_1C.as_u32;
    if (flags & 0x2000) {
        if (arg3->unk_44.at02_u16.v & 0x8000) {
            arg3->unk_44.at02_u16.v &= 0x7FFF;
        }
    } else {
        if (flags & 0x410) {
            goto actor_check;
        }
        if (!(flags & 0x20000)) {
            goto actor_check;
        }
        arg3->unk_2A.as_s16 = func_800A0818(
            arg2->unk_24, arg2->unk_25,
            D_80082E80[0x24], D_80082E80[0x25], &scratch);
    }

actor_check:
    if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
        arg0->unk_8C = &D_80170E94;
        func_800A9A04(arg3);
    }
}
