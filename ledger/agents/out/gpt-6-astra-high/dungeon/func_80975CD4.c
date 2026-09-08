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

/* Updates actor behavior, animation, and facing from its status and current tile. */
void func_801714D4(void *actor_arg, void *context_arg, void *sprite_arg, void *stats_arg)
{
    static void *const action_labels[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6,
        &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12
    };
    void *actor = actor_arg;
    void *context = context_arg;
    register void *sprite ASM_REG("$17") = sprite_arg;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *stats ASM_REG("$18") = stats_arg;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s16 distance;
    s32 flags;
    s32 action_index;
    s8 tile_index;
    s16 angle;
    u16 action_flags;
    void *callback;
    void *owner;


    if (D_80083462 & 0x1000) {
        ((S_801714D4_0 *)actor)->unk_9A = 14;
        func_80171A18(actor, context, sprite, stats);
        return;
    }

    ASM_KEEP(actor);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(context);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(sprite);   /* MATCH pin: retail basic-block layout depends on it */
    ASM_KEEP(stats);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    if (((Rec_D_800E3D7C *)stats)->unk_24.at01_u8.v == 0) {
        func_800AA79C(actor, context, sprite, stats);
        if (((S_801714D4_2 *)sprite)->unk_2C == D_80174158) {
            return;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174150;
        func_80047784(
            sprite,
            D_80174150[((D_80083228 + ((Rec_D_800E3D7C *)stats)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((Rec_D_800E3D7C *)stats)->unk_1C.as_u32 & 0x200) {
        if (((S_801714D4_2 *)sprite)->unk_2C == D_80174158) {
            ((S_801714D4_0 *)actor)->unk_9A = 13;
            ((S_801714D4_0 *)actor)->unk_9B = 1;
            ((S_801714D4_0 *)actor)->unk_8C = 0;
            ((Rec_D_800E3D7C *)stats)->unk_1C.as_u32 &= ~0x40000;
            return;
        }
        if (func_800AA924(actor, context, sprite, D_801740F0) != 0) {
            return;
        }
    }

    if ((D_80083462 & 0x2000) == 0) {
        if (((Rec_D_800E3D7C *)stats)->unk_1C.as_u32 & 0x100) {
            func_800AA258(actor, context, sprite, stats);
            return;
        }

        if (((S_801714D4_0 *)actor)->unk_9A != 14) {
            ((S_801714D4_0 *)actor)->unk_9A = 14;
        }

        if ((((S_801714D4_2 *)sprite)->unk_2C != D_801740E0) &&
            (((S_801714D4_2 *)sprite)->unk_2C != D_801740E8)) {
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801740E0;
            func_80047784(
                sprite,
                D_801740E0[((D_80083228 + ((Rec_D_800E3D7C *)stats)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
            ((S_801714D4_2 *)sprite)->unk_05 = 1;
            ((S_801714D4_0 *)actor)->unk_A2.s = 0;
            ((S_801714D4_0 *)actor)->unk_9E = 0;
        }

        ((Rec_D_800E3D7C *)stats)->unk_1C.as_u32 |= 0x40000;
        ((S_801714D4_0 *)actor)->unk_98 &= 0xFFF7;

        if (((Rec_D_800E3D7C *)stats)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(actor, context, sprite, D_80174140) != 0) {
                return;
            }
        }

        if (((Rec_D_800E3D7C *)stats)->unk_1C.as_u32 & 0x80000) {
            func_800AA888(actor, context, sprite, stats);
            ((S_801714D4_0 *)actor)->unk_92 -= ((S_801714D4_0 *)actor)->unk_A2.u;
            ((S_801714D4_0 *)actor)->unk_A2.s = 0;
            ((S_801714D4_0 *)actor)->unk_9E = 0;
            func_80173E00(actor, context, sprite, stats);
            return;
        }

        if ((s16)func_800A1C58(stats) != 0) {
            func_800AAB10(actor, context, sprite, stats);
        }
    }

    tile_index = func_8009FB34(((S_801714D4_2 *)sprite)->unk_24.at00.v, ((S_801714D4_2 *)sprite)->unk_24.at01.v);
    ((S_801714D4_2 *)sprite)->unk_26 = tile_index;

    if (((Rec_D_800E3D7C *)stats)->unk_6D.as_s8 > 0) {
        if (((Rec_D_800E3D7C *)stats)->unk_1C.as_u32 & 0x20) {
            goto jt_c12;
        }
        if (((S_801714D4_2 *)sprite)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto jt_default;
        }
        action_flags = ((Rec_D_800E3D7C *)stats)->unk_44.at02_u16.v;
        if ((action_flags & 0x8000) == 0) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(
                        stats, (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172628(actor, context, sprite, 0) == 0) {
                return;
            }
            action_flags = ((Rec_D_800E3D7C *)stats)->unk_44.at02_u16.v | 0x4000;
            ((Rec_D_800E3D7C *)stats)->unk_44.at02_u16.v = action_flags;
            if ((action_flags & 0x8000) == 0) {
                goto jt_default;
            }
        }

        action_index = (((Rec_D_800E3D7C *)stats)->unk_44.at02_u16.v & 0x3FFF) - 1;
        if ((u32)action_index >= 12U) {
            goto jt_default;
        }
        (void)action_labels;
        goto *D_80170808[action_index];

jt_c8:
jt_c9:
        if ((s16)func_8017237C(actor, context, sprite, stats) != 0) {
            return;
        }
        func_80172548(actor, context, sprite, stats);
        return;

jt_c5:
jt_c6:
jt_c7:
        angle = func_800A0818(
            ((S_801714D4_2 *)sprite)->unk_24.at00.v, ((S_801714D4_2 *)sprite)->unk_24.at01.v,
            D_80082E80[0x24], D_80082E80[0x25], &distance);
        owner = D_800814A8;
        ((Rec_D_800E3D7C *)stats)->unk_2A.as_s16 = angle;
        if (((S_801714D4_4 *)owner)->unk_9A == 0x11) {
            goto jt_c1;
        }

jt_c12:
        func_800A9A0C(stats);
        return;

jt_c1:
jt_c2:
jt_c3:
        callback = (void *)func_801714D4;

jt_call:
        func_800AAF00(actor, context, sprite, 0, callback);
        return;

jt_c4:
jt_c10:
jt_c11:
jt_default:
        func_80171C34(actor, context, sprite, stats);
        return;
    }

    flags = ((Rec_D_800E3D7C *)stats)->unk_1C.as_u32;
    if (flags & 0x2000) {
        return;
    }
    if (tile_index >= 0) {
        if (D_800E2970[tile_index].flags & 2) {
            return;
        }
    }
    if (flags & 0x430) {
        return;
    }

    {
        u8 *origin = D_80082E80;

        if ((s16)func_8009FD7C(
                ((S_801714D4_2 *)sprite)->unk_24.at00.v, ((S_801714D4_2 *)sprite)->unk_24.at01.v,
                origin[0x24], origin[0x25]) == 0) {
            return;
        }
        ((Rec_D_800E3D7C *)stats)->unk_2A.as_s16 = func_800A0818(
            ((S_801714D4_2 *)sprite)->unk_24.at00.v, ((S_801714D4_2 *)sprite)->unk_24.at01.v,
            origin[0x24], origin[0x25], &distance);
    }
}
