#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_801730C4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
    s16 unk_A8;
    u8 pad_AA[0x6];
    u8 unk_B0;
} S_801730C4_0;   /* arg0 in func_801730C4 */


typedef struct S_801730C4_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801730C4_2;   /* arg3 in func_801730C4 */


typedef struct S_801730C4_4 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_801730C4_4;   /* global in func_801730C4 */



extern void func_80047784(void *, u8, s32);
extern s32 func_800644B8(s32);
extern s32 func_800A0818(u8, u8, u8, u8, void *);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);
extern void func_801708B8(void *, void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_800E23E0[];
extern u8 D_800E2458[];
extern u8 D_800E2460[];
extern u8 D_80171A80[];

void func_801730C4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 sp18;
    s32 state;

    state = ((S_801730C4_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if ((s32)state < 2) {
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
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000)) {
        goto done;
    }
    {
        u8 *model = D_800E2458;

        (*(u8 * *)((u8 *)arg2 + 0x2C)) = model;
        func_80047784(arg2,
            model[((D_80083228 + ((S_801730C4_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            1);
    }
    ((S_801730C4_0 *)arg0)->unk_98 |= 8;
    ((S_801730C4_2 *)arg3)->unk_1C.s &= 0xF7FFFFFF;
    ((S_801730C4_0 *)arg0)->unk_A8 = 5;
    ((S_801730C4_0 *)arg0)->unk_A4 = 0;
    ((S_801730C4_0 *)arg0)->unk_9B++;

state_one:
    {
        s32 initial_timer;
        s16 next_timer;

        initial_timer = ((S_801730C4_0 *)arg0)->unk_A8;
        ((S_801730C4_0 *)arg0)->unk_90.at00.v -= ((S_801730C4_0 *)arg0)->unk_A4;
        if (initial_timer != 0) {
            s32 delta;
            s32 position;

            delta = ((Rec_D_80082E80 *)arg2)->unk_24 << 6;
            position = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_s16.v;
            position -= 0x20;
            delta -= position;
            ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = (delta << 16) / initial_timer;

            position = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_s16.v;
            delta = ((Rec_D_80082E80 *)arg2)->unk_25 << 6;
            position -= 0x20;
            delta -= position;
            ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v =
                (delta << 16) / ((S_801730C4_0 *)arg0)->unk_A8;
            ((S_801730C4_0 *)arg0)->unk_A4 =
                -func_800644B8(((S_801730C4_0 *)arg0)->unk_A8 * 0x199) << 9;
        }

        ((S_801730C4_0 *)arg0)->unk_90.at00.v += ((S_801730C4_0 *)arg0)->unk_A4;
        next_timer = (u16)((S_801730C4_0 *)arg0)->unk_A8 - 1;
        ((S_801730C4_0 *)arg0)->unk_A8 = next_timer;
        if (next_timer >= 0) {
            goto state_two;
        }
    }
    ((S_801730C4_0 *)arg0)->unk_90.at02.v = -0x10;
    ((S_801730C4_0 *)arg0)->unk_98 &= 0xFFF7;
    ((S_801730C4_2 *)arg3)->unk_1C.s |= 0x08000000;
    ((S_801730C4_0 *)arg0)->unk_9B++;

state_two:
    if (!(((S_801730C4_2 *)arg3)->unk_1C.s & 0x08000000)) {
        goto done;
    }
    ((S_801730C4_0 *)arg0)->unk_98 &= 0xFFF7;
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    {
        u8 *model = D_800E2460;

        (*(u8 * *)((u8 *)arg2 + 0x2C)) = model;
        func_80047784(arg2,
            model[((D_80083228 + ((S_801730C4_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
    }
    ((S_801730C4_0 *)arg0)->unk_9B++;
    goto done;

state_three:
    {
        u8 *model = D_800E23E0;

        if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 == model) {
            goto done;
        }
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = model;
        func_80047784(arg2,
            model[((D_80083228 + ((S_801730C4_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
    }
    if (((S_801730C4_0 *)arg0)->unk_B0 != 0) {
        goto done;
    }
    func_801708B8(arg0, arg1, arg2);

done:
    {
        u16 timer;

        timer = ((S_801730C4_0 *)arg0)->unk_96 - 1;
        ((S_801730C4_0 *)arg0)->unk_96 = timer;
        if ((timer << 16) > 0) {
            return;
        }
    }

    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    func_800AD594(arg3, 0x10);
    func_800A4ACC(arg3);
    {
        u8 *global = (u8 *)&D_80083460;

        if (((S_801730C4_4 *)global)->unk_08 != 0) {
            ((S_801730C4_4 *)global)->unk_08 = (u16)((S_801730C4_4 *)global)->unk_08 - 1;
        }
    }
    {
        s32 flags = ((S_801730C4_2 *)arg3)->unk_1C.u;

        if (flags & 0x2000) {
            if (((S_801730C4_2 *)arg3)->unk_46 & 0x8000) {
                ((S_801730C4_2 *)arg3)->unk_46 &= 0x7FFF;
            }
            goto call_actor;
        }
        if (!(flags & 0x410)) {
            if (flags & 0x20000) {
                ((S_801730C4_2 *)arg3)->unk_2A = func_800A0818(
                    ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25,
                    D_80082E80[0x24], D_80082E80[0x25], &sp18);
            }
        }
    }

call_actor:
    if ((func_800AD9B4(arg2, arg3) << 16) <= 0) {
        return;
    }
    ((S_801730C4_0 *)arg0)->unk_8C = D_80171A80;
    func_800A9A04(arg3);
}
