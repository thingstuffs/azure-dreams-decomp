#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
extern int abs(int);

typedef struct S_801715F4_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    void * unk_0C;
} S_801715F4_0;   /* global in advance_actor_path_with_item_search */

typedef struct S_801715F4_1 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 pad_13[0x1];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
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
} S_801715F4_1;   /* arg3 in advance_actor_path_with_item_search */

typedef struct S_801715F4_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    union { s8 s; u8 u; } unk_26;   /* accessed as both */
} S_801715F4_2;   /* arg2 in advance_actor_path_with_item_search */

typedef struct S_801715F4_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801715F4_3_pre;   /* the 0x14 bytes before found in advance_actor_path_with_item_search, addressed as found[-1] */

typedef struct S_801715F4_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_801715F4_3;   /* found in advance_actor_path_with_item_search */

typedef struct S_801715F4_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801715F4_4;   /* other in advance_actor_path_with_item_search */

typedef struct S_801715F4_6 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_801715F4_6;   /* monster_table + index * 0x14 in advance_actor_path_with_item_search */

typedef struct S_801715F4_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801715F4_7;   /* held_origin in advance_actor_path_with_item_search */

typedef struct S_801715F4_8 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   /* accessed as both */
} S_801715F4_8;   /* arg0 in advance_actor_path_with_item_search */

typedef struct S_801715F4_9 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_801715F4_9;   /* counter_state in advance_actor_path_with_item_search */

typedef struct S_801715F4_10 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_801715F4_10;   /* (u8 *)arg3 + (((S_801715F4_1 *)arg3)->unk_71.u & 0x7F) in advance_actor_path_with_item_search */

extern s32 check_entity_relation(void *, void *);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern void update_map_cell_flags_with_item_limit(u8, u8, s32);
extern s32 check_diagonal_side_height(s32, u8, u8, s16);
extern s16 check_movement_clearance_and_height(s16, void *, void *, s32);
extern s32 compare_monster_neighbor_values(u8, u8, u8, u8);
extern s16 get_actor_height_difference(void *, void *);
extern void *find_valid_monster_neighbor(void *, u8, u8);
extern void *place_actor_at_directional_neighbor(void *, u8, u8, s16);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void rebuild_monster_reachable_tiles(u8 *actor_held, s32 kind, u8 *work_p, u16 *out);
extern void update_actor_proximity_flag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
extern s32 generate_random_value(void);
extern s16 find_nearest_floor_item_in_room(void *, s32, s16 *, s16 *);
extern void update_actor_status_and_food(void *);
extern s16 sample_terrain_surface_height(s32, s32, s16);
extern s16 func_80171EBC(void *, void *, void *, void *);

extern s8 D_8006CD00;
extern u8 D_80082E80_b[];

