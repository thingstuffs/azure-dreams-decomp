#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"


typedef struct DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(u8, u8);
extern s32 func_8009FD7C(u8, u8, u8, u8);
extern s16 func_800A0818(u8, u8, u8, u8, s16 *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);

extern void func_80171A18(void *, void *, void *, void *);
extern void func_80171C34(void *, void *, void *, void *);
extern s32 func_8017237C(void *, void *, void *, void *);
extern void func_80172548(void *, void *, void *, void *);
extern s32 func_80172628(void *, void *, void *, s32);
extern void func_80173E00(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern DungeonRecord D_800E2970[];
extern void *D_80170808[];
extern u8 D_801740E0[];
extern u8 D_801740E8[];
extern u8 D_801740F0[];
extern u8 D_80174140[];
extern u8 D_80174150[];
extern u8 D_80174158[];


typedef struct S_801714D4_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
} S_801714D4_0;   /* arg0 in func_801714D4 */


typedef struct S_801714D4_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0x1E];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} S_801714D4_2;   /* arg2 in func_801714D4 */


typedef struct S_801714D4_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_801714D4_4;   /* owner in func_801714D4 */

void func_801714D4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6,
        &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12
    };
    void *p0 = arg0;
    void *p1 = arg1;
    register void *p2 ASM_REG("$17") = arg2;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *p3 ASM_REG("$18") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s16 sp18;
    s32 flags;
    s32 kind;
    s8 tile;
    s16 angle;
    u16 field46;
    void *fifth;
    void *owner;

#define arg0 p0
#define arg1 p1
#define arg2 p2
#define arg3 p3

    if (D_80083462 & 0x1000) {
        ((S_801714D4_0 *)arg0)->unk_9A = 14;
        func_80171A18(arg0, arg1, arg2, arg3);
        return;
    }

    ASM_KEEP(p0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(p1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(p2);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(p3);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    if (((Rec_D_800E3D7C *)arg3)->unk_24.at01_u8.v == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (((S_801714D4_2 *)arg2)->unk_2C == D_80174158) {
            return;
        }
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80174150;
        func_80047784(
            arg2,
            D_80174150[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x200) {
        if (((S_801714D4_2 *)arg2)->unk_2C == D_80174158) {
            ((S_801714D4_0 *)arg0)->unk_9A = 13;
            ((S_801714D4_0 *)arg0)->unk_9B = 1;
            ((S_801714D4_0 *)arg0)->unk_8C = 0;
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 &= ~0x40000;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_801740F0) != 0) {
            return;
        }
    }

    if ((D_80083462 & 0x2000) == 0) {
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        if (((S_801714D4_0 *)arg0)->unk_9A != 14) {
            ((S_801714D4_0 *)arg0)->unk_9A = 14;
        }

        if ((((S_801714D4_2 *)arg2)->unk_2C != D_801740E0) &&
            (((S_801714D4_2 *)arg2)->unk_2C != D_801740E8)) {
            (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801740E0;
            func_80047784(
                arg2,
                D_801740E0[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
            ((S_801714D4_2 *)arg2)->unk_05 = 1;
            ((S_801714D4_0 *)arg0)->unk_A2.s = 0;
            ((S_801714D4_0 *)arg0)->unk_9E = 0;
        }

        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 |= 0x40000;
        ((S_801714D4_0 *)arg0)->unk_98 &= 0xFFF7;

        if (((Rec_D_800E3D7C *)arg3)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80174140) != 0) {
                return;
            }
        }

        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            ((S_801714D4_0 *)arg0)->unk_92 -= ((S_801714D4_0 *)arg0)->unk_A2.u;
            ((S_801714D4_0 *)arg0)->unk_A2.s = 0;
            ((S_801714D4_0 *)arg0)->unk_9E = 0;
            func_80173E00(arg0, arg1, arg2, arg3);
            return;
        }

        if ((s16)func_800A1C58(arg3) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    tile = func_8009FB34(((S_801714D4_2 *)arg2)->unk_24.at00.v, ((S_801714D4_2 *)arg2)->unk_24.at01.v);
    ((S_801714D4_2 *)arg2)->unk_26 = tile;

    if (((Rec_D_800E3D7C *)arg3)->unk_6D.as_s8 > 0) {
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x20) {
            goto jt_c12;
        }
        if (((S_801714D4_2 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto jt_default;
        }
        field46 = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v;
        if ((field46 & 0x8000) == 0) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(
                        arg3, (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172628(arg0, arg1, arg2, 0) == 0) {
                return;
            }
            field46 = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v | 0x4000;
            ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v = field46;
            if ((field46 & 0x8000) == 0) {
                goto jt_default;
            }
        }

        kind = (((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x3FFF) - 1;
        if ((u32)kind >= 12U) {
            goto jt_default;
        }
        (void)jt_keep;
        goto *D_80170808[kind];

jt_c8:
jt_c9:
        if ((s16)func_8017237C(arg0, arg1, arg2, arg3) != 0) {
            return;
        }
        func_80172548(arg0, arg1, arg2, arg3);
        return;

jt_c5:
jt_c6:
jt_c7:
        angle = func_800A0818(
            ((S_801714D4_2 *)arg2)->unk_24.at00.v, ((S_801714D4_2 *)arg2)->unk_24.at01.v,
            D_80082E80[0x24], D_80082E80[0x25], &sp18);
        owner = D_800814A8;
        ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = angle;
        if (((S_801714D4_4 *)owner)->unk_9A == 0x11) {
            goto jt_c1;
        }

jt_c12:
        func_800A9A0C(arg3);
        return;

jt_c1:
jt_c2:
jt_c3:
        fifth = (void *)func_801714D4;

jt_call:
        func_800AAF00(arg0, arg1, arg2, 0, fifth);
        return;

jt_c4:
jt_c10:
jt_c11:
jt_default:
        func_80171C34(arg0, arg1, arg2, arg3);
        return;
    }

    flags = ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32;
    if (flags & 0x2000) {
        return;
    }
    if (tile >= 0) {
        if (D_800E2970[tile].flags & 2) {
            return;
        }
    }
    if (flags & 0x430) {
        return;
    }

    {
        u8 *origin = D_80082E80;

        if ((s16)func_8009FD7C(
                ((S_801714D4_2 *)arg2)->unk_24.at00.v, ((S_801714D4_2 *)arg2)->unk_24.at01.v,
                origin[0x24], origin[0x25]) == 0) {
            return;
        }
        ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = func_800A0818(
            ((S_801714D4_2 *)arg2)->unk_24.at00.v, ((S_801714D4_2 *)arg2)->unk_24.at01.v,
            origin[0x24], origin[0x25], &sp18);
    }
}
