#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"


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
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} S_801714D4_2;   /* arg2 in func_801714D4 */


/* Updates actor behavior, animation, and facing from its status and current tile. */
void func_801714D4(void *actor_arg, void *context_arg, void *sprite_arg, void *stats_arg)
{
    register void *actor_head = actor_arg;
    register void *context = context_arg;
    register void *sprite = sprite_arg;
    register EntityRec *stats = stats_arg;
    s16 distance;
    s32 flags;
    s32 action_index;
    s8 tile_index;
    s16 angle;
    u16 action_flags;
    void *callback;
    EntityRec *owner;
    void *actor_tail;
#define actor_arg actor_head
#define context_arg context


    if (dungeonStatus.flags & 0x1000) {
        ((S_801714D4_0 *)actor_arg)->unk_9A = 14;
        func_80171A18(actor_arg, context_arg, sprite, stats);
        return;
    }


    if (stats->tileY == 0) {
        func_800AA79C(actor_arg, context_arg, sprite, stats);
        if (((S_801714D4_2 *)sprite)->unk_2C == D_80174158) {
            return;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174150;
        func_80047784(
            sprite,
            D_80174150[((gameWork.view.viewAngle + stats->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)stats->flags1C) & 0x200) {
        if (((S_801714D4_2 *)sprite)->unk_2C == D_80174158) {
            ((S_801714D4_0 *)actor_arg)->unk_9A = 13;
            ((S_801714D4_0 *)actor_arg)->unk_9B = 1;
            ((S_801714D4_0 *)actor_arg)->unk_8C = 0;
            stats->flags1C &= ~0x40000;
            return;
        }
        if (func_800AA924(actor_arg, context_arg, sprite, D_801740F0) != 0) {
            return;
        }
    }

    if ((dungeonStatus.flags & 0x2000) == 0) {
        if (((u32)stats->flags1C) & 0x100) {
            func_800AA258(actor_arg, context_arg, sprite, stats);
            return;
        }

        if (((S_801714D4_0 *)actor_arg)->unk_9A != 14) {
            ((S_801714D4_0 *)actor_arg)->unk_9A = 14;
        }

        if ((((S_801714D4_2 *)sprite)->unk_2C != D_801740E0) &&
            (((S_801714D4_2 *)sprite)->unk_2C != D_801740E8)) {
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801740E0;
            func_80047784(
                sprite,
                D_801740E0[((gameWork.view.viewAngle + stats->facing + 0x100) >> 9) & 7],
                0);
            ((S_801714D4_2 *)sprite)->unk_05 = 1;
            ((S_801714D4_0 *)actor_arg)->unk_A2.s = 0;
            ((S_801714D4_0 *)actor_arg)->unk_9E = 0;
        }

        stats->flags1C |= 0x40000;
        ((S_801714D4_0 *)actor_arg)->unk_98 &= 0xFFF7;

        if (stats->unk_64 != 0) {
            if (func_800AA6B4(actor_arg, context_arg, sprite, D_80174140) != 0) {
                return;
            }
        }

        if (((u32)stats->flags1C) & 0x80000) {
            func_800AA888(actor_arg, context_arg, sprite, stats);
            ((S_801714D4_0 *)actor_arg)->unk_92 -= ((S_801714D4_0 *)actor_arg)->unk_A2.u;
            ((S_801714D4_0 *)actor_arg)->unk_A2.s = 0;
            ((S_801714D4_0 *)actor_arg)->unk_9E = 0;
            func_80173E00(actor_arg, context_arg, sprite, stats);
            return;
        }

        if ((s16)func_800A1C58(stats) != 0) {
            func_800AAB10(actor_arg, context_arg, sprite, stats);
        }
    }

    actor_tail = actor_head;
#undef actor_arg
#define actor_arg actor_tail
    tile_index = func_8009FB34(((S_801714D4_2 *)sprite)->unk_24.at00.v, ((S_801714D4_2 *)sprite)->unk_24.at01.v);
    ((S_801714D4_2 *)sprite)->unk_26 = tile_index;

    if (stats->unk_6D > 0) {
        if (((u32)stats->flags1C) & 0x20) {
            func_800A9A0C(stats);
            return;
        }
        if (((S_801714D4_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_80171C34(actor_arg, context_arg, sprite, stats);
            return;
        }
        action_flags = stats->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)func_8009A180(
                        stats, (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172628(actor_arg, context_arg, sprite, 0) == 0) {
                return;
            }
            action_flags = stats->unk_46 | 0x4000;
            stats->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                func_80171C34(actor_arg, context_arg, sprite, stats);
                return;
            }
        }

        action_index = (stats->unk_46 & 0x3FFF) - 1;
        switch (action_index) {
        case 7:
        case 8:
            if ((s16)func_8017237C(actor_arg, context_arg, sprite, stats) != 0) {
                return;
            }
            func_80172548(actor_arg, context_arg, sprite, stats);
            return;

        case 4:
        case 5:
        case 6:
            angle = func_800A0818(
                ((S_801714D4_2 *)sprite)->unk_24.at00.v, ((S_801714D4_2 *)sprite)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY, &distance);
            owner = D_800814A8;
            stats->facing = angle;
            if (owner->unk_9A == 0x11) {
                callback = (void *)func_801714D4;
                func_800AAF00(actor_arg, context_arg, sprite, 0, callback);
                return;
            }

        case 11:
            func_800A9A0C(stats);
            return;

        case 0:
        case 1:
        case 2:
            callback = (void *)func_801714D4;

            func_800AAF00(actor_arg, context_arg, sprite, 0, callback);
            return;

        default:
            func_80171C34(actor_arg, context_arg, sprite, stats);
            return;
        }
    }

    flags = ((u32)stats->flags1C);
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

        if ((s16)func_8009FD7C(
                ((S_801714D4_2 *)sprite)->unk_24.at00.v, ((S_801714D4_2 *)sprite)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY) == 0) {
            return;
        }
        stats->facing = func_800A0818(
            ((S_801714D4_2 *)sprite)->unk_24.at00.v, ((S_801714D4_2 *)sprite)->unk_24.at01.v,
            D_80082E80.tileX, D_80082E80.tileY, &distance);
    }
#undef actor_arg
#undef context_arg
}
