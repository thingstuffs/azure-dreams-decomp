#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_80171138_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x4];
    s16 unk_A0;
} S_80171138_0;   /* arg0 in func_8014D138 */

typedef struct S_80171138_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80171138_1;   /* arg3 in func_8014D138 */

typedef struct S_80171138_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80171138_2;   /* arg2 in func_8014D138 */


extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(u8, u8);
extern s32 func_8009FD7C(u8, u8, u8, u8);
extern s16 func_800A0818(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_8014D670(void *, void *);
extern void func_8014D82C(void *, void *, void *, void *);
extern s32 func_8014DF74(void *, void *, void *, void *);
extern void func_8014E138(void *, void *, void *, void *);
extern s32 func_8014E258(void *, void *, void *, s32);
extern void func_8014FD38(void *, void *, void *, void *);
extern void func_801500F4(void *, void *, void *, void *);

extern u8 D_8014D138[];
extern u8 D_80150AD4[];
extern u8 D_80150ADC[];
extern u8 D_80150AEC[];
extern u8 D_80150AF4[];
extern u8 D_80150AFC[];

/* Updates actor behavior, animation, and facing from its status and dungeon state. */
void func_8014D138(void *actor_in, void *context_in, void *sprite_in, void *stats_in)
{
    void *actor;
    void *context;
    void *sprite;
    void *stats;
    s32 angle_aux;
    s32 status_flags;
    s8 tile_index;
    u16 action_state;
    u32 dungeon_flags = dungeonStatus.flags;

    actor = actor_in;
    context = context_in;
    sprite = sprite_in;
    stats = stats_in;

    if (dungeon_flags & 0x1000) {
        ((S_80171138_0 *)actor)->unk_9A = 0xE;
        func_8014D670(actor_in, context_in);
        return;
    }

    if (((S_80171138_1 *)stats)->unk_25 == 0) {
        func_800AA79C(actor, context, sprite, stats);
        if (((S_80171138_2 *)sprite)->unk_2C == D_80150AFC) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80150AF4;
        func_80047784(sprite,
            D_80150AF4[((gameWork.view.viewAngle + ((S_80171138_1 *)stats)->unk_2A + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((S_80171138_1 *)stats)->unk_1C & 0x200) {
        if (((S_80171138_2 *)sprite)->unk_2C == D_80150AFC) {
            ((S_80171138_0 *)actor)->unk_9A = 0xD;
            ((S_80171138_0 *)actor)->unk_9B = 1;
            ((S_80171138_0 *)actor)->unk_8C = 0;
            ((S_80171138_1 *)stats)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(actor, context, sprite, D_80150AF4) != 0) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((S_80171138_1 *)stats)->unk_1C & 0x100) {
            func_800AA258(actor, context, sprite, stats);
            return;
        }

        if (((S_80171138_0 *)actor)->unk_9A != 0xE) {
            ((S_80171138_0 *)actor)->unk_9A = 0xE;
        }

        if (((S_80171138_2 *)sprite)->unk_2C != D_80150AD4) {
            ((S_80171138_0 *)actor)->unk_A0 = 0;
            (*(void * *)((u8 *)sprite + 0x2C)) = D_80150AD4;
            func_80047784(sprite,
                D_80150AD4[((gameWork.view.viewAngle + ((S_80171138_1 *)stats)->unk_2A + 0x100) >> 9) & 7],
                ((S_80171138_0 *)actor)->unk_A0);
        }

        ((S_80171138_1 *)stats)->unk_1C |= 0x40000;
        ((S_80171138_0 *)actor)->unk_98 &= 0xFFF7;

        if (((S_80171138_1 *)stats)->unk_64 != 0) {
            if (func_800AA6B4(actor, context, sprite, D_80150ADC) != 0) {
                return;
            }
        }

        if (((S_80171138_1 *)stats)->unk_1C & 0x80000) {
            func_800AA888(actor, context, sprite, stats);
            ((S_80171138_0 *)actor)->unk_A0 = 0;
            func_8014FD38(actor, context, sprite, stats);
            return;
        }

        if ((func_800A1C58(stats) << 16) != 0) {
            func_800AAB10(actor, context, sprite, stats);
        }
    }

    tile_index = func_8009FB34(((S_80171138_2 *)sprite)->unk_24.at00.v, ((S_80171138_2 *)sprite)->unk_24.at01.v);
    ((S_80171138_2 *)sprite)->unk_26 = tile_index;

    if (((S_80171138_1 *)stats)->unk_6D > 0) {
        if (((S_80171138_1 *)stats)->unk_1C & 0x20) {
            func_800A9A0C(stats);
            return;
        }
        if (!(((S_80171138_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX))) {
            action_state = ((S_80171138_1 *)stats)->unk_46;
            if (!(action_state & 0x8000)) {
                if (dungeonStatus.flags & 0x2000) {
                    if ((func_8009A180(stats,
                            (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                        return;
                    }
                }
                if ((func_8014E258(actor, context, sprite, 0) << 16) == 0) {
                    return;
                }
                action_state = ((S_80171138_1 *)stats)->unk_46 | 0x4000;
                ((S_80171138_1 *)stats)->unk_46 = action_state;
            }

            if (action_state & 0x8000) {
                switch (((S_80171138_1 *)stats)->unk_46 & 0x3FFF) {
                case 9:
                    func_801500F4(actor, context, sprite, stats);
                    return;

                case 8:
                    if ((func_8014DF74(actor, context, sprite, stats) << 16) != 0) {
                        return;
                    }
                    func_8014E138(actor, context, sprite, stats);
                    return;

                case 12:
                    func_800A9A0C(stats);
                    return;

                case 5:
                case 6:
                case 7:
                {
                    EntityRec *player;
                    s16 facing_angle;

                    facing_angle = func_800A0818(
                        ((S_80171138_2 *)sprite)->unk_24.at00.v, ((S_80171138_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &angle_aux);
                    player = D_800814A8;
                    ((S_80171138_1 *)stats)->unk_2A = facing_angle;
                    if (player->unk_9A != 0x11) {
                        func_800A9A0C(stats);
                        return;
                    }
                }

                case 1:
                case 2:
                case 3:
                    func_800AAF00(actor, context, sprite, D_80150AEC, D_8014D138);
                    return;

                case 4:
                case 10:
                case 11:
                default:
                    break;
                }
            }
        }
        func_8014D82C(actor, context, sprite, stats);
        return;
    }

    status_flags = ((S_80171138_1 *)stats)->unk_1C;
    if (status_flags & 0x2000) {
        return;
    }
    if (tile_index >= 0) {
        if (D_800E2970[tile_index].flags & 2) {
            return;
        }
    }
    if (status_flags & 0x430) {
        return;
    }

    {

        if ((func_8009FD7C(
                ((S_80171138_2 *)sprite)->unk_24.at00.v, ((S_80171138_2 *)sprite)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
            ((S_80171138_1 *)stats)->unk_2A = func_800A0818(
                ((S_80171138_2 *)sprite)->unk_24.at00.v, ((S_80171138_2 *)sprite)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY, &angle_aux);
        }
    }
    return;
}