/* Chooses a movement direction, advances the actor, and updates its movement history. */
void advance_actor_path_with_item_search(void *move_state, void *caller_context, void *position_arg, void *actor_arg) {
    s16 target_x;
    s16 target_y;
    s16 turn_index;
    s32 next_angle;
    s32 limit_turns;
    s32 flags;
    s32 follow_x;
    s32 follow_y;
    s32 target_x_wide;
    s32 dx;
    s32 dy;
    u32 table_offset;
    void *angle;
    DungeonGlobalStatus *dungeon_state = &g_dungeon_status;
    u8 *angle_context;
    u8 *follow_context;
    s16 *turn_table;

    limit_turns = 0;
    flags = dungeon_state->flags;
    if ((flags & 0x4000) || (((S_801715F4_1 *)actor_arg)->unk_71.s >= 0)) {
        if ((((S_801715F4_1 *)actor_arg)->unk_12 >= 2) ||
            ((s16)func_80171EBC(move_state, caller_context, position_arg, actor_arg) == 0)) {
            update_actor_status_and_food(actor_arg);
            return;
        }
        if (dungeon_state->active_actor == actor_arg) {
            ((S_801715F4_1 *)actor_arg)->unk_46 = 0xC008;
        }
        return;
    }

    if (!(flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position_arg, actor_arg, 3, 6, (u8 *)move_state + 0x9C);
    flags = ((S_801715F4_1 *)actor_arg)->unk_1C;
    if (flags & 0x410) {
        if (flags & 0x400) {
            angle = find_valid_monster_neighbor(actor_arg, ((S_801715F4_2 *)position_arg)->unk_24.at00.v,
                                  ((S_801715F4_2 *)position_arg)->unk_24.at01.v);
            if (angle != 0) {
                S_801715F4_4 *other = ((S_801715F4_3_pre *)angle)[-1].unk_00;

                ((S_801715F4_1 *)actor_arg)->unk_2A.u = get_rounded_facing_and_rounding_flag(
                    ((S_801715F4_2 *)position_arg)->unk_24.at00.v, ((S_801715F4_2 *)position_arg)->unk_24.at01.v,
                    other->unk_24, other->unk_25,
                    (u8 *)move_state + 0x98);
                ((S_801715F4_1 *)actor_arg)->unk_71.u &= 0x7F;
                return;
            }
            {
                s32 sign_mask = 0x80000000;
                s32 state_flags;

                state_flags = ((S_801715F4_1 *)actor_arg)->unk_14;
                if (state_flags >= 0) {
                    state_flags |= sign_mask;
                    ((S_801715F4_1 *)actor_arg)->unk_14 = state_flags;
                    sign_mask = generate_random_value();
                    ((S_801715F4_1 *)actor_arg)->unk_2A.u += (sign_mask & 7) << 9;
                }
            }
        } else {
            angle = place_actor_at_directional_neighbor(actor_arg, ((S_801715F4_2 *)position_arg)->unk_24.at00.v,
                                  ((S_801715F4_2 *)position_arg)->unk_24.at01.v,
                                  ((S_801715F4_1 *)actor_arg)->unk_2A.s);
            if (angle != 0) {
                ((S_801715F4_1 *)actor_arg)->unk_71.u &= 0x7F;
                return;
            }
        }
    } else if (flags & 0x2000) {
        turn_index = 0;
        if (!(((S_801715F4_1 *)actor_arg)->unk_46 & 0x8000)) {
            if (!(flags & 0x20000)) {
                rebuild_monster_reachable_tiles(position_arg, ((S_801715F4_8 *)move_state)->unk_9C.s, actor_arg,
                              (u8 *)move_state + 0x98);
            } else {
                {
                    u32 follow_offset;

                    follow_offset =
                        ((((S_801715F4_1 *)actor_arg)->unk_45 +
                          ((s32)(((u16)D_800814A8->facing) << 16) >> 25)) &
                         7) *
                        2;

                    follow_x = D_80082E80.tile_position.parts.tile_x + *(u16 *)((u8 *)((s8 *)dir_step_x) + follow_offset);
                    follow_y = D_80082E80.tile_position.parts.tile_y + *(u16 *)((u8 *)((s8 *)dir_step_y) + follow_offset);
                }
                target_x = follow_x;
                target_y = follow_y;

                if ((((S_801715F4_2 *)position_arg)->unk_24.at00.v == (u16)follow_x) &&
                    (((S_801715F4_2 *)position_arg)->unk_24.at01.v == (u16)follow_y)) {
                    ((S_801715F4_1 *)actor_arg)->unk_71.u &= 0x7F;
                    return;
                }

                ((S_801715F4_1 *)actor_arg)->unk_2A.u = get_rounded_facing_and_rounding_flag(
                    ((S_801715F4_2 *)position_arg)->unk_24.at00.v, ((S_801715F4_2 *)position_arg)->unk_24.at01.v, target_x,
                        target_y,
                    angle_context = (u8 *)move_state + 0x98);
                if (check_movement_clearance_and_height(((S_801715F4_1 *)actor_arg)->unk_2A.s, position_arg, actor_arg, 0x20) <=
                    0) {
                    ((S_801715F4_1 *)actor_arg)->unk_2A.u = get_rounded_facing_and_rounding_flag(
                        ((S_801715F4_2 *)position_arg)->unk_24.at00.v, ((S_801715F4_2 *)position_arg)->unk_24.at01.v,
                        D_80082E80_b[0x24], D_80082E80_b[0x25],
                        angle_context);
                }
                {
                    s16 path_ok = compare_monster_neighbor_values(((S_801715F4_2 *)position_arg)->unk_24.at00.v,
                                                ((S_801715F4_2 *)position_arg)->unk_24.at01.v,
                                                D_80082E80_b[0x24],
                                                D_80082E80_b[0x25]);

                    if (path_ok != 0) {
                        limit_turns = 1;
                    }
                }
                turn_index = 0;
            }
        }
    } else {
        turn_index = find_nearest_floor_item_in_room(position_arg, 0x12, &target_x, &target_y);
        if (((S_801715F4_2 *)position_arg)->unk_26.s >= 0) {
            s32 monster_index = ((S_801715F4_2 *)position_arg)->unk_26.s;
            u8 *monster_table = D_800E2970;

            if (((S_801715F4_6 *)(monster_table + monster_index * 0x14))->unk_0C & 2) {
                goto call_obstacle;
            }
        }

        if (!(((S_801715F4_1 *)actor_arg)->unk_46 & 0x8000)) {
            angle = place_actor_at_directional_neighbor(actor_arg, ((S_801715F4_2 *)position_arg)->unk_24.at00.v,
                                  ((S_801715F4_2 *)position_arg)->unk_24.at01.v, ((S_801715F4_1 *)actor_arg)->unk_2A.s);
            if ((angle != 0) && (((S_801715F4_3 *)angle)->unk_1C & 0x2000) &&
                (get_actor_height_difference(angle, actor_arg) < 0x81) &&
                ((s16)check_diagonal_side_height(
                     ((s32)(((S_801715F4_1 *)actor_arg)->unk_2A.u << 16) >> 25) & 0xFFFF,
                     ((S_801715F4_2 *)position_arg)->unk_24.at00.v, ((S_801715F4_2 *)position_arg)->unk_24.at01.v,
                     (s16)(((S_801715F4_1 *)actor_arg)->unk_88 - 0x20)) != 0)) {
                ((S_801715F4_1 *)actor_arg)->unk_71.u &= 0x7F;
                return;
            }

            if (((S_801715F4_1 *)actor_arg)->unk_1C & 0x20000) {
                follow_context = (u8 *)move_state + 0x98;
                ((S_801715F4_1 *)actor_arg)->unk_2A.u = get_rounded_facing_and_rounding_flag(
                    ((S_801715F4_2 *)position_arg)->unk_24.at00.v, ((S_801715F4_2 *)position_arg)->unk_24.at01.v,
                    D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y,
                    follow_context);
                if ((s16)compare_monster_neighbor_values(((S_801715F4_2 *)position_arg)->unk_24.at00.v,
                                       ((S_801715F4_2 *)position_arg)->unk_24.at01.v,
                                       D_80082E80.tile_position.parts.tile_x,
                                       D_80082E80.tile_position.parts.tile_y) != 0) {
                    if (get_actor_height_difference(D_800814A8, actor_arg) < 0x81) {
                        if ((s16)check_diagonal_side_height(
                                ((s32)(((S_801715F4_1 *)actor_arg)->unk_2A.u << 16) >> 25) & 0xFFFF,
                                ((S_801715F4_2 *)position_arg)->unk_24.at00.v, ((S_801715F4_2 *)position_arg)->unk_24.at01.v,
                                (s16)(((S_801715F4_1 *)actor_arg)->unk_88 - 0x20)) != 0) {
                            ((S_801715F4_1 *)actor_arg)->unk_71.u &= 0x7F;
                            return;
                        }
                        if (turn_index != 0) {
                            dx = ((S_801715F4_2 *)position_arg)->unk_24.at00.v;
                            dx -= (target_x_wide = (u16)target_x);
                            dx = abs(dx);
                            if (dx >= 2 || (dy = abs(((S_801715F4_2 *)position_arg)->unk_24.at01.v - (u16)target_y)) >= 2) {
                                ((S_801715F4_1 *)actor_arg)->unk_2A.u = get_rounded_facing_and_rounding_flag(
                                    ((S_801715F4_2 *)position_arg)->unk_24.at00.v, ((S_801715F4_2 *)position_arg)->unk_24.at01.v,
                                        (s16)target_x_wide, target_y,
                                    follow_context);
                            } else {
                                ((S_801715F4_1 *)actor_arg)->unk_2A.u = (generate_random_value() & 7) << 9;
                            }
                        }
                    }
                }
            } else {
                if (turn_index == 0) {
                    rebuild_monster_reachable_tiles(position_arg, ((S_801715F4_8 *)move_state)->unk_9C.s, actor_arg,
                  (u8 *)move_state + 0x98);
                } else {
                    dx = ((S_801715F4_2 *)position_arg)->unk_24.at00.v;
                    dx -= (target_x_wide = (u16)target_x);
                    dx = abs(dx);
                    if (dx >= 2 || (dy = abs(((S_801715F4_2 *)position_arg)->unk_24.at01.v - (u16)target_y)) >= 2) {
                        ((S_801715F4_1 *)actor_arg)->unk_2A.u = get_rounded_facing_and_rounding_flag(
                            ((S_801715F4_2 *)position_arg)->unk_24.at00.v, ((S_801715F4_2 *)position_arg)->unk_24.at01.v,
                                (s16)target_x_wide, target_y,
                            (u8 *)move_state + 0x98);
                    } else {
                        ((S_801715F4_1 *)actor_arg)->unk_2A.u = (generate_random_value() & 7) << 9;
                    }
                }
            }
        }
    }
    goto loop_setup;
call_obstacle:
    rebuild_monster_reachable_tiles(position_arg, ((S_801715F4_8 *)move_state)->unk_9C.s, actor_arg,
                  (u8 *)move_state + 0x98);

loop_setup:
    turn_index = 0;
    turn_table = (s16 *)&D_8006CD00;

    for (; turn_index < 8; turn_index++) {
        {

            angle = (void *)(((S_801715F4_1 *)actor_arg)->unk_2A.s);
            if (((S_801715F4_8 *)move_state)->unk_98 & 2) {
                next_angle = ((s32)angle) - turn_table[turn_index];
            } else {
                next_angle = ((s32)angle) + turn_table[turn_index];
            }
        }

        if (check_movement_clearance_and_height((s16)next_angle, position_arg, actor_arg, 0x20) > 0) {
            if (turn_index >= 3) {
                s16 turn_limit;

                turn_limit = limit_turns;
                if (turn_limit != 0) {
                    ((S_801715F4_1 *)actor_arg)->unk_71.u &= 0x7F;
                    return;
                }
            }

            ((S_801715F4_1 *)actor_arg)->unk_2A.u = next_angle;
            ((S_801715F4_10 *)((u8 *)actor_arg + (((S_801715F4_1 *)actor_arg)->unk_71.u & 0x7F)))->unk_74 =
                ((S_801715F4_2 *)position_arg)->unk_24.at00.v;
            ((S_801715F4_10 *)((u8 *)actor_arg + (((S_801715F4_1 *)actor_arg)->unk_71.u & 0x7F)))->unk_7C =
                ((S_801715F4_2 *)position_arg)->unk_24.at01.v;
            ((S_801715F4_1 *)actor_arg)->unk_71.u++;

            update_map_cell_flags_with_item_limit(((S_801715F4_2 *)position_arg)->unk_24.at00.v, ((S_801715F4_2 *)position_arg)->unk_24.at01.v,
                          (((S_801715F4_1 *)actor_arg)->unk_1C & 0x2000) ? 0x300 : 0x3000);

            table_offset = (((S_801715F4_1 *)actor_arg)->unk_2A.u >> 8) & 0xE;
            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                x_step += table_offset;
                ((S_801715F4_2 *)position_arg)->unk_24.at00.v += *x_step;
            }
            ((S_801715F4_2 *)position_arg)->unk_24.at01.v +=
                *(u8 *)((u8 *)((s8 *)dir_step_y) + table_offset);

            cycle_map_cell_flags(((S_801715F4_2 *)position_arg)->unk_24.at00.v, ((S_801715F4_2 *)position_arg)->unk_24.at01.v,
                          (((S_801715F4_1 *)actor_arg)->unk_1C & 0x2000) ? 0x300 : 0x3000);
            break;
        }

        if (turn_index == 0) {
            if (*(u16 *)(&D_80082E80.tile_position.parts.tile_x) != ((S_801715F4_2 *)position_arg)->unk_24.at00u.v) {
                if ((s16)check_entity_relation(
                        actor_arg,
                        (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
        }

    }

    if (turn_index >= 8) {
        ((S_801715F4_1 *)actor_arg)->unk_71.u &= 0x7F;
        ((S_801715F4_1 *)actor_arg)->unk_46 &= 0x7FFF;
        update_actor_status_and_food(actor_arg);
        return;
    }

    ((S_801715F4_1 *)actor_arg)->unk_46 &= 0x7FFF;
    ((S_801715F4_8 *)move_state)->unk_9C.u = ((S_801715F4_2 *)position_arg)->unk_26.u;
    ((S_801715F4_1 *)actor_arg)->unk_6D.u--;
    {
        DungeonGlobalStatus *counter_state = &g_dungeon_status;

        counter_state->activity_counts.parts.pending_movement_count++;
    }
    if (((S_801715F4_1 *)actor_arg)->unk_6D.s == 0) {
        ((S_801715F4_1 *)actor_arg)->unk_71.u &= 0x7F;
        return;
    }

    turn_index = sample_terrain_surface_height((((S_801715F4_2 *)position_arg)->unk_24.at00.v << 6) | 0x20,
                               (((S_801715F4_2 *)position_arg)->unk_24.at01.v << 6) | 0x20,
                               (s16)(((S_801715F4_1 *)actor_arg)->unk_88 - 0x20));
    if (turn_index < 0x200) {
        ((S_801715F4_1 *)actor_arg)->unk_88 = turn_index;
    }
    return;

    return;
}
