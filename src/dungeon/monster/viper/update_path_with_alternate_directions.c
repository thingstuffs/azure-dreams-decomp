#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct S_8017163C_1 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 pad_13[0x1];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x19];
    u8 unk_45;
    u16 unk_46;
    u8 pad_48[0x25];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x16];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_8017163C_1;   /* arg3 in update_path_with_alternate_directions */

typedef struct S_8017163C_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    union { s8 s; u8 u; } unk_26;   /* accessed as both */
} S_8017163C_2;   /* arg2 in update_path_with_alternate_directions */

typedef struct S_8017163C_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017163C_3_pre;   /* the 0x14 bytes before other in update_path_with_alternate_directions, addressed as other[-1] */

typedef struct S_8017163C_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8017163C_3;   /* other in update_path_with_alternate_directions */


typedef struct S_8017163C_5 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   /* accessed as both */
} S_8017163C_5;   /* arg0 in update_path_with_alternate_directions */

typedef struct S_8017163C_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017163C_7;   /* ((S_8017163C_3_pre *)other)[-1].unk_00 in update_path_with_alternate_directions */

typedef struct S_8017163C_8 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8017163C_8;   /* (u8 *)arg3 + (((S_8017163C_1 *)arg3)->unk_71.u & 0x7F) in update_path_with_alternate_directions */


typedef struct DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern s32 func_80171DFC(void *, void *, void *, void *);
extern void update_actor_status_and_food(void *);
extern void update_actor_proximity_flag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
extern void *find_valid_monster_neighbor(void *, u8, u8);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 generate_random_value(void);
extern void *place_actor_at_directional_neighbor(void *, u8, u8, s16);
extern s16 get_actor_height_difference(void *, void *);
extern s16 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height);
extern s16 compare_monster_neighbor_values(s32, s32, s32, s32);
extern void rebuild_monster_reachable_tiles(u8 *actor_held, s32 kind, u8 *work_p, u16 *out);
extern s16 check_movement_clearance_and_height(s16, void *, void *, s32);
extern void update_map_cell_flags_with_item_limit(s32, s32, s32);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern s16 check_entity_relation(void *, void *);
extern s16 sample_terrain_surface_height(s32, s32, s16);

extern s16 actor_turn_angle_offsets[];


