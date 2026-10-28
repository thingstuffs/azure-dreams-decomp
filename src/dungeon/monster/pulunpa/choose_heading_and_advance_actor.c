#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_func_800A9E70_arg0.h"

typedef struct S_8017405C_0 {
    u8 pad_00[0x14];
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
} S_8017405C_0;   /* d in choose_heading_and_advance_actor */

typedef struct S_8017405C_1 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    union { s8 s; u8 u; } unk_26;   /* accessed as both */
} S_8017405C_1;   /* c in choose_heading_and_advance_actor */

typedef struct S_8017405C_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017405C_2_pre;   /* the 0x14 bytes before e in choose_heading_and_advance_actor, addressed as e[-1] */

typedef struct S_8017405C_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8017405C_2;   /* e in choose_heading_and_advance_actor */

typedef struct S_8017405C_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017405C_3;   /* e2 in choose_heading_and_advance_actor */



typedef struct S_8017405C_7_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017405C_7_pre;   /* the 0x14 bytes before pa in choose_heading_and_advance_actor, addressed as pa[-1] */

typedef struct S_8017405C_8_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017405C_8_pre;   /* the 0x14 bytes before pb in choose_heading_and_advance_actor, addressed as pb[-1] */

typedef struct S_8017405C_9 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017405C_9;   /* p2 in choose_heading_and_advance_actor */

typedef struct S_8017405C_10 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017405C_10;   /* p1 in choose_heading_and_advance_actor */

typedef struct S_8017405C_11 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8017405C_11;   /* (u8 *)d + (((S_8017405C_0 *)d)->unk_71.u & 0x7F) in choose_heading_and_advance_actor */


typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonModeRecord;

