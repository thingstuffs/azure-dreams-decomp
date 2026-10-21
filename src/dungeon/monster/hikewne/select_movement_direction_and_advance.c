#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"
#include "shared/actor_status.h"

typedef struct S_80171C34_1 {
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
} S_80171C34_1;   /* arg3 in select_movement_direction_and_advance */

typedef struct S_80171C34_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    union { s8 s; u8 u; } unk_26;   /* accessed as both */
} S_80171C34_2;   /* arg2 in select_movement_direction_and_advance */

   /* the 0x14 bytes before other in select_movement_direction_and_advance, addressed as other[-1] */

typedef struct S_80171C34_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80171C34_3;   /* other in select_movement_direction_and_advance */


typedef struct S_80171C34_5 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   /* accessed as both */
} S_80171C34_5;   /* arg0 in select_movement_direction_and_advance */

   /* ((S_80171C34_3_pre *)other)[-1].unk_00 in select_movement_direction_and_advance */

   /* (u8 *)arg3 + (((S_80171C34_1 *)arg3)->unk_71.u & 0x7F) in select_movement_direction_and_advance */


typedef struct DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern s32 validate_action_and_apply_effect(void *, void *, void *, void *);
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
extern s16 check_directional_move_and_terrain(s16, void *, void *, s32);
extern void update_map_cell_flags_with_item_limit(s32, s32, s32);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern s16 check_entity_relation(void *, void *);
extern s16 sample_terrain_surface_height(s32, s32, s16);

extern s16 actor_turn_angle_offsets[];


