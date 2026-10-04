#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_80171094_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0xA];
    union { s16 s; u16 u; } unk_A6;   /* accessed as both */
    u8 pad_A8[0x4];
    union { s16 s; u16 u; } unk_AC;   /* accessed as both */
} S_80171094_0;   /* arg0 in func_80171094 */

typedef struct S_80171094_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80171094_1;   /* arg3 in func_80171094 */

typedef struct S_80171094_2 {
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
} S_80171094_2;   /* arg2 in func_80171094 */


extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(u8, u8);
extern s32 func_8009FD7C(u8, u8, u8, u8);
extern s16 func_800A0818(u8, u8, u8, u8, s16 *);
extern s32 func_800A1C58(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);

extern void func_801716D8(void *, void *, void *, void *);
extern void func_801718B4(void *, void *, void *, void *);
extern s32 func_80171FFC(void *, void *, void *, void *);
extern void func_801721C0(void *, void *, void *, void *);
extern s32 func_80172438(void *, void *, void *, void *);
extern void func_8017272C(void *, void *, void *, void *);
extern void func_8017283C(void *, void *, void *, void *);
extern void func_8017294C(void *, void *, void *, void *);
extern s32 func_80172A5C(void *, void *, void *, s32);
extern void func_80174520(void *, void *, void *, void *);

extern u8 D_80171094[];
extern u8 D_80176460[];
extern u8 D_80176468[];
extern u8 D_80176470[];
extern u8 D_801764A8[];