extern void update_actor_status_and_mp(ActorRecord *entity);
extern void update_actor_proximity_flag(void *, void *, s32, s32, void *);
extern void * find_adjacent_actor(void *, s32, s32);
extern s32 get_rounded_facing_and_rounding_flag(s16, s16, s16, s16, void *);
extern s32 generate_random_value(void);
extern void *probe_directional_neighbor(void *, s32, s32, s32);
extern s16 check_movement_clearance_and_height(s16, void *, void *, s32);
extern void select_actor_route_target(void *, s32, void *, void *);
extern s16 get_actor_height_difference(ActorRecord *left_record, ActorRecord *right_record);
extern s16 check_diagonal_side_height(s32, s32, s32, s32);
extern s32 calculate_planar_heading(s16, s16, s16, s16);
extern s16 get_tile_chebyshev_distance(void *, void *);
extern s16 test_neighbor_position_relation(s32, s32, s32, s32);
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern void cycle_map_cell_flags(s32, s32, s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern s16 sample_terrain_surface_height(s32, s32, s16);
extern s16 func_80174BCC(void *, s32, void *, void *);

extern u8 reference_tile_object[];
extern u16 reference_tile_position_alias;
extern s16 actor_turn_angle_offsets[];
extern DungeonModeRecord dungeon_rooms[];

/*
 * Steers Pulunpa toward the nearer companion or a player-relative tile, tries clear headings, and
 * updates its path and occupancy.
 */
void choose_heading_and_advance_actor(void *context, s32 action, S_8017405C_1 *actor, void *movement)
{
    s16 move_index;
    s16 stop_fallback = 0;
    s16 heading;
    u16 target_y;
    u16 state_flags;
    s32 flags;
    s32 y_offset;
    void *target;

    state_flags = g_dungeon_status.flags;

    if ((state_flags & 0x4000) || ((S_8017405C_0 *)movement)->unk_71.s >= 0) {
        if (((S_8017405C_0 *)movement)->unk_71.s >= 0 || func_80174BCC(context, action, actor, movement) == 0) {
            update_actor_status_and_mp(movement);
        } else {
            ((S_8017405C_0 *)movement)->unk_46 = 0xC008;
        }
        return;
    }
    if (!(state_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(actor, movement, 3, 6, (u8 *)context + 0x9C);
    flags = ((S_8017405C_0 *)movement)->unk_1C;
    if (flags & 0x410) {
        if (flags & 0x400) {
            target = find_adjacent_actor(movement, actor->unk_24.at00.v, actor->unk_24.at01.v);
            if (target != 0) {
                S_8017405C_3 *target_pos = ((S_8017405C_2_pre *)target)[-1].unk_00;
                ((S_8017405C_0 *)movement)->unk_2A.u = get_rounded_facing_and_rounding_flag(actor->unk_24.at00.v, actor->unk_24.at01.v,
                                                    target_pos->unk_24, target_pos->unk_25,
                                                    (u8 *)context + 0x98);
                ((S_8017405C_0 *)movement)->unk_71.u &= 0x7F;
                return;
            }
            {
                s32 turn_flags = ((S_8017405C_0 *)movement)->unk_14;
                if (!(turn_flags & 0x80000000)) {
                    turn_flags |= 0x80000000;
                    ((S_8017405C_0 *)movement)->unk_14 = turn_flags;
                    ((S_8017405C_0 *)movement)->unk_2A.u += (generate_random_value() & 7) << 9;
                }
            }
        } else if (probe_directional_neighbor(movement, actor->unk_24.at00.v, actor->unk_24.at01.v,
            ((S_8017405C_0 *)movement)->unk_2A.s) != 0) {
            ((S_8017405C_0 *)movement)->unk_71.u &= 0x7F;
            return;
        }
    } else if (flags & 0x2000) {
        if (!(((S_8017405C_0 *)movement)->unk_46 & 0x8000)) {
            if (!(flags & 0x20000)) {
                select_actor_route_target(actor, ((Rec_func_800A9E70_arg0 *)context)->unk_9C.as_s8, movement, (u8 *)context + 0x98);
            } else {
                {
                    s32 dir;
                    dir = (((S_8017405C_0 *)movement)->unk_45 + (primary_actor_record->facing >> 9)) & 7;
                    heading = reference_tile_object[0x24] + dir_step_x[dir];
                    target_y = reference_tile_object[0x25] + dir_step_y[dir];
                    if (actor->unk_24.at00.v == (u16)heading && actor->unk_24.at01.v == (u16)target_y) {
                        ((S_8017405C_0 *)movement)->unk_71.u &= 0x7F;
                        return;
                    }
                }
                {
                    void *path_state = (u8 *)context + 0x98;
                    u16 target_heading = get_rounded_facing_and_rounding_flag(actor->unk_24.at00.v, actor->unk_24.at01.v, (s16)heading,
                        (s16)target_y, path_state);
                    ((S_8017405C_0 *)movement)->unk_2A.u = target_heading;
                    if (check_movement_clearance_and_height((s16)target_heading, actor, movement, 0x20) <= 0) {
                        u8 *leader_pos = (u8 *)&reference_tile_position_alias - 0x24;
                        ((S_8017405C_0 *)movement)->unk_2A.u = get_rounded_facing_and_rounding_flag(actor->unk_24.at00.v, actor->unk_24.at01.v,
                                                            leader_pos[0x24], leader_pos[0x25], path_state);
                    }
                }
            }
        }
    } else {
        s32 mode = actor->unk_26.s;
        if (mode >= 0 && (dungeon_rooms[mode].flags & 2)) {
            select_actor_route_target(actor, ((Rec_func_800A9E70_arg0 *)context)->unk_9C.as_s8, movement, (u8 *)context + 0x98);
        } else {
            if (!(((S_8017405C_0 *)movement)->unk_46 & 0x8000)) {
                target = probe_directional_neighbor(movement, actor->unk_24.at00.v, actor->unk_24.at01.v,
                    ((S_8017405C_0 *)movement)->unk_2A.s);
                if (target != 0 && (((S_8017405C_2 *)target)->unk_1C & 0x2000)
                    && get_actor_height_difference(target, movement) < 0x81) {
                    if (check_diagonal_side_height((((s16)((S_8017405C_0 *)movement)->unk_2A.u >> 9) & 0xFFFF),
                                      actor->unk_24.at00.v, actor->unk_24.at01.v,
                                      (s16)(((S_8017405C_0 *)movement)->unk_88 - 0x20)) != 0) {
                        ((S_8017405C_0 *)movement)->unk_71.u &= 0x7F;
                        return;
                    }
                }
            }
            if (((S_8017405C_0 *)movement)->unk_1C & 0x20000) {
                S_8017405C_7_pre *first_master;
                S_8017405C_8_pre *second_master;
                ((Rec_func_800A9E70_arg0 *)context)->unk_A6 = 0;
                first_master = primary_actor_record->unk_AC.address;
                if (first_master == 0 || (second_master = primary_actor_record->unk_B0.address) == 0) {
                    {
                        u8 *leader_pos = reference_tile_object;
                        s32 angle_delta;
                        s32 relative_angle;
                        angle_delta = calculate_planar_heading(leader_pos[0x24], leader_pos[0x25],
                                              actor->unk_24.at00.v, actor->unk_24.at01.v);
                        relative_angle = (((u16)primary_actor_record->facing) + angle_delta) & 0xFFF;
                        if (relative_angle > 0x400 && relative_angle < 0xC00) {
                            ((S_8017405C_0 *)movement)->unk_45 = 3;
                        } else if (relative_angle == 0x400 || relative_angle == 0xC00) {
                            ((S_8017405C_0 *)movement)->unk_45 = 1;
                        } else {
                            ((S_8017405C_0 *)movement)->unk_45 = 2;
                        }
                    }
                    {
                        s32 dir;
                        dir = (((S_8017405C_0 *)movement)->unk_45 + (primary_actor_record->facing >> 9)) & 7;
                        heading = reference_tile_object[0x24] + dir_step_x[dir];
                        target_y = reference_tile_object[0x25] + dir_step_y[dir];
                        ((S_8017405C_0 *)movement)->unk_2A.u = get_rounded_facing_and_rounding_flag(actor->unk_24.at00.v, actor->unk_24.at01.v,
                                                            heading, target_y, (u8 *)context + 0x98);
                        if (actor->unk_24.at00.v == (u16)heading && actor->unk_24.at01.v == (u16)target_y) {
                            ((S_8017405C_0 *)movement)->unk_71.u &= 0x7F;
                            return;
                        }
                    }
                } else {
                    S_8017405C_9 *first_pos = first_master[-1].unk_00;
                    S_8017405C_10 *second_pos = second_master[-1].unk_00;
                    s16 first_distance = get_tile_chebyshev_distance(first_pos, actor);
                    if (first_distance < get_tile_chebyshev_distance(second_pos, actor)) {
                        ((S_8017405C_0 *)movement)->unk_2A.u = get_rounded_facing_and_rounding_flag(actor->unk_24.at00.v, actor->unk_24.at01.v,
                                                            first_pos->unk_24,
                                                                first_pos->unk_25,
                                                            (u8 *)context + 0x98);
                        if (test_neighbor_position_relation(actor->unk_24.at00.v, actor->unk_24.at01.v,
                                          first_pos->unk_24, first_pos->unk_25)
                                              != 0) {
                            ((S_8017405C_0 *)movement)->unk_71.u &= 0x7F;
                            return;
                        }
                    } else {
                        ((S_8017405C_0 *)movement)->unk_2A.u = get_rounded_facing_and_rounding_flag(actor->unk_24.at00.v, actor->unk_24.at01.v,
                                                            second_pos->unk_24,
                                                                second_pos->unk_25,
                                                            (u8 *)context + 0x98);
                        if (test_neighbor_position_relation(actor->unk_24.at00.v, actor->unk_24.at01.v,
                                          first_pos->unk_24, first_pos->unk_25)
                                              != 0) {
                            ((S_8017405C_0 *)movement)->unk_71.u &= 0x7F;
                            return;
                        }
                    }
                }
            } else if (((Rec_func_800A9E70_arg0 *)context)->unk_A6 == 0) {
                ((Rec_func_800A9E70_arg0 *)context)->unk_A6 = 1;
                ((Rec_func_800A9E70_arg0 *)context)->unk_A4 = ((generate_random_value() & 3) << 10) + 0x200;
            }
        }
    }
    {
        for (move_index = 0; move_index < 8; move_index++) {
            if (((Rec_func_800A9E70_arg0 *)context)->unk_A6 != 0) {
                s32 base_heading = ((Rec_func_800A9E70_arg0 *)context)->unk_A4;
                if (((Rec_func_800A9E70_arg0 *)context)->unk_98 & 2) {
                    y_offset = actor_turn_angle_offsets[move_index];
                    heading = base_heading - y_offset;
                } else {
                    y_offset = actor_turn_angle_offsets[move_index];
                    heading = base_heading + y_offset;
                }
            } else {
                target = (void *)((u8 *)(((S_8017405C_0 *)movement)->unk_2A.s));
                if (((Rec_func_800A9E70_arg0 *)context)->unk_98 & 2) {
                    y_offset = actor_turn_angle_offsets[move_index];
                    heading = (s32)(u8 *)target - y_offset;
                } else {
                    y_offset = actor_turn_angle_offsets[move_index];
                    heading = (s32)(u8 *)target + y_offset;
                }
            }
            if (check_movement_clearance_and_height(heading, actor, movement, 0x20) > 0) {
                if (move_index >= 3) {
                    if ((stop_fallback != 0) || (((Rec_func_800A9E70_arg0 *)context)->unk_A6 != 0)) {
                        ((S_8017405C_0 *)movement)->unk_71.u &= 0x7F;
                        return;
                    }
                }
                ((S_8017405C_0 *)movement)->unk_2A.u = heading;
                ((S_8017405C_11 *)((u8 *)movement + (((S_8017405C_0 *)movement)->unk_71.u & 0x7F)))->unk_74 =
                    actor->unk_24.at00.v;
                ((S_8017405C_11 *)((u8 *)movement + (((S_8017405C_0 *)movement)->unk_71.u & 0x7F)))->unk_7C =
                    actor->unk_24.at01.v;
                ((S_8017405C_0 *)movement)->unk_71.u = ((S_8017405C_0 *)movement)->unk_71.u + 1;
                update_map_cell_flags_with_item_limit(actor->unk_24.at00.v, actor->unk_24.at01.v,
                              (((S_8017405C_0 *)movement)->unk_1C & 0x2000) ? 0x300 : 0x3000);
                {
                    s32 step_offset;
                    u8 *x_steps;
                    step_offset = (((S_8017405C_0 *)movement)->unk_2A.u >> 8) & 0xE;
                    x_steps = (u8 *)dir_step_x;
                    x_steps += step_offset;
                    actor->unk_24.at00.v = actor->unk_24.at00.v + *x_steps;
                    {
                        u8 *y_steps = (u8 *)dir_step_y;
                        actor->unk_24.at01.v = actor->unk_24.at01.v +
                                             *(u8 *)((unsigned long)step_offset + (unsigned long)y_steps);
                    }
                }
                cycle_map_cell_flags(actor->unk_24.at00.v, actor->unk_24.at01.v,
                              (((S_8017405C_0 *)movement)->unk_1C & 0x2000) ? 0x300 : 0x3000);
                break;
            }
            if (move_index == 0 && reference_tile_position_alias != actor->unk_24.at00u.v) {
                if (check_entity_relation(movement, primary_actor_record->previous_actor_header + 0x20) != 0) {
                    return;
                }
            }
        }
    }

    if (move_index >= 8) {
        ((S_8017405C_0 *)movement)->unk_71.u &= 0x7F;
        ((S_8017405C_0 *)movement)->unk_46 &= 0x7FFF;
        update_actor_status_and_mp(movement);
        return;
    }
    {
        ((S_8017405C_0 *)movement)->unk_46 &= 0x7FFF;
        ((Rec_func_800A9E70_arg0 *)context)->unk_9C.as_s8 = actor->unk_26.u;
        ((S_8017405C_0 *)movement)->unk_6D.u = ((S_8017405C_0 *)movement)->unk_6D.u - 1;
        g_dungeon_status.activity_counts.parts.pending_movement_count = ((u16)g_dungeon_status.activity_counts.parts.pending_movement_count) + 1;
    }
    if (((S_8017405C_0 *)movement)->unk_6D.s == 0) {
        ((S_8017405C_0 *)movement)->unk_71.u &= 0x7F;
        return;
    }
    move_index = sample_terrain_surface_height((actor->unk_24.at00.v << 6) | 0x20,
                        (actor->unk_24.at01.v << 6) | 0x20,
                        (s16)(((S_8017405C_0 *)movement)->unk_88 - 0x20));
    if (move_index < 0x200) {
        ((S_8017405C_0 *)movement)->unk_88 = move_index;
    }
    return;
}
