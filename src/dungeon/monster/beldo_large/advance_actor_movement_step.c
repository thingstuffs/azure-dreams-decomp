#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/dungeon_moving_views.h"
#include "shared/actor_status.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8016B230_1 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 pad_13[0x1];
    s32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x19];
    u8 unk_45;
    u16 unk_46;
    u8 pad_48[0x25];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x16];
    u16 unk_88;
} S_8016B230_1;   /* arg3 in advance_actor_movement_step */

typedef struct S_8016B230_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    union { s8 s; u8 u; } unk_26;   /* accessed as both */
} S_8016B230_2;   /* arg2 in advance_actor_movement_step */

typedef struct S_8016B230_3_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_8016B230_3_pre;   /* the 0x14 bytes before found in advance_actor_movement_step, addressed as found[-1] */

typedef struct S_8016B230_3 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_8016B230_3;   /* found in advance_actor_movement_step */

   /* object in advance_actor_movement_step */

typedef struct S_8016B230_5 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   /* accessed as both */
    u8 pad_9D[0x12];
    u8 unk_AF;
} S_8016B230_5;   /* arg0 in advance_actor_movement_step */


typedef struct S_8016B230_10 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_8016B230_10;   /* kind_table + kind * 0x14 in advance_actor_movement_step */

typedef struct S_8016B230_11 {
    u16 unk_00;
} S_8016B230_11;   /* &D_80082EA4 in advance_actor_movement_step */

   /* arg3 + (((S_8016B230_1 *)arg3)->unk_71.u & 0x7F) in advance_actor_movement_step */


struct ActorRecord; s32 check_entity_relation(struct ActorRecord *, struct ActorRecord *);
void cycle_map_cell_flags(s16, s16, u16);
#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"
s32 check_diagonal_side_height(s32, s16, s16, s16);
extern s32 check_movement_clearance_and_height();
s32 compare_monster_neighbor_values(s32, s32, s32, s32);
s16 get_actor_height_difference(struct ActorRecord *, struct ActorRecord *);
extern void *find_valid_monster_neighbor();
extern void *place_actor_at_directional_neighbor();
extern u16 get_rounded_facing_and_rounding_flag();
s32 rebuild_monster_reachable_tiles(u8 *, s32, u8 *, u16 *);
s32 update_actor_proximity_flag(void *, void *, s32, s32, s8 *);
extern s32 generate_random_value();
void update_actor_status_and_food(struct ActorRecord *);
extern s16 sample_terrain_surface_height();
struct Rec_D_80082E80; struct Rec_func_800A9E70_arg0; s32 try_actor_attack(struct Rec_func_800A9E70_arg0 *, s32, struct Rec_D_80082E80 *, struct ActorRecord *);

extern s16 D_8006CD00[];

