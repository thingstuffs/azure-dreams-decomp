#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"



typedef struct S_801713A8_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} S_801713A8_2;   /* arg2 in func_801713A8 */


typedef struct S_801713A8_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_801713A8_4;   /* owner in func_801713A8 */

typedef struct S_801713A8_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801713A8_5;   /* map_base in func_801713A8 */



typedef struct DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(u8, u8);
extern s32 func_8009FD7C(u8, u8, u8, u8);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_801718D0(void *);
extern void func_80171A98(void *, void *, void *, void *);
extern s32 func_801721E0(void *, void *, void *, void *);
extern void func_801723A4(void *, void *, void *, void *);
extern s32 func_801724C4(void *, void *, void *, s32);
extern void func_80174250(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_80174494[];
extern u8 D_8017449C[];
extern u8 D_801744A4[];
extern u8 D_801744D4[];
extern u8 D_801744EC[];
extern u8 D_801744FC[];

void func_801713A8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const sw_keep[] = {
        &&case_1, &&case_2, &&case_3, &&case_4,
        &&case_5, &&case_6, &&case_7, &&case_8,
        &&case_9, &&case_10, &&case_11, &&case_12,
    };
    s32 distance;
    u32 flags;
    s32 kind;
    s8 tile;
    u16 field46;
    void *fifth;
    u8 *map_base;

    if (D_80083462 & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 14;
        func_801718D0(arg0);
        return;
    }

    if (((Rec_D_800E3D7C *)arg3)->unk_24.at01_u8.v == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (((S_801713A8_2 *)arg2)->unk_2C == D_801744FC) {
            return;
        }
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801744EC;
        func_80047784(
            arg2,
            D_801744EC[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x200) {
        if (((S_801713A8_2 *)arg2)->unk_2C == D_801744FC) {
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 13;
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9B.as_u8 = 2;
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_8C = 0;
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 &= ~0x40000;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_801744EC) != 0) {
            return;
        }
    }

    if ((D_80083462 & 0x2000) == 0) {
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 != 14) {
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 14;
        }

        if ((((S_801713A8_2 *)arg2)->unk_2C != D_80174494) &&
            (((S_801713A8_2 *)arg2)->unk_2C != D_8017449C)) {
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_A8 = 0;
            (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_8017449C;
            func_80047784(
                arg2,
                D_8017449C[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                ((Rec_func_800A9E70_arg0 *)arg0)->unk_A8);
        }

        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 |= 0x40000;
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_98 &= 0xFFF7;

        if (((Rec_D_800E3D7C *)arg3)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_801744A4) != 0) {
                return;
            }
        }

        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_A8 = 0;
            func_80174250(arg0, arg1, arg2, arg3);
            return;
        }

        if ((s16)func_800A1C58(arg3) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    tile = func_8009FB34(((S_801713A8_2 *)arg2)->unk_24.at00.v, ((S_801713A8_2 *)arg2)->unk_24.at01.v);
    ((S_801713A8_2 *)arg2)->unk_26 = tile;

    if (((Rec_D_800E3D7C *)arg3)->unk_6D.as_s8 > 0) {
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x20) {
            goto case_12;
        }
        if (((S_801713A8_2 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto case_default;
        }
        field46 = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v;
        if ((field46 & 0x8000) == 0) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(
                        arg3, (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_801724C4(arg0, arg1, arg2, 0) == 0) {
                return;
            }
            field46 = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v | 0x4000;
            ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v = field46;
            if ((field46 & 0x8000) == 0) {
                goto case_default;
            }
        }

        kind = (((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x3FFF) - 1;
        if ((u32)kind >= 12U) {
            goto case_default;
        }
        (void)sw_keep;
        goto *D_80170808[kind];

case_8:
case_9:
        if ((s16)func_801721E0(arg0, arg1, arg2, arg3) != 0) {
            return;
        }
        func_801723A4(arg0, arg1, arg2, arg3);
        return;

case_5:
case_6:
case_7:
        {
            s16 new_distance;
            void *owner;

            new_distance = func_800A0818(
                ((S_801713A8_2 *)arg2)->unk_24.at00.v, ((S_801713A8_2 *)arg2)->unk_24.at01.v,
                D_80082E80[0x24], D_80082E80[0x25], &distance);
            owner = D_800814A8;
            ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = new_distance;
            if (((S_801713A8_4 *)owner)->unk_9A != 0x11) {
                goto case_12;
            }
        }
        fifth = (void *)func_801713A8;
        goto case_call;

case_12:
        func_800A9A0C(arg3);
        return;

case_1:
case_2:
case_3:
        fifth = (void *)func_801713A8;

case_call:
        func_800AAF00(arg0, arg1, arg2, D_801744D4, fifth);
        return;

case_4:
case_10:
case_11:
case_default:
        func_80171A98(arg0, arg1, arg2, arg3);
        return;
    }

    flags = ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32;
    if (flags & 0x2000) {
        return;
    }
    if (tile >= 0) {
        if (((DungeonRecord *)D_800E2970)[tile].flags & 2) {
            return;
        }
    }
    if (flags & 0x430) {
        return;
    }

    map_base = D_80082E80;
    if ((s16)func_8009FD7C(
            ((S_801713A8_2 *)arg2)->unk_24.at00.v, ((S_801713A8_2 *)arg2)->unk_24.at01.v,
            ((S_801713A8_5 *)map_base)->unk_24, ((S_801713A8_5 *)map_base)->unk_25) == 0) {
        return;
    }
    ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = func_800A0818(
        ((S_801713A8_2 *)arg2)->unk_24.at00.v, ((S_801713A8_2 *)arg2)->unk_24.at01.v,
        ((S_801713A8_5 *)map_base)->unk_24, ((S_801713A8_5 *)map_base)->unk_25, &distance);
}
