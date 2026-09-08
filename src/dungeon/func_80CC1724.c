#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80174F24_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    s32 unk_A0;
} S_80174F24_0;   /* arg0 in func_80174F24 */

typedef struct S_80174F24_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80174F24_1;   /* arg2 in func_80174F24 */


typedef struct S_80174F24_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174F24_3;   /* arg1 in func_80174F24 */



extern void func_80047784(void *, u8, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_80173B98;
extern u8 D_80176338[];
extern u8 D_80176340[];

void func_80174F24(void *arg0, void *in_arg1, void *in_arg2, void *arg3)
{
    register void *arg1 ASM_REG("$18") = in_arg1;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *arg2 ASM_REG("$19") = in_arg2;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 scratch;
    u8 state;

    state = ((S_80174F24_0 *)arg0)->unk_9B;
    switch (state) {
    case 0:
        if (((S_80174F24_1 *)arg2)->unk_14 & 0x6000) {
            u8 *table = D_80176338;

            (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
            func_80047784(arg2,
                table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
            ((S_80174F24_0 *)arg0)->unk_98 |= 8;
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 &= ~0x08000000;
            ((S_80174F24_0 *)arg0)->unk_9E.s = 5;
            ((S_80174F24_0 *)arg0)->unk_A0 = 0;
            ((S_80174F24_0 *)arg0)->unk_9B++;
        } else {
            goto shared;
        }
        /* fall through */

    case 1:
        {
            s16 timer;
            s32 delta;
            s32 position;
            s32 velocity;

            ((S_80174F24_0 *)arg0)->unk_90 -= ((S_80174F24_0 *)arg0)->unk_A0;
            timer = ((S_80174F24_0 *)arg0)->unk_9E.s;
            if (timer != 0) {
                delta = ((S_80174F24_1 *)arg2)->unk_24 << 6;
                position = ((S_80174F24_3 *)arg1)->unk_02 - 0x20;
                delta -= position;
                velocity = (delta << 16) / timer;

                position = ((S_80174F24_3 *)arg1)->unk_06;
                ((S_80174F24_3 *)arg1)->unk_0C = velocity;
                position -= 0x20;
                delta = ((S_80174F24_1 *)arg2)->unk_25 << 6;
                delta -= position;
                ((S_80174F24_3 *)arg1)->unk_10 =
                    (delta << 16) / ((S_80174F24_0 *)arg0)->unk_9E.s;

                ((S_80174F24_0 *)arg0)->unk_A0 =
                    (-func_800644B8(((S_80174F24_0 *)arg0)->unk_9E.s * 409)) << 9;
            }

            ((S_80174F24_0 *)arg0)->unk_90 += ((S_80174F24_0 *)arg0)->unk_A0;
            timer = ((S_80174F24_0 *)arg0)->unk_9E.u - 1;
            ((S_80174F24_0 *)arg0)->unk_9E.s = timer;
            if (timer >= 0) {
                goto state2;
            }
            ((S_80174F24_0 *)arg0)->unk_90 = 0;
            ((S_80174F24_0 *)arg0)->unk_98 &= 0xFFF7;
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 |= 0x08000000;
            ((S_80174F24_0 *)arg0)->unk_9B++;
        }
        /* fall through */

    case 2:
state2:
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x08000000) {
            u8 *table;

            ((S_80174F24_0 *)arg0)->unk_98 &= 0xFFF7;
            ((S_80174F24_3 *)arg1)->unk_14 = 0;
            ((S_80174F24_3 *)arg1)->unk_10 = 0;
            ((S_80174F24_3 *)arg1)->unk_0C = 0;
            func_800A2B04(arg1,
                ((S_80174F24_1 *)arg2)->unk_24, ((S_80174F24_1 *)arg2)->unk_25);
            table = D_80176340;
            (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
            func_80047784(arg2,
                table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
            ((S_80174F24_0 *)arg0)->unk_9B++;
        }
        break;

    default:
        break;
    }

shared:
    {
        s16 timer;
        s16 *counter;
        u32 flags;

        timer = ((S_80174F24_0 *)arg0)->unk_96.s - 1;
        ((S_80174F24_0 *)arg0)->unk_96.u = timer;
        if (timer > 0) {
            return;
        }

        ((S_80174F24_3 *)arg1)->unk_14 = 0;
        ((S_80174F24_3 *)arg1)->unk_10 = 0;
        ((S_80174F24_3 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1,
            ((S_80174F24_1 *)arg2)->unk_24, ((S_80174F24_1 *)arg2)->unk_25);
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);

        counter = (s16 *)&D_80083460;
        if (counter[4] != 0) {
            counter[4]--;
        }

        flags = ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32;
        if (flags & 0x2000) {
            if (((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x8000) {
                ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v &= 0x7FFF;
            }
            goto update_actor;
        }
        if (flags & 0x410) {
            goto update_actor;
        }
        if (flags & 0x20000) {
            ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = func_800A0818(
                ((S_80174F24_1 *)arg2)->unk_24, ((S_80174F24_1 *)arg2)->unk_25,
                D_80082E80[0x24], D_80082E80[0x25], &scratch);
        }

update_actor:
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            ((S_80174F24_0 *)arg0)->unk_8C = &D_80173B98;
            func_800A9A04(arg3);
        }
        ASM_KEEP(arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    }
}