/* Updates an actor's movement path, trying alternate directions around obstacles. */
void update_path_with_alternate_directions(void *move_ctx_in, void *action_ctx, void *position_in, void *actor_in)
{
    u16 dungeon_flags = g_dungeon_status.flags;
    s32 near_target = 0;
    register s16 stop_turning;
    s32 actor_flags;
    s32 trial_angle;
    s32 current_angle;
    u16 turn_flags;
    s16 turn_index;
    s16 *turn_table;
    s32 direction_offset;

    if ((dungeon_flags & 0x4000) || ((S_8017163C_1 *)actor_in)->unk_71.s >= 0) {
        if (((S_8017163C_1 *)actor_in)->unk_12 >= 2 ||
            (s16)func_80171DFC(move_ctx_in, action_ctx, position_in, actor_in) == 0) {
            update_actor_status_and_food(actor_in);
            return;
        }
        if (g_dungeon_status.active_actor == actor_in) {
            ((S_8017163C_1 *)actor_in)->unk_46 = 0xC008;
        }
        return;
    }

    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position_in, actor_in, 3, 6, (u8 *)move_ctx_in + 0x9C);
    actor_flags = ((S_8017163C_1 *)actor_in)->unk_1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)find_valid_monster_neighbor(actor_in, ((S_8017163C_2 *)position_in)->unk_24.at00.v,
                                  ((S_8017163C_2 *)position_in)->unk_24.at01.v);
            if (((void *)current_angle) != 0) {
                s16 target_angle = get_rounded_facing_and_rounding_flag(
                    ((S_8017163C_2 *)position_in)->unk_24.at00.v, ((S_8017163C_2 *)position_in)->unk_24.at01.v,
                    ((S_8017163C_7 *)(((S_8017163C_3_pre *)((void *)current_angle))[-1].unk_00))->unk_24,
                    ((S_8017163C_7 *)(((S_8017163C_3_pre *)((void *)current_angle))[-1].unk_00))->unk_25,
                    (u8 *)move_ctx_in + 0x98);
                ((S_8017163C_1 *)actor_in)->unk_2A.s = target_angle;
                ((S_8017163C_1 *)actor_in)->unk_71.u &= 0x7F;
                return;
            }
            if (!(((S_8017163C_1 *)actor_in)->unk_14 & 0x80000000)) {
                ((S_8017163C_1 *)actor_in)->unk_14 |= 0x80000000;
                ((S_8017163C_1 *)actor_in)->unk_2A.u +=
                    (generate_random_value() & 7) << 9;
            }
        } else if (place_actor_at_directional_neighbor(actor_in, ((S_8017163C_2 *)position_in)->unk_24.at00.v,
                          ((S_8017163C_2 *)position_in)->unk_24.at01.v,
                          ((S_8017163C_1 *)actor_in)->unk_2A.s) != 0) {
            ((S_8017163C_1 *)actor_in)->unk_71.u &= 0x7F;
            return;
        }
    } else if (actor_flags & 0x2000) {
        if (!(((S_8017163C_1 *)actor_in)->unk_46 & 0x8000)) {
            if (actor_flags & 0x20000) {
                s16 target_angle;
                s32 target_x;
                s32 target_y;
                u8 *move_flags;
                {
                    TileObject *target_position = &reference_tile_object;
                    s32 target_heading = ((u16)primary_actor_record->facing);
                    s32 table_index =
                        ((((S_8017163C_1 *)actor_in)->unk_45 + ((s16)target_heading >> 9)) & 7) << 1;
                    target_x = target_position->tile_position.parts.tile_x +
                        *(u16 *)((u8 *)((s8 *)dir_step_x) + table_index);
                    target_y = target_position->tile_position.parts.tile_y +
                        *(u16 *)((u8 *)((s8 *)dir_step_y) + table_index);
                }

                if (((S_8017163C_2 *)position_in)->unk_24.at00.v == (u16)target_x &&
                    ((S_8017163C_2 *)position_in)->unk_24.at01.v == (u16)target_y) {
                    ((S_8017163C_1 *)actor_in)->unk_71.u &= 0x7F;
                    return;
                }

                move_flags = (u8 *)move_ctx_in + 0x98;
                target_angle = get_rounded_facing_and_rounding_flag(
                    ((S_8017163C_2 *)position_in)->unk_24.at00.v, ((S_8017163C_2 *)position_in)->unk_24.at01.v,
                    (s16)target_x, (s16)target_y, move_flags);
                ((S_8017163C_1 *)actor_in)->unk_2A.s = target_angle;
                if (check_movement_clearance_and_height(target_angle, position_in, actor_in, 0x20) <= 0) {
                    ((S_8017163C_1 *)actor_in)->unk_2A.s = get_rounded_facing_and_rounding_flag(
                        ((S_8017163C_2 *)position_in)->unk_24.at00.v, ((S_8017163C_2 *)position_in)->unk_24.at01.v,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, move_flags);
                }
                if (compare_monster_neighbor_values(
                        ((S_8017163C_2 *)position_in)->unk_24.at00.v, ((S_8017163C_2 *)position_in)->unk_24.at01.v,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) != 0) {
                    near_target = 1;
                }
            } else {
                rebuild_monster_reachable_tiles(position_in, ((S_8017163C_5 *)move_ctx_in)->unk_9C.s, actor_in,
                              (u8 *)move_ctx_in + 0x98);
            }
        }
    } else {
        if (((S_8017163C_2 *)position_in)->unk_26.s >= 0 &&
            (((DungeonRecord *)dungeon_rooms + ((S_8017163C_2 *)position_in)->unk_26.s)->flags & 2)) {
            rebuild_monster_reachable_tiles(position_in, ((S_8017163C_5 *)move_ctx_in)->unk_9C.s, actor_in,
                          (u8 *)move_ctx_in + 0x98);
        } else if (!(((S_8017163C_1 *)actor_in)->unk_46 & 0x8000) &&
                   !(((S_8017163C_5 *)move_ctx_in)->unk_98 & 0x8000)) {
            current_angle = (s32)place_actor_at_directional_neighbor(actor_in, ((S_8017163C_2 *)position_in)->unk_24.at00.v,
                                  ((S_8017163C_2 *)position_in)->unk_24.at01.v,
                                  ((S_8017163C_1 *)actor_in)->unk_2A.s);
            if (((void *)current_angle) != 0 &&
                (((S_8017163C_3 *)((void *)current_angle))->unk_1C & 0x2000) &&
                (s16)get_actor_height_difference((void *)current_angle, actor_in) < 0x81) {
                if (check_diagonal_side_height(
                        ((s16)((S_8017163C_1 *)actor_in)->unk_2A.u >> 9) & 0xFFFF,
                        ((S_8017163C_2 *)position_in)->unk_24.at00.v, ((S_8017163C_2 *)position_in)->unk_24.at01.v,
                        (s16)(((S_8017163C_1 *)actor_in)->unk_88.u - 0x20)) != 0) {
                    ((S_8017163C_1 *)actor_in)->unk_71.u &= 0x7F;
                    return;
                }
            }

            if (((S_8017163C_1 *)actor_in)->unk_1C & 0x20000) {
                TileObject *target_position = &reference_tile_object;
                ((S_8017163C_1 *)actor_in)->unk_2A.s = get_rounded_facing_and_rounding_flag(
                    ((S_8017163C_2 *)position_in)->unk_24.at00.v, ((S_8017163C_2 *)position_in)->unk_24.at01.v,
                    target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y, (u8 *)move_ctx_in + 0x98);
                if (compare_monster_neighbor_values(
                        ((S_8017163C_2 *)position_in)->unk_24.at00.v, ((S_8017163C_2 *)position_in)->unk_24.at01.v,
                        target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y) != 0) {
                    if ((s16)get_actor_height_difference(primary_actor_record, actor_in) < 0x81) {
                        if (check_diagonal_side_height(
                                ((s16)((S_8017163C_1 *)actor_in)->unk_2A.u >> 9) & 0xFFFF,
                                ((S_8017163C_2 *)position_in)->unk_24.at00.v,
                                    ((S_8017163C_2 *)position_in)->unk_24.at01.v,
                                (s16)(((S_8017163C_1 *)actor_in)->unk_88.u - 0x20)) != 0) {
                            ((S_8017163C_1 *)actor_in)->unk_71.u &= 0x7F;
                            return;
                        }
                    }
                }
            } else {
                rebuild_monster_reachable_tiles(position_in, ((S_8017163C_5 *)move_ctx_in)->unk_9C.s, actor_in,
                              (u8 *)move_ctx_in + 0x98);
            }
        }
    }

    turn_index = -1;

    while (++turn_index < 8) {
        turn_flags = ((S_8017163C_5 *)move_ctx_in)->unk_98;
        current_angle = ((S_8017163C_1 *)actor_in)->unk_2A.s;
        if (turn_flags & 2) {
            trial_angle = current_angle - actor_turn_angle_offsets[turn_index];
        } else {
            trial_angle = current_angle + actor_turn_angle_offsets[turn_index];
        }

        if (check_movement_clearance_and_height(trial_angle, position_in, actor_in, 0x20) > 0) {
            if (turn_index >= 3) {
                stop_turning = near_target;
                if (stop_turning != 0) {
                    ((S_8017163C_1 *)actor_in)->unk_71.u &= 0x7F;
                    return;
                }
            }

            ((S_8017163C_1 *)actor_in)->unk_2A.s = trial_angle;
            ((S_8017163C_8 *)((u8 *)actor_in + (((S_8017163C_1 *)actor_in)->unk_71.u & 0x7F)))->unk_74 =
                ((S_8017163C_2 *)position_in)->unk_24.at00.v;
            ((S_8017163C_8 *)((u8 *)actor_in + (((S_8017163C_1 *)actor_in)->unk_71.u & 0x7F)))->unk_7C =
                ((S_8017163C_2 *)position_in)->unk_24.at01.v;
            ((S_8017163C_1 *)actor_in)->unk_71.u++;

            update_map_cell_flags_with_item_limit(
                ((S_8017163C_2 *)position_in)->unk_24.at00.v, ((S_8017163C_2 *)position_in)->unk_24.at01.v,
                (((S_8017163C_1 *)actor_in)->unk_1C & 0x2000) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                direction_offset = (((S_8017163C_1 *)actor_in)->unk_2A.u >> 8) & 0xE;
                x_step += direction_offset;
                ((S_8017163C_2 *)position_in)->unk_24.at00.v += *x_step;
                ((S_8017163C_2 *)position_in)->unk_24.at01.v += *((u8 *)((s8 *)dir_step_y) + direction_offset);
            }

            cycle_map_cell_flags(
                ((S_8017163C_2 *)position_in)->unk_24.at00.v, ((S_8017163C_2 *)position_in)->unk_24.at01.v,
                (((S_8017163C_1 *)actor_in)->unk_1C & 0x2000) ? 0x300 : 0x3000);
            break;
        }

        if (turn_index == 0 &&
            *(u16 *)(&reference_tile_object.tile_position.parts.tile_x) != ((S_8017163C_2 *)position_in)->unk_24.at00u.v) {
            if (check_entity_relation(actor_in,
                    (u8 *)primary_actor_record->unk_58 + 0x20) != 0) {
                return;
            }
        }

    }

    if (turn_index >= 8) {
        ((S_8017163C_1 *)actor_in)->unk_71.u &= 0x7F;
        ((S_8017163C_1 *)actor_in)->unk_46 &= 0x7FFF;
        update_actor_status_and_food(actor_in);
        return;
    }

    {
        ((S_8017163C_1 *)actor_in)->unk_46 &= 0x7FFF;
        ((S_8017163C_5 *)move_ctx_in)->unk_9C.u = ((S_8017163C_2 *)position_in)->unk_26.u;
        ((S_8017163C_1 *)actor_in)->unk_6D.u--;
        g_dungeon_status.activity_counts.parts.pending_movement_count++;
    }
    if (((S_8017163C_1 *)actor_in)->unk_6D.s == 0) {
        ((S_8017163C_1 *)actor_in)->unk_71.u &= 0x7F;
        return;
    }

    turn_index = sample_terrain_surface_height(
        (((S_8017163C_2 *)position_in)->unk_24.at00.v << 6) | 0x20,
        (((S_8017163C_2 *)position_in)->unk_24.at01.v << 6) | 0x20,
        (s16)(((S_8017163C_1 *)actor_in)->unk_88.u - 0x20));
    if (turn_index < 0x200) {
        ((S_8017163C_1 *)actor_in)->unk_88.s = turn_index;
    }
}