/* Updates actor animation, status, and behavior according to dungeon state. */
void func_80171094(void *actor_arg, void *context_arg, void *sprite_arg, void *stats_arg)
{
    void *stats = stats_arg;
    s16 distance;
    s8 tile_id;
    u16 action_flags;

    if (dungeonStatus.flags & 0x1000) {
        ((S_80171094_0 *)actor_arg)->unk_9A = 14;
        func_801716D8(actor_arg, context_arg, sprite_arg, stats);
        return;
    }


    if (((S_80171094_1 *)stats)->unk_25 == 0) {
        func_800AA79C(actor_arg, context_arg, sprite_arg, stats);
        if (((S_80171094_2 *)sprite_arg)->unk_2C == D_80176470) {
            return;
        }
        {
            u8 *animations = D_80176468;
            (*(u8 * *)((u8 *)sprite_arg + 0x2C)) = animations;
            func_80047784(
                sprite_arg,
                animations[((gameWork.view.viewAngle + ((S_80171094_1 *)stats)->unk_2A.s + 0x100) >> 9) & 7],
                0);
            return;
        }
    }

    if (((S_80171094_1 *)stats)->unk_1C & 0x200) {
        if (((S_80171094_2 *)sprite_arg)->unk_2C == D_80176470) {
            ((S_80171094_0 *)actor_arg)->unk_9A = 13;
            ((S_80171094_0 *)actor_arg)->unk_9B = 1;
            ((S_80171094_0 *)actor_arg)->unk_8C = 0;
            ((S_80171094_1 *)stats)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(actor_arg, context_arg, sprite_arg, D_80176468) != 0) {
            return;
        }
    }

    if ((dungeonStatus.flags & 0x2000) == 0) {
        if (((S_80171094_1 *)stats)->unk_1C & 0x100) {
            func_800AA258(actor_arg, context_arg, sprite_arg, stats);
            return;
        }

        if (((S_80171094_0 *)actor_arg)->unk_9A != 14) {
            ((S_80171094_0 *)actor_arg)->unk_9A = 14;
        }

        if (((S_80171094_2 *)sprite_arg)->unk_2C != D_80176460) {
            u8 *animations = D_80176460;
            (*(u8 * *)((u8 *)sprite_arg + 0x2C)) = animations;
            func_80047784(
                sprite_arg,
                animations[((gameWork.view.viewAngle + ((S_80171094_1 *)stats)->unk_2A.s + 0x100) >> 9) & 7],
                0);
            ((S_80171094_2 *)sprite_arg)->unk_05 = 1;
            ((S_80171094_0 *)actor_arg)->unk_A6.s = 0;
            ((S_80171094_0 *)actor_arg)->unk_AC.s = 0;
        }

        {
            u32 flags = ((S_80171094_1 *)stats)->unk_1C;
            u16 actor_flags;

            if (flags & 0x20) {
                ((S_80171094_1 *)stats)->unk_1C = flags & ~0x40000;
                actor_flags = ((S_80171094_0 *)actor_arg)->unk_98 | 8;
            } else {
                ((S_80171094_1 *)stats)->unk_1C = flags | 0x40000;
                actor_flags = ((S_80171094_0 *)actor_arg)->unk_98 & 0xFFF7;
            }
            ((S_80171094_0 *)actor_arg)->unk_98 = actor_flags;
        }

        if (((S_80171094_1 *)stats)->unk_64 != 0) {
            if (func_800AA6B4(actor_arg, context_arg, sprite_arg, D_801764A8) != 0) {
                return;
            }
        }

        if (((S_80171094_1 *)stats)->unk_1C & 0x80000) {
            func_800AA888(actor_arg, context_arg, sprite_arg, stats);
            ((S_80171094_0 *)actor_arg)->unk_92 -= ((S_80171094_0 *)actor_arg)->unk_A6.u;
            ((S_80171094_0 *)actor_arg)->unk_A6.u = 0;
            ((S_80171094_0 *)actor_arg)->unk_AC.u = 0;
            func_80174520(actor_arg, context_arg, sprite_arg, stats);
            return;
        }

        if ((s16)func_800A1C58(stats) != 0) {
            func_800AAB10(actor_arg, context_arg, sprite_arg, stats);
        }
    }

    tile_id = func_8009FB34(((S_80171094_2 *)sprite_arg)->unk_24.at00.v, ((S_80171094_2 *)sprite_arg)->unk_24.at01.v);
    ((S_80171094_2 *)sprite_arg)->unk_26 = tile_id;

    if (((S_80171094_1 *)stats)->unk_6D > 0) {
        if (((S_80171094_1 *)stats)->unk_1C & 0x20) {
            func_800A9A0C(stats);
            return;
        }
        if (((S_80171094_2 *)sprite_arg)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_801718B4(actor_arg, context_arg, sprite_arg, stats);
            return;
        }
        action_flags = ((S_80171094_1 *)stats)->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)func_8009A180(
                        stats, (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172A5C(actor_arg, context_arg, sprite_arg, 0) == 0) {
                return;
            }
            action_flags = ((S_80171094_1 *)stats)->unk_46 | 0x4000;
            ((S_80171094_1 *)stats)->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                func_801718B4(actor_arg, context_arg, sprite_arg, stats);
            return;
            }
        }

        switch (((S_80171094_1 *)stats)->unk_46 & 0x3FFF) {
        case 8:
            if ((s16)func_80171FFC(actor_arg, context_arg, sprite_arg, stats) != 0) {
                return;
            }
            func_801721C0(actor_arg, context_arg, sprite_arg, stats);
            return;
        case 9:
            if (((S_80171094_1 *)stats)->unk_1C & 0x400) {
                s32 behavior_state;
                behavior_state = ((S_80171094_1 *)stats)->unk_14;
                if ((behavior_state & 0x80000000) == 0) {
                    behavior_state |= 0x80000000;
                    ((S_80171094_1 *)stats)->unk_14 = behavior_state;
                    ((S_80171094_1 *)stats)->unk_2A.u += (func_800A6D30() & 7) << 9;
                }
            }
            switch ((s16)func_80172438(actor_arg, context_arg, sprite_arg, stats)) {
            case -1:
            case 1:
                break;
            case 0:
                func_8017272C(actor_arg, context_arg, sprite_arg, stats);
                return;
            case 2:
                func_8017283C(actor_arg, context_arg, sprite_arg, stats);
                return;
            case 3:
                func_8017294C(actor_arg, context_arg, sprite_arg, stats);
                return;
            }
            return;
        case 5:
        case 6:
        case 7:
            {
                s16 heading = func_800A0818(
                    ((S_80171094_2 *)sprite_arg)->unk_24.at00.v, ((S_80171094_2 *)sprite_arg)->unk_24.at01.v,
                    D_80082E80.tileX, D_80082E80.tileY, &distance);
                EntityRec *player = D_800814A8;
                ((S_80171094_1 *)stats)->unk_2A.s = heading;
                if (player->unk_9A == 0x11) {
                    func_800AAF00(actor_arg, context_arg, sprite_arg, D_80176460, D_80171094);
                    return;
                }
            }
            /* fallthrough */
        case 12:
            func_800A9A0C(stats);
            return;
        case 1:
        case 2:
        case 3:
            func_800AAF00(actor_arg, context_arg, sprite_arg, D_80176460, D_80171094);
            return;
        default:
            func_801718B4(actor_arg, context_arg, sprite_arg, stats);
            return;
        }
    }

    {
        u32 flags = ((S_80171094_1 *)stats)->unk_1C;

        if (!(flags & 0x2000)) {
            s32 tile_index = (s8)tile_id;

            if ((tile_index < 0) ||
                !(D_800E2970[tile_index].flags & 2)) {
                if (!(flags & 0x430)) {
                    if ((s16)func_8009FD7C(
                            ((S_80171094_2 *)sprite_arg)->unk_24.at00.v, ((S_80171094_2 *)sprite_arg)->unk_24.at01.v,
                            D_80082E80.tileX, D_80082E80.tileY) != 0) {
                        ((S_80171094_1 *)stats)->unk_2A.s = func_800A0818(
                            ((S_80171094_2 *)sprite_arg)->unk_24.at00.v, ((S_80171094_2 *)sprite_arg)->unk_24.at01.v,
                            D_80082E80.tileX, D_80082E80.tileY,
                            &distance);
                    }
                }
            }
        }
    }
}