/* Select a movement direction, record the previous tile, and update the actor position and height. */
void advance_actor_movement_step(u8 *movement_in, void *action_ctx, u8 *position, u8 *actor) {
    u16 near_target;
    u8 target_nearby = 0;
    s32 height_result;
    s32 attempt;
    register u8 *x_offsets;
    DungeonGlobalStatus *dungeon_state;
    DungeonGlobalStatus *turn_state;
    u32 dungeon_flags;
    u32 actor_flags;
    s32 path_result;
    s32 random_bits;
    s32 direction_offset;
    s32 moved;
    s32 tile_mask;
    s32 base_angle;
    s16 move_angle;
    u8 next_x;
    s32 next_y;
    void *found;
    u8 *object;

    dungeon_state = &g_dungeon_status;
    dungeon_flags = dungeon_state->flags;
    near_target = 0;

    if ((dungeon_flags & 0x4000) || (((S_8016B230_1 *)actor)->unk_71.s >= 0)) {
        if ((((S_8016B230_1 *)actor)->unk_12 >= 2) ||
            ((try_actor_attack((struct Rec_func_800A9E70_arg0 *)(movement_in), (s32)(action_ctx), (struct Rec_D_80082E80 *)(position), (struct ActorRecord *)(actor)) << 16) == 0)) {
            update_actor_status_and_food((struct ActorRecord *)(actor));
            return;
        }
        if (dungeon_state->active_actor != actor) {
            return;
        }
        ((S_8016B230_1 *)actor)->unk_46 = 0xC008;
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position, actor, 3, 6, movement_in + 0x9C);
    actor_flags = ((S_8016B230_1 *)actor)->unk_1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            found = find_valid_monster_neighbor(actor, ((S_8016B230_2 *)position)->unk_24.at00.v,
                ((S_8016B230_2 *)position)->unk_24.at01.v);
            if (found != NULL) {
                object = ((S_8016B230_3_pre *)found)[-1].unk_00;
                ((S_8016B230_1 *)actor)->unk_2A.u = get_rounded_facing_and_rounding_flag(
                    ((S_8016B230_2 *)position)->unk_24.at00.v, ((S_8016B230_2 *)position)->unk_24.at01.v,
                    ((MovingTile *)object)->unk_24, ((MovingTile *)object)->unk_25, movement_in + 0x98);
                ((S_8016B230_1 *)actor)->unk_71.u &= 0x7F;
                return;
            }
            {
                s32 object_status;

                object_status = ((S_8016B230_1 *)actor)->unk_14;
                if (!(object_status & 0x80000000)) {
                    object_status |= 0x80000000;
                    ((S_8016B230_1 *)actor)->unk_14 = object_status;
                    random_bits = generate_random_value();
                    ((S_8016B230_1 *)actor)->unk_2A.u += (random_bits & 7) << 9;
                }
            }
        } else {
            found = place_actor_at_directional_neighbor(actor, ((S_8016B230_2 *)position)->unk_24.at00.v,
                ((S_8016B230_2 *)position)->unk_24.at01.v,
                                  ((S_8016B230_1 *)actor)->unk_2A.s);
            if (found != NULL) {
                ((S_8016B230_1 *)actor)->unk_71.u &= 0x7F;
                return;
            }
        }
    } else if (((S_8016B230_5 *)movement_in)->unk_AF) {
        if (!(((S_8016B230_1 *)actor)->unk_46 & 0x8000)) {
            if (actor_flags & 0x20000) {
                s32 direction;
                s16 target_x;
                s32 target_y;
                s16 new_angle;
                TileObject *target;

                target = &D_80082E80;
                direction = (((S_8016B230_1 *)actor)->unk_45 +
                             ((s32)(((u16)D_800814A8->facing) << 16) >> 25)) & 7;
                target_x = target->tile_position.parts.tile_x +
                           ((u16 *)((s8 *)dir_step_x))[direction];
                target_y = target->tile_position.parts.tile_y +
                           ((u16 *)((s8 *)dir_step_y))[direction];
                if ((((S_8016B230_2 *)position)->unk_24.at00.v == (u16)target_x) &&
                    (((S_8016B230_2 *)position)->unk_24.at01.v == (u16)target_y)) {
                    ((S_8016B230_1 *)actor)->unk_71.u &= 0x7F;
                    return;
                }
                new_angle = get_rounded_facing_and_rounding_flag(((S_8016B230_2 *)position)->unk_24.at00.v,
                    ((S_8016B230_2 *)position)->unk_24.at01.v,
                                          target_x, (s16)target_y, movement_in + 0x98);
                ((S_8016B230_1 *)actor)->unk_2A.u = new_angle;
                if ((check_movement_clearance_and_height(new_angle, position, actor, 0x20) << 16) <= 0) {
                    TileObject *retry_target = &D_80082E80;

                    ((S_8016B230_1 *)actor)->unk_2A.u = get_rounded_facing_and_rounding_flag(
                        ((S_8016B230_2 *)position)->unk_24.at00.v, ((S_8016B230_2 *)position)->unk_24.at01.v,
                        retry_target->tile_position.parts.tile_x, retry_target->tile_position.parts.tile_y,
                        movement_in + 0x98);
                }
                {
                    TileObject *check_target = &D_80082E80;

                    if ((compare_monster_neighbor_values(((S_8016B230_2 *)position)->unk_24.at00.v,
                        ((S_8016B230_2 *)position)->unk_24.at01.v,
                                       check_target->tile_position.parts.tile_x,
                                       check_target->tile_position.parts.tile_y) << 16) != 0) {
                        near_target = 1;
                    }
                }
            } else {
                rebuild_monster_reachable_tiles(position, ((S_8016B230_5 *)movement_in)->unk_9C.s, actor, (u16 *)(movement_in + 0x98));
            }
        }
    } else {
        s32 kind;

        kind = ((S_8016B230_2 *)position)->unk_26.s;
        if ((kind >= 0) && (((S_8016B230_10 *)((u8 *)D_800E2970 + kind * 0x14))->unk_0C & 2)) {
            rebuild_monster_reachable_tiles(position, ((S_8016B230_5 *)movement_in)->unk_9C.s, actor, (u16 *)(movement_in + 0x98));
        } else if (!(((S_8016B230_1 *)actor)->unk_46 & 0x8000)) {
            found = place_actor_at_directional_neighbor(actor, ((S_8016B230_2 *)position)->unk_24.at00.v,
                ((S_8016B230_2 *)position)->unk_24.at01.v,
                                  ((S_8016B230_1 *)actor)->unk_2A.s);
            if ((found != NULL) && (((S_8016B230_3 *)found)->unk_1C & 0x2000) &&
                (get_actor_height_difference(found, (struct ActorRecord *)(actor)) < 0x81) &&
                ((check_diagonal_side_height(((s32)(((S_8016B230_1 *)actor)->unk_2A.u << 16) >> 25) & 0xFFFF,
                                ((S_8016B230_2 *)position)->unk_24.at00.v, ((S_8016B230_2 *)position)->unk_24.at01.v,
                                (s16)(((S_8016B230_1 *)actor)->unk_88 - 0x20)) << 16) != 0)) {
                ((S_8016B230_1 *)actor)->unk_71.u &= 0x7F;
                return;
            }
            if (((S_8016B230_1 *)actor)->unk_1C & 0x20000) {
                TileObject *target = &D_80082E80;
                ((S_8016B230_1 *)actor)->unk_2A.u = get_rounded_facing_and_rounding_flag(
                    ((S_8016B230_2 *)position)->unk_24.at00.v, ((S_8016B230_2 *)position)->unk_24.at01.v,
                    target->tile_position.parts.tile_x, target->tile_position.parts.tile_y, movement_in + 0x98);
                if ((compare_monster_neighbor_values(((S_8016B230_2 *)position)->unk_24.at00.v, ((S_8016B230_2 *)position)->unk_24.at01.v,
                                   target->tile_position.parts.tile_x, target->tile_position.parts.tile_y) << 16) != 0) {
                    if (get_actor_height_difference(D_800814A8, (struct ActorRecord *)(actor)) < 0x81) {
                        path_result = check_diagonal_side_height(
                            ((s32)(((S_8016B230_1 *)actor)->unk_2A.u << 16) >> 25) & 0xFFFF,
                            ((S_8016B230_2 *)position)->unk_24.at00.v, ((S_8016B230_2 *)position)->unk_24.at01.v,
                            (s16)(((S_8016B230_1 *)actor)->unk_88 - 0x20));
                        if ((path_result << 16) != 0) {
                            ((S_8016B230_1 *)actor)->unk_71.u &= 0x7F;
                            return;
                        }
                    }
                }
            } else {
                rebuild_monster_reachable_tiles(position, ((S_8016B230_5 *)movement_in)->unk_9C.s, actor, (u16 *)(movement_in + 0x98));
            }
        }
    }
    attempt = 0;
    x_offsets = (u8 *)((s8 *)dir_step_x);

    do {
        base_angle = (s32)((S_8016B230_1 *)actor)->unk_2A.s;
        if (((S_8016B230_5 *)movement_in)->unk_98 & 2) {
            {
                s32 angle_delta = (s32)D_8006CD00[attempt];

                move_angle = (s16)(base_angle - angle_delta);
            }
        } else {
            {
                s32 angle_delta = (s32)D_8006CD00[attempt];

                move_angle = (s16)(base_angle + angle_delta);
            }
        }
        if ((check_movement_clearance_and_height(move_angle, position, actor, 0x20) << 16) > 0) {
            if (attempt >= 3) {
                target_nearby = near_target;

                if (target_nearby) {
                    ((S_8016B230_1 *)actor)->unk_71.u &= 0x7F;
                    return;
                }
            }
            ((S_8016B230_1 *)actor)->unk_2A.u = move_angle;
            ((ActorStatusBytesView *)(actor + (((S_8016B230_1 *)actor)->unk_71.u & 0x7F)))->unk_74 =
                ((S_8016B230_2 *)position)->unk_24.at00.v;
            ((ActorStatusBytesView *)(actor + (((S_8016B230_1 *)actor)->unk_71.u & 0x7F)))->unk_7C =
                ((S_8016B230_2 *)position)->unk_24.at01.v;
            ((S_8016B230_1 *)actor)->unk_71.u++;
            update_map_cell_flags_with_item_limit(((S_8016B230_2 *)position)->unk_24.at00.v, ((S_8016B230_2 *)position)->unk_24.at01.v,
                          (((S_8016B230_1 *)actor)->unk_1C & 0x2000) ? 0x300 : 0x3000);
            direction_offset = (((S_8016B230_1 *)actor)->unk_2A.u >> 8) & 0xE;
            ((S_8016B230_2 *)position)->unk_24.at00.v +=
                *((u8 *)((u32)direction_offset + (u32)x_offsets));
            ((S_8016B230_2 *)position)->unk_24.at01.v += *((u8 *)((s8 *)dir_step_y) + direction_offset);
            next_x = ((S_8016B230_2 *)position)->unk_24.at00.v;
            next_y = ((S_8016B230_2 *)position)->unk_24.at01.v;
            tile_mask = 0x3000;
            if (((S_8016B230_1 *)actor)->unk_1C & 0x2000) {
                tile_mask = 0x300;
            }
            cycle_map_cell_flags(next_x, next_y, tile_mask);
            break;
        }
        if (attempt == 0) {
            if ((((S_8016B230_11 *)(((s8 *)&D_80082E80.tile_position.parts.tile_x)))->unk_00 != ((S_8016B230_2 *)position)->unk_24.at00u.v)
                &&
                ((s16)check_entity_relation((struct ActorRecord *)(actor), (struct ActorRecord *)(((s32)D_800814A8->unk_58) + 0x20)) != 0)) {
                return;
            }
        }
        attempt++;
    } while (attempt < 8);
    moved = attempt < 8;
    if (!moved) {
        ((S_8016B230_1 *)actor)->unk_71.u &= 0x7F;
        ((S_8016B230_1 *)actor)->unk_46 &= 0x7FFF;
        update_actor_status_and_food((struct ActorRecord *)(actor));
        return;
    }
    turn_state = &g_dungeon_status;
    ((S_8016B230_1 *)actor)->unk_46 &= 0x7FFF;
    ((S_8016B230_5 *)movement_in)->unk_9C.u = ((S_8016B230_2 *)position)->unk_26.u;
    ((S_8016B230_1 *)actor)->unk_6D.u--;
    turn_state->activity_counts.parts.pending_movement_count++;
    if (((S_8016B230_1 *)actor)->unk_6D.s == 0) {
        ((S_8016B230_1 *)actor)->unk_71.u &= 0x7F;
        return;
    }

    height_result = sample_terrain_surface_height((((S_8016B230_2 *)position)->unk_24.at00.v << 6) | 0x20,
                      (((S_8016B230_2 *)position)->unk_24.at01.v << 6) | 0x20,
                      (s16)(((S_8016B230_1 *)actor)->unk_88 - 0x20));
    attempt = height_result;
    if (attempt < 0x200) {
        ((S_8016B230_1 *)actor)->unk_88 = attempt;
    }
    return;

    return;
}
