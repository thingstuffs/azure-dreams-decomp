#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172C10_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xB];
    u8 unk_A7;
    u8 unk_A8;
} S_80172C10_0;   /* arg0 in func_80172C10 */






extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 *D_800E3D7C;
extern u8 D_80170F20[];
extern u8 D_80173B98[];
extern u8 D_80176318[];
extern u8 D_80176378[];

void func_80172C10(S_80172C10_0 *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, void *arg3)
{
    s32 one;
    s32 value;
    s32 *global_state;

    one = 1;
    switch (arg0->unk_9B) {
    case 0:
        func_800AD4D0(arg3);
        arg1->unk_0C.as_s32 =
            *(s16 *)((u8 *)&D_8006CCD8 +
                     ((((Rec_D_800E3D7C *)arg3)->unk_6A.as_u16 >> 8) & 0xE)) << 19;
        arg1->unk_10.at00_s32.v =
            *(s16 *)((u8 *)&D_8006CCE8 +
                     ((((Rec_D_800E3D7C *)arg3)->unk_6A.as_u16 >> 8) & 0xE)) << 19;
        arg0->unk_9B++;

        if (((Rec_D_800E3D7C *)arg3)->unk_28 == 0) {
            arg1->unk_14.as_s32 = 0;
            arg1->unk_10.at00_s32.v = 0;
            arg1->unk_0C.as_s32 = 0;
            if (arg0->unk_A7 != 0) {
                func_800AAA54(arg0, arg1, arg2, D_80176378);
                if (arg0->unk_A8 != 0) {
                    u8 *mark;

                    mark = D_800E3D7C;
                    mark += arg0->unk_A8;
                    mark[0xF9] = one;
                }
                return;
            }
            func_800AAA54(arg0, arg1, arg2, D_80176318);
            return;
        }

        if (arg2->unk_14.at00_u16.v & 0x8000) {
            arg0->unk_96.s = 0;
            arg0->unk_9B = 2;
            return;
        }
        arg0->unk_96.s =
            (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x228) ? 8 : -1;
        /* fall through */

    case 1:
        arg1->unk_0C.as_s32 -= arg1->unk_0C.as_s32 / 4;
        arg1->unk_10.at00_s32.v -= arg1->unk_10.at00_s32.v / 4;

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

        arg1->unk_14.as_s32 = 0;
        arg1->unk_10.at00_s32.v = 0;
        arg1->unk_0C.as_s32 = 0;
        if (arg0->unk_A7 != 0) {
            func_800AAA54(arg0, arg1, arg2, D_80176378);
            if (arg0->unk_A8 != 0) {
                u8 *mark;

                mark = D_800E3D7C;
                mark += arg0->unk_A8;
                mark[0xF9] = 1;
            }
            return;
        }
        func_800AAA54(arg0, arg1, arg2, D_80176318);
        return;

increment_state:
        arg0->unk_96.s = 8;
        arg0->unk_9B++;
        return;

    case 2: {
        s32 case_x;
        s32 case_y;
        s32 case_delta;
        s16 case_timer;
        u16 case_utimer;

        case_timer = arg0->unk_96.s;
        if (case_timer > 0) {
            case_x = arg2->unk_24 << 6;
            case_delta = arg1->unk_00.at02_s16.v - 0x20;
            case_x = (case_x - case_delta) << 16;
            case_x = case_x / case_timer;
            case_delta = arg1->unk_04.at02_s16.v - 0x20;
            arg1->unk_0C.as_s32 = case_x;
            case_y = (arg2->unk_25 << 6) - case_delta;
            arg1->unk_10.at00_s32.v =
                (case_y << 16) / arg0->unk_96.s;
        }

        case_utimer = arg0->unk_96.u - 1;
        arg0->unk_96.s = case_utimer;
        if ((s32)(case_utimer << 16) > 0) {
            return;
        }

        arg1->unk_14.as_s32 = 0;
        arg1->unk_10.at00_s32.v = 0;
        arg1->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);

        global_state = &D_80083460;
        value = global_state[4];
        if (value == (s32)((u8 *)arg3 - 0x20)) {
            global_state[4] = value & 0x7FFFFFFF;
        }
        if (arg0->unk_A7 != 0) {
            arg0->unk_8C = D_80173B98;
        } else {
            arg0->unk_8C = D_80170F20;
        }
        return;
    }

    default:
        return;
    }
}

/* MECHANISM: Split the fall-through timer web so direct fields emit the fresh lh/lhu pair.
   Case-2 sibling locals preload the second coordinate into the first mflo hazard slot.
   Compound /4 damping and pointer-update indexing recover retail coloring and order. */