/* Selects a movement direction and updates the actor's position and movement state. */
void select_movement_direction_and_advance(void *move_data, void *context, void *position_data, void *actor_data)
{
    u16 dungeon_flags = g_dungeon_status.flags;
    s32 limit_detour = 0;
    s16 detour_check;
    s32 actor_flags;
    s32 trial_angle;
    s32 current_angle;
    u16 turn_flags;
    s16 turn_index;
    s16 *turn_table;
    s32 step_offset;

    if ((dungeon_flags & 0x4000) || ((S_80171C34_1 *)actor_data)->unk_71.s >= 0) {
        if (((S_80171C34_1 *)actor_data)->unk_12 >= 2 ||
            (s16)validate_action_and_apply_effect(move_data, context, position_data, actor_data) == 0) {
            update_actor_status_and_food(actor_data);
            return;
        }
        if (g_dungeon_status.active_actor == actor_data) {
            ((S_80171C34_1 *)actor_data)->unk_46 = 0xC008;
        }
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position_data, actor_data, 3, 6, (u8 *)move_data + 0x9C);
    actor_flags = ((S_80171C34_1 *)actor_data)->unk_1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)find_valid_monster_neighbor(actor_data, ((S_80171C34_2 *)position_data)->unk_24.at00.v,
                                  ((S_80171C34_2 *)position_data)->unk_24.at01.v);
            if (((void *)current_angle) != 0) {
                s16 target_angle = get_rounded_facing_and_rounding_flag(
                    ((S_80171C34_2 *)position_data)->unk_24.at00.v, ((S_80171C34_2 *)position_data)->unk_24.at01.v,
                    ((MovingTile *)(((SpriteLinkPrefixView *)((void *)current_angle))[-1].unk_00))->unk_24,
                    ((MovingTile *)(((SpriteLinkPrefixView *)((void *)current_angle))[-1].unk_00))->unk_25,
                    (u8 *)move_data + 0x98);
                ((S_80171C34_1 *)actor_data)->unk_2A.s = target_angle;
                ((S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
            if (!(((S_80171C34_1 *)actor_data)->unk_14 & 0x80000000)) {
                ((S_80171C34_1 *)actor_data)->unk_14 |= 0x80000000;
                ((S_80171C34_1 *)actor_data)->unk_2A.u +=
                    (generate_random_value() & 7) << 9;
            }
        } else {
            if (place_actor_at_directional_neighbor(actor_data, ((S_80171C34_2 *)position_data)->unk_24.at00.v,
                              ((S_80171C34_2 *)position_data)->unk_24.at01.v,
                              ((S_80171C34_1 *)actor_data)->unk_2A.s) != 0) {
                ((S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(((S_80171C34_1 *)actor_data)->unk_46 & 0x8000)) {
            if (actor_flags & 0x20000) {
                s16 target_angle;
                s32 target_x;
                s32 target_y;
                u8 *turn_data;
                {
                    TileObject *target_position = &reference_tile_object;
                    s32 target_facing = ((u16)primary_actor_record->facing);
                    s32 offset_index =
                        ((((S_80171C34_1 *)actor_data)->unk_45 + ((s16)target_facing >> 9)) & 7) << 1;
                    target_x = target_position->tile_position.parts.tile_x +
                        *(u16 *)((u8 *)((s8 *)dir_step_x) + offset_index);
                    target_y = target_position->tile_position.parts.tile_y +
                        *(u16 *)((u8 *)((s8 *)dir_step_y) + offset_index);
                }

                if (((S_80171C34_2 *)position_data)->unk_24.at00.v == (u16)target_x &&
                    ((S_80171C34_2 *)position_data)->unk_24.at01.v == (u16)target_y) {
                    ((S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                    return;
                }

                turn_data = (u8 *)move_data + 0x98;
                target_angle = get_rounded_facing_and_rounding_flag(
                    ((S_80171C34_2 *)position_data)->unk_24.at00.v, ((S_80171C34_2 *)position_data)->unk_24.at01.v,
                    (s16)target_x, (s16)target_y, turn_data);
                ((S_80171C34_1 *)actor_data)->unk_2A.s = target_angle;
                if (check_directional_move_and_terrain(target_angle, position_data, actor_data, 0x20) <= 0) {
                    ((S_80171C34_1 *)actor_data)->unk_2A.s = get_rounded_facing_and_rounding_flag(
                        ((S_80171C34_2 *)position_data)->unk_24.at00.v, ((S_80171C34_2 *)position_data)->unk_24.at01.v,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, turn_data);
                }
                if (compare_monster_neighbor_values(
                        ((S_80171C34_2 *)position_data)->unk_24.at00.v, ((S_80171C34_2 *)position_data)->unk_24.at01.v,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) != 0) {
                    limit_detour = 1;
                }
            } else {
                rebuild_monster_reachable_tiles(position_data, ((S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                              (u8 *)move_data + 0x98);
            }
        }
    } else if (((S_80171C34_2 *)position_data)->unk_26.s >= 0 &&
               ((DungeonRecord *)dungeon_rooms)[((S_80171C34_2 *)position_data)->unk_26.s].flags & 2) {
        rebuild_monster_reachable_tiles(position_data, ((S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                      (u8 *)move_data + 0x98);
    } else if (!(((S_80171C34_1 *)actor_data)->unk_46 & 0x8000)) {
        current_angle = (s32)place_actor_at_directional_neighbor(actor_data, ((S_80171C34_2 *)position_data)->unk_24.at00.v,
                              ((S_80171C34_2 *)position_data)->unk_24.at01.v,
                              ((S_80171C34_1 *)actor_data)->unk_2A.s);
        if (((void *)current_angle) != 0 &&
            (((S_80171C34_3 *)((void *)current_angle))->unk_1C & 0x2000) &&
            (s16)get_actor_height_difference((void *)current_angle, actor_data) < 0x81) {
            if (check_diagonal_side_height(
                    ((s16)((S_80171C34_1 *)actor_data)->unk_2A.u >> 9) & 0xFFFF,
                    ((S_80171C34_2 *)position_data)->unk_24.at00.v, ((S_80171C34_2 *)position_data)->unk_24.at01.v,
                    (s16)(((S_80171C34_1 *)actor_data)->unk_88.u - 0x20)) != 0) {
                ((S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
        }

        if (((S_80171C34_1 *)actor_data)->unk_1C & 0x20000) {
            TileObject *target_position = &reference_tile_object;
            ((S_80171C34_1 *)actor_data)->unk_2A.s = get_rounded_facing_and_rounding_flag(
                ((S_80171C34_2 *)position_data)->unk_24.at00.v, ((S_80171C34_2 *)position_data)->unk_24.at01.v,
                target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y, (u8 *)move_data + 0x98);
            if (compare_monster_neighbor_values(
                    ((S_80171C34_2 *)position_data)->unk_24.at00.v, ((S_80171C34_2 *)position_data)->unk_24.at01.v,
                    target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y) != 0) {
                if (get_actor_height_difference(primary_actor_record, actor_data) < 0x81) {
                    if (check_diagonal_side_height(
                            ((s16)((S_80171C34_1 *)actor_data)->unk_2A.u >> 9) & 0xFFFF,
                            ((S_80171C34_2 *)position_data)->unk_24.at00.v,
                                ((S_80171C34_2 *)position_data)->unk_24.at01.v,
                            (s16)(((S_80171C34_1 *)actor_data)->unk_88.u - 0x20)) != 0) {
                        ((S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                        return;
                    }
                }
            }
        } else {
            rebuild_monster_reachable_tiles(position_data, ((S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                          (u8 *)move_data + 0x98);
        }
    }

    turn_index = 0;
    turn_table = actor_turn_angle_offsets;

    do {
        turn_flags = ((S_80171C34_5 *)move_data)->unk_98;
        current_angle = ((S_80171C34_1 *)actor_data)->unk_2A.s;
        if (turn_flags & 2) {
            trial_angle = current_angle - turn_table[turn_index];
        } else {
            trial_angle = current_angle + turn_table[turn_index];
        }

        if (check_directional_move_and_terrain(trial_angle, position_data, actor_data, 0x20) > 0) {
            if (turn_index >= 3) {
                detour_check = limit_detour;
                if (detour_check != 0) {
                    ((S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                    return;
                }
            }

            ((S_80171C34_1 *)actor_data)->unk_2A.s = trial_angle;
            ((ActorStatusBytesView *)((u8 *)actor_data + (((S_80171C34_1 *)actor_data)->unk_71.u & 0x7F)))->unk_74 =
                ((S_80171C34_2 *)position_data)->unk_24.at00.v;
            ((ActorStatusBytesView *)((u8 *)actor_data + (((S_80171C34_1 *)actor_data)->unk_71.u & 0x7F)))->unk_7C =
                ((S_80171C34_2 *)position_data)->unk_24.at01.v;
            ((S_80171C34_1 *)actor_data)->unk_71.u++;

            update_map_cell_flags_with_item_limit(
                ((S_80171C34_2 *)position_data)->unk_24.at00.v, ((S_80171C34_2 *)position_data)->unk_24.at01.v,
                (((S_80171C34_1 *)actor_data)->unk_1C & 0x2000) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                step_offset = (((S_80171C34_1 *)actor_data)->unk_2A.u >> 8) & 0xE;
                x_step += step_offset;
                ((S_80171C34_2 *)position_data)->unk_24.at00.v += *x_step;
                ((S_80171C34_2 *)position_data)->unk_24.at01.v += *((u8 *)((s8 *)dir_step_y) + step_offset);
            }

            cycle_map_cell_flags(
                ((S_80171C34_2 *)position_data)->unk_24.at00.v, ((S_80171C34_2 *)position_data)->unk_24.at01.v,
                (((S_80171C34_1 *)actor_data)->unk_1C & 0x2000) ? 0x300 : 0x3000);
            break;
        }

        if (turn_index == 0 &&
            *(u16 *)(&reference_tile_object.tile_position.parts.tile_x) != ((S_80171C34_2 *)position_data)->unk_24.at00u.v) {
            if (check_entity_relation(actor_data,
                    (u8 *)primary_actor_record->unk_58 + 0x20) != 0) {
                do {
                    return;
                } while (0);
            }
        }

        turn_index++;
        if (turn_index >= 8) {
            break;
        }
    } while (1);

    if (turn_index >= 8) {
        ((S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
        ((S_80171C34_1 *)actor_data)->unk_46 &= 0x7FFF;
        update_actor_status_and_food(actor_data);
        return;
    }

    {
        ((S_80171C34_1 *)actor_data)->unk_46 &= 0x7FFF;
        ((S_80171C34_5 *)move_data)->unk_9C.u = ((S_80171C34_2 *)position_data)->unk_26.u;
        ((S_80171C34_1 *)actor_data)->unk_6D.u--;
        g_dungeon_status.activity_counts.parts.pending_movement_count++;
    }
    if (((S_80171C34_1 *)actor_data)->unk_6D.s == 0) {
        ((S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
        return;
    }

    turn_index = sample_terrain_surface_height(
        (((S_80171C34_2 *)position_data)->unk_24.at00.v << 6) | 0x20,
        (((S_80171C34_2 *)position_data)->unk_24.at01.v << 6) | 0x20,
        (s16)(((S_80171C34_1 *)actor_data)->unk_88.u - 0x20));
    if (turn_index < 0x200) {
        ((S_80171C34_1 *)actor_data)->unk_88.s = turn_index;
    }
}
