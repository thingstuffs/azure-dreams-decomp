#include "shared/object_node.h"
/* Ghosh tile stepping and staged actor movement. */
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"
#include "shared/actor_status.h"
#include "dungeon/level.h"

typedef struct S_8016FCE4_0 {
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
} S_8016FCE4_0;   /* arg3 in advance_boss_actor_movement_state */

typedef struct S_8016FCE4_1 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    u8 unk_26;
} S_8016FCE4_1;   /* arg2 in advance_boss_actor_movement_state */

typedef struct S_8016FCE4_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8016FCE4_4;   /* heading_base in advance_boss_actor_movement_state */

   /* (arg3 + ((u8) ((S_8016FCE4_0 *)arg3)->unk_71.s & 0x7F)) in advance_boss_actor_movement_state */

s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
s32 check_movement_clearance_and_height(s32, void *, void *, s32);
s16 test_neighbor_position_relation(s32 src_x, s32 src_y, s32 dst_x, s32 dst_y);
void *find_adjacent_actor(void *entity, u16 x, u16 y);
s32 probe_directional_neighbor(void *, s32, s32, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
s16 get_rounded_facing_and_rounding_flag(s32, s32, s32, s32, void *); /* Unprototyped: retail call narrows its arguments to this declaration; no shared prototype keeps it */
s32 select_actor_route_target(u8 *actor_held, s32 kind, u8 *work_p, u16 *out);
void update_actor_proximity_flag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
s32 generate_random_value(void);
void update_actor_status_and_mp(ActorRecord *entity);
extern s16 actor_turn_angle_offsets[];
extern TileObject D_80082E80_b __asm__("D_80082E80");

/* Adds the indexed byte from the direction table to the tile coordinate and returns the low byte. */
static __inline__ u8 advance_tile(u8 tile, const u8 * table, u16 index)
{
    return tile + *(const u8 *)((u32)index + (unsigned long)table);
}

/* Choose a movement heading, advance the actor_in, and update its movement state. */
void advance_boss_actor_movement_state(void *move_state, void *unused, void *position_in, void *actor_in) {
    ObjectNodeHeader *previous_node;
    void *previous_body;
    ActorRecord *previous_actor;
    s32 tile_mask;
    register s16 *turn_offsets;
    s32 y_address;
    s32 target_y;
    s32 target_x;
    s16 trial_heading;
    s16 target_heading;
    s16 step_coord;
    s32 tile_y;
    void * heading_state;
    s32 move_result;
    s32 move_flags;
    s32 heading;
    s32 turn_index;
    s32 limit_turns;
    u8 *x_offsets;
    ActorRecord *target;
    MovingTile *target_position;

    limit_turns = 0;
    if ((g_dungeon_status.flags & 0x4000) || (((S_8016FCE4_0 *)actor_in)->unk_71.s >= 0)) {
        update_actor_status_and_mp(actor_in);
        return;
    }
    if (g_dungeon_status.flags & 0x2000) {
        update_actor_proximity_flag(position_in, actor_in, 3, 6, move_state + 0x9C);
        move_flags = ((S_8016FCE4_0 *)actor_in)->unk_1C;
        if (move_flags & 0x410) {
            if (move_flags & 0x400) {
                target = find_adjacent_actor(actor_in, ((S_8016FCE4_1 *)position_in)->unk_24.at00.v,
                    ((S_8016FCE4_1 *)position_in)->unk_24.at01.v);
                if (target != 0) {
                    target_position = ((SpriteLinkPrefixView *)target)[-1].sprite;
                    ((S_8016FCE4_0 *)actor_in)->unk_2A.u = get_rounded_facing_and_rounding_flag(((S_8016FCE4_1 *)position_in)->unk_24.at00.v,
                        ((S_8016FCE4_1 *)position_in)->unk_24.at01.v, target_position->tile_x, target_position->tile_y,
                        move_state + 0x98);
                    ((S_8016FCE4_0 *)actor_in)->unk_71.u = ((S_8016FCE4_0 *)actor_in)->unk_71.u & 0x7F;
                    return;
                }
                move_result = ((S_8016FCE4_0 *)actor_in)->unk_14;
                if (!(move_result & 0x80000000)) {
                    move_result |= 0x80000000;
                    ((S_8016FCE4_0 *)actor_in)->unk_14 = (s32)move_result;
                    ((S_8016FCE4_0 *)actor_in)->unk_2A.u += (generate_random_value() & 7) << 9;
                }
            } else {
                move_result = probe_directional_neighbor(actor_in, ((S_8016FCE4_1 *)position_in)->unk_24.at00.v,
                    ((S_8016FCE4_1 *)position_in)->unk_24.at01.v, (s16) ((S_8016FCE4_0 *)actor_in)->unk_2A.u);
                if (move_result != 0) {
                    ((S_8016FCE4_0 *)actor_in)->unk_71.s = (s8) ((u8) ((S_8016FCE4_0 *)actor_in)->unk_71.s & 0x7F);
                    return;
                }
            }
        } else {
            if (!(((S_8016FCE4_0 *)actor_in)->unk_46 & 0x8000)) {
                if (move_flags & 0x20000) {
                    u8 **heading_ref = &primary_actor_record;
                    TileObject *position_base = &reference_tile_object;
                    u8 *heading_base;
                    u8 *x_table_base;
                    s32 dir_index;

                    x_table_base = ((u8 *)dir_step_x);
                    heading_base = *heading_ref;
                    dir_index = ((((S_8016FCE4_0 *)actor_in)->unk_45 + ((s32) (((S_8016FCE4_4 *)heading_base)->unk_2A
                        << 0x10) >> 0x19)) & 7) * 2;
                    target_x = position_base->tile_position.parts.tile_x + *(u16 *)(x_table_base + dir_index);
                    target_y = reference_tile_object.tile_position.parts.tile_y + *(u16 *)(((u8 *)dir_step_y) + dir_index);
                    if ((((S_8016FCE4_1 *)position_in)->unk_24.at00.v != (u16)target_x)
                        || (((S_8016FCE4_1 *)position_in)->unk_24.at01.v != (u16)target_y)) {
                        heading_state = move_state + 0x98;
                        target_heading = get_rounded_facing_and_rounding_flag(((S_8016FCE4_1 *)position_in)->unk_24.at00.v,
                            ((S_8016FCE4_1 *)position_in)->unk_24.at01.v, (s16) target_x, (s16) target_y,
                            heading_state);
                        ((S_8016FCE4_0 *)actor_in)->unk_2A.u = (u16) target_heading;
                        if ((check_movement_clearance_and_height(target_heading, position_in, actor_in, 0x20) << 0x10) <= 0) {
                            ((S_8016FCE4_0 *)actor_in)->unk_2A.u =
                                get_rounded_facing_and_rounding_flag(((S_8016FCE4_1 *)position_in)->unk_24.at00.v,
                                ((S_8016FCE4_1 *)position_in)->unk_24.at01.v, D_80082E80_b.tile_position.parts.tile_x, D_80082E80_b.tile_position.parts.tile_y,
                                heading_state);
                        }
                        move_result = test_neighbor_position_relation(((S_8016FCE4_1 *)position_in)->unk_24.at00.v,
                            ((S_8016FCE4_1 *)position_in)->unk_24.at01.v, D_80082E80_b.tile_position.parts.tile_x, D_80082E80_b.tile_position.parts.tile_y);
                        if ((move_result << 0x10) != 0) {
                            limit_turns = 1;
                        }
                    } else {
                        ((S_8016FCE4_0 *)actor_in)->unk_71.s = (s8) ((u8) ((S_8016FCE4_0 *)actor_in)->unk_71.s & 0x7F);
                        return;
                    }
                } else {
                    select_actor_route_target(position_in, ((Rec_func_800A9E70_arg0 *)move_state)->unk_9C.as_s8, actor_in,
                        move_state + 0x98);
                }
            }
        }
        turn_index = 0;
        x_offsets = ((u8 *)dir_step_x);
        turn_offsets = actor_turn_angle_offsets;
        do {
            heading = ((S_8016FCE4_0 *)actor_in)->unk_2A.s;
            if (((Rec_func_800A9E70_arg0 *)move_state)->unk_98 & 2) {
                move_result = *turn_offsets;
                trial_heading = heading - move_result;
            } else {
                move_result = *turn_offsets;
                trial_heading = heading + move_result;
            }
            if ((check_movement_clearance_and_height((s16) trial_heading, position_in, actor_in, 0x20) << 0x10) > 0) {
                if (turn_index >= 3) {
                    move_result = limit_turns;
                    if (move_result != 0) {
                        ((S_8016FCE4_0 *)actor_in)->unk_71.s = (s8) ((u8) ((S_8016FCE4_0 *)actor_in)->unk_71.s & 0x7F);
                        return;
                    }
                }
                {
                    ((S_8016FCE4_0 *)actor_in)->unk_2A.u = (u16) trial_heading;
                    ((ActorStatusBytesView *)((actor_in + ((u8) ((S_8016FCE4_0 *)actor_in)->unk_71.s & 0x7F))))->path_x =
                        (u8) ((S_8016FCE4_1 *)position_in)->unk_24.at00.v;
                    ((ActorStatusBytesView *)((actor_in + ((u8) ((S_8016FCE4_0 *)actor_in)->unk_71.s & 0x7F))))->path_y =
                        (u8) ((S_8016FCE4_1 *)position_in)->unk_24.at01.v;
                    ((S_8016FCE4_0 *)actor_in)->unk_71.s = (s8) ((u8) ((S_8016FCE4_0 *)actor_in)->unk_71.s + 1);
                    update_map_cell_flags_with_item_limit(((S_8016FCE4_1 *)position_in)->unk_24.at00.v,
                        ((S_8016FCE4_1 *)position_in)->unk_24.at01.v,
                                  (((S_8016FCE4_0 *)actor_in)->unk_1C & 0x2000) ? 0x300 : 0x3000);
                    step_coord = ((u16) ((S_8016FCE4_0 *)actor_in)->unk_2A.u >> 8) & 0xE;
                    ((S_8016FCE4_1 *)position_in)->unk_24.at00.v =
                        advance_tile(((S_8016FCE4_1 *)position_in)->unk_24.at00.v, x_offsets, step_coord);
                    y_address = step_coord + (s32)((u8 *)dir_step_y);
                    ((S_8016FCE4_1 *)position_in)->unk_24.at01.v =
                        advance_tile(((S_8016FCE4_1 *)position_in)->unk_24.at01.v, (u8 *)y_address, 0);
                    step_coord = ((S_8016FCE4_1 *)position_in)->unk_24.at00.v;
                    tile_y = ((S_8016FCE4_1 *)position_in)->unk_24.at01.v;
                    if (((S_8016FCE4_0 *)actor_in)->unk_1C & 0x2000) {
                        tile_mask = 0x300;
                    } else {
                        tile_mask = 0x3000;
                    }
                    cycle_map_cell_flags(step_coord, tile_y, tile_mask);
                    break;
                }
            }
            if ((turn_index != 0) || (reference_tile_object.tile_position.word == ((S_8016FCE4_1 *)position_in)->unk_24.at00u.v)
                || ((check_entity_relation(actor_in, (previous_node = primary_actor_record->previous_actor_header,
                    previous_body = previous_node + 1, previous_actor = previous_body)) << 0x10) == 0)) {
                turn_index += 1;
                turn_offsets += 1;
            } else {
                return;
            }
        } while (turn_index < 8);
        move_result = turn_index < 8;
        if (move_result == 0) {
            ((S_8016FCE4_0 *)actor_in)->unk_71.s = (s8) ((u8) ((S_8016FCE4_0 *)actor_in)->unk_71.s & 0x7F);
            ((S_8016FCE4_0 *)actor_in)->unk_46 = (u16) (((S_8016FCE4_0 *)actor_in)->unk_46 & 0x7FFF);
            update_actor_status_and_mp(actor_in);
            return;
        }
        ((S_8016FCE4_0 *)actor_in)->unk_46 = (u16) (((S_8016FCE4_0 *)actor_in)->unk_46 & 0x7FFF);
        ((Rec_func_800A9E70_arg0 *)move_state)->unk_9C.as_s8 = (s8) ((S_8016FCE4_1 *)position_in)->unk_26;
        ((S_8016FCE4_0 *)actor_in)->unk_6D.u = (u8) (((S_8016FCE4_0 *)actor_in)->unk_6D.u - 1);
        g_dungeon_status.activity_counts.parts.pending_movement_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_movement_count) + 1);
        if (((S_8016FCE4_0 *)actor_in)->unk_6D.s == 0) {
            ((S_8016FCE4_0 *)actor_in)->unk_71.s = (s8) ((u8) ((S_8016FCE4_0 *)actor_in)->unk_71.s & 0x7F);
            return;
        }
        turn_index = (s16) sample_terrain_surface_height((((S_8016FCE4_1 *)position_in)->unk_24.at00.v << 6) | 0x20,
            (((S_8016FCE4_1 *)position_in)->unk_24.at01.v << 6) | 0x20,
            (s16) (((S_8016FCE4_0 *)actor_in)->unk_88 - 0x20));
        if (turn_index < 0x200) {
            ((S_8016FCE4_0 *)actor_in)->unk_88 = (u16) turn_index;
        }
    }
}
