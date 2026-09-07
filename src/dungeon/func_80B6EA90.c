#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172290_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
} S_80172290_0;   /* arg0 in func_80172290 */




typedef struct S_80172290_4 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_80172290_4;   /* global_state in func_80172290 */

typedef struct S_80172290_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172290_5;   /* map_state in func_80172290 */



extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s32 D_80083460;
extern s32 D_80170E5C;

void func_80172290(S_80172290_0 *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, Rec_D_800E3D7C *arg3) {
    s32 stack_value;
    s32 count;
    s32 flags;
    s32 state;

    state = arg0->unk_9B;
    if (state == 1) {
        goto movement;
    }
    if (state >= 2) {
        goto high_state;
    }
    if (state == 0) {
        goto initialize;
    }
    goto countdown;

high_state:
    if (state == 2) {
        goto check_flag;
    }
    goto countdown;

initialize:
    arg0->unk_98 |= 8;
    arg1->unk_14.as_s32 = 0xFFEE0000;
    arg3->unk_1C.as_s32 &= 0xF7FFFFFF;
    arg0->unk_A0 = 0;
    arg0->unk_9B++;

movement:
    count = arg0->unk_96.s;
    arg0->unk_90 -= arg0->unk_A0;
    if (count != 0) {
        {
            s32 coord = arg2->unk_24 << 6;
            s32 current = arg1->unk_00.at02_s16.v - 0x20;

            arg1->unk_0C.as_s32 = ((coord - current) << 16) / count;
        }
        {
            s32 coord = arg2->unk_25 << 6;
            s32 current = arg1->unk_04.at02_s16.v - 0x20;

            arg1->unk_10.at00_s32.v =
                ((coord - current) << 16) / arg0->unk_96.s;
        }
        arg0->unk_A0 += arg1->unk_14.as_s32;
        arg1->unk_14.as_s32 += 0x40000;
    }

    arg0->unk_90 += arg0->unk_A0;
    if (arg0->unk_96.s < 2) {
        arg0->unk_90 = 0;
        arg0->unk_98 &= 0xFFF7;
        arg3->unk_1C.as_s32 |= 0x08000000;
        arg0->unk_9B++;
    }

check_flag:
    if (arg3->unk_1C.as_s32 & 0x08000000) {
        arg0->unk_98 &= 0xFFF7;
        arg1->unk_14.as_s32 = 0;
        arg1->unk_10.at00_s32.v = 0;
        arg1->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
        arg0->unk_9B++;
    }

countdown:
    if ((s16)--arg0->unk_96.u <= 0) {
        arg1->unk_14.as_s32 = 0;
        arg1->unk_10.at00_s32.v = 0;
        arg1->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);

        {
            u8 *global_state = (u8 *)&D_80083460;

            if (((S_80172290_4 *)global_state)->unk_08.s != 0) {
                ((S_80172290_4 *)global_state)->unk_08.u--;
            }
        }

        flags = arg3->unk_1C.as_s32;
        if (!(flags & 0x2000)) {
            goto low_flags;
        }
        if (arg3->unk_44.at02_u16.v & 0x8000) {
            arg3->unk_44.at02_u16.v &= 0x7FFF;
        }
        goto call_entity;

low_flags:
        if (flags & 0x410) {
            goto call_entity;
        }
        if (flags & 0x20000) {
            u8 *map_state = D_80082E80;

            arg3->unk_2A.as_s16 = func_800A0818(
                arg2->unk_24, arg2->unk_25,
                ((S_80172290_5 *)map_state)->unk_24, ((S_80172290_5 *)map_state)->unk_25, &stack_value);
        }

call_entity:
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            arg0->unk_8C = &D_80170E5C;
            func_800A9A04(arg3);
        }
    }

done:
    return;
}
