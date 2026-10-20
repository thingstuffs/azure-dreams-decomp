#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"
#include "shared/actor_status.h"

typedef struct S_8016BF74_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_8016BF74_0;   /* state in advance_actor_path */

typedef struct S_8016BF74_1 {
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
} S_8016BF74_1;   /* arg3 in advance_actor_path */

typedef struct S_8016BF74_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    s8 unk_26;
} S_8016BF74_2;   /* arg2 in advance_actor_path */





typedef struct S_8016BF74_5 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    s8 unk_9C;
    u8 pad_9D[0x15];
    u8 unk_B2;
} S_8016BF74_5;   /* arg0 in advance_actor_path */


typedef struct S_8016BF74_7 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8016BF74_7;

typedef struct S_8016BF74_8 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8016BF74_8;   /* state2 in advance_actor_path */

   /* (arg3 + ((u8) ((S_8016BF74_1 *)arg3)->unk_71.s & 0x7F)) in advance_actor_path */


struct EntityRec; s32 check_entity_relation(struct EntityRec *, struct EntityRec *);                     /* extern */
void cycle_map_cell_flags(s16, s16, u16);             /* extern */
#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"             /* extern */
s32 check_diagonal_side_height(s32, s16, s16, s16);                /* extern */
s32 check_movement_clearance_and_height();    /* extern */
s32 compare_monster_neighbor_values(s32, s32, s32, s32);                  /* extern */
struct EntityRec; s16 get_actor_height_difference(struct EntityRec *, struct EntityRec *);                  /* extern */
void *find_valid_monster_neighbor();                /* extern */
void *place_actor_at_directional_neighbor();           /* extern */
u16 get_rounded_facing_and_rounding_flag();          /* extern */
s32 rebuild_monster_reachable_tiles(u8 *, s32, u8 *, u16 *);  /* extern */
s32 update_actor_proximity_flag(void *, void *, s32, s32, s8 *); /* extern */
s32 generate_random_value();                            /* extern */
struct EntityRec; void update_actor_status_and_food(struct EntityRec *);                      /* extern */
s16 sample_terrain_surface_height();                   /* extern */
s32 func_8016C720();          /* extern */
typedef struct {
    u8 pad[0xC];
    u16 flags;
    u8 tail[6];
} D_800E2970Entry;
extern s16 D_8006CD00[];
extern s16 D_8006CCD8[8];
extern u8 D_80082E80[];
extern u16 D_80082EA4;
extern D_800E2970Entry D_800E2970[];

static __inline__ u8 get_y_step(s16 byte_offset) {
    return ((u8 *)dir_step_y)[byte_offset];
}

/* Selects a movement direction and advances the actor path through available tiles. */
void advance_actor_path(void *motion, void *context, S_8016BF74_2 *position, void *actor) {
    s32 turn_index;
    s32 near_target;
    u8 *x_offsets;
    s32 old_tile_mask;
    s32 new_tile_mask;
    s32 target_y;
    s32 target_x;
    s32 y_offset;
    s32 world_y;
    s32 world_x;
    s16 target_angle;
    s16 actor_distance;
    u16 tile_x_or_offset;
    u8 *x_offset_ptr;
    s32 move_value;
    u32 initialized_bit;
    s32 actor_flags;
    s32 direction_offset;
    s32 result;
    s8 tile_index;
    s32 state_flags;
    MovingTile *target_position;
    void *x_offset;
    s32 active_actor;
    s32 path_status;
    s32 tile_y;
    s32 first_tile_y;
    s32 current_angle;
    s16 candidate_angle;
    void *motion_flags;
    s32 source_x;
    s32 source_y;
    s32 dest_x;
    s32 dest_y;
    s32 new_tile_flags;
    s32 step_y;
    s32 next_x;
    s16 current_x;
    s16 next_path_index;
    s32 current_y;
    u8 *world_position;

    state_flags = g_dungeon_status.flags;
    near_target = 0;
    if ((state_flags & 0x4000) || (((S_8016BF74_1 *)actor)->unk_71.s >= 0)) {
        if (((u8) ((S_8016BF74_1 *)actor)->unk_12 >= 2U) || ((func_8016C720(motion, context, position, actor) << 0x10)
            == 0)) {
            update_actor_status_and_food(actor);
            return;
        }
        active_actor = ((s32)g_dungeon_status.active_actor);
        if ((void *)active_actor == actor) {
            path_status = 0xC008;
            ((S_8016BF74_1 *)actor)->unk_46 = (u16) path_status;
            return;
        }
        return;
    }
    if (state_flags & 0x2000) {
        update_actor_proximity_flag(position, actor, 3, 6, motion + 0x9C);
        actor_flags = ((S_8016BF74_1 *)actor)->unk_1C;
        if (actor_flags & 0x410) {
            if (actor_flags & 0x400) {
                initialized_bit = (s32)(find_valid_monster_neighbor(actor, position->unk_24.at00.v, position->unk_24.at01.v));
                if ((void *)initialized_bit != NULL) {
                    source_x = position->unk_24.at00.v;
                    target_position = ((SpriteLinkPrefixView *)(void *)initialized_bit)[-1].unk_00;
                    source_y = position->unk_24.at01.v;
                    dest_x = target_position->unk_24;
                    dest_y = target_position->unk_25;
                    motion_flags = motion + 0x98;
                    ((S_8016BF74_1 *)actor)->unk_2A.u = get_rounded_facing_and_rounding_flag(source_x, source_y, dest_x, dest_y, motion_flags);
                    ((S_8016BF74_1 *)actor)->unk_71.u &= 0x7F;
                    return;
                }
                move_value = ((S_8016BF74_1 *)actor)->unk_14;
                if (move_value >= 0) {
                    initialized_bit = 0x80000000;
                    move_value |= initialized_bit;
                    ((S_8016BF74_1 *)actor)->unk_14 = move_value;
                    result = generate_random_value();
                    ((S_8016BF74_1 *)actor)->unk_2A.u += (result & 7) << 9;
                }
            } else {
                x_offset = place_actor_at_directional_neighbor(actor, position->unk_24.at00.v, position->unk_24.at01.v,
                    (s16) ((S_8016BF74_1 *)actor)->unk_2A.u);
                if (x_offset != NULL) {
                    ((S_8016BF74_1 *)actor)->unk_71.u &= 0x7F;
                    return;
                }
            }
        } else if (((S_8016BF74_5 *)motion)->unk_B2 != 0) {
            if (!(((S_8016BF74_1 *)actor)->unk_46 & 0x8000)) {
                if (actor_flags & 0x20000) {
                    direction_offset = ((((S_8016BF74_1 *)actor)->unk_45 + ((s32) (((u16)D_800814A8->facing) << 0x10)
                        >> 0x19)) & 7) * 2;
                    world_x = D_80082E80[0x24];
                    world_y = D_80082E80[0x25];
                    x_offset = (void *)(*(u16 *)((u8 *)(((s32 *)dir_step_x)) + direction_offset));
                    y_offset = (*(u16 *)((u8 *)(((s32 *)dir_step_y)) + direction_offset));
                    current_x = (((S_8016BF74_2 *)position)->unk_24.at00.v);
                    target_x = world_x + ((s32)x_offset);
                    target_y = world_y + y_offset;
                    if ((current_x != (target_x & 0xFFFF)) || (position->unk_24.at01.v != (target_y & 0xFFFF))) {
                        target_angle = get_rounded_facing_and_rounding_flag(position->unk_24.at00.v, position->unk_24.at01.v, (s16) target_x,
                            (s16) target_y, motion + 0x98);
                        ((S_8016BF74_1 *)actor)->unk_2A.u = (u16) target_angle;
                        if ((check_movement_clearance_and_height(target_angle, position, actor, 0x20) << 0x10) <= 0) {
                            u8 *fallback_position;

                            fallback_position = (u8 *)&D_80082EA4 - 0x24;
                            ((S_8016BF74_1 *)actor)->unk_2A.u = get_rounded_facing_and_rounding_flag(position->unk_24.at00.v,
                                position->unk_24.at01.v, fallback_position[0x24], fallback_position[0x25],
                                motion + 0x98);
                        }
                        world_position = (u8 *)&D_80082EA4 - 0x24;
                        result = compare_monster_neighbor_values(position->unk_24.at00.v, position->unk_24.at01.v, world_position[0x24],
                            world_position[0x25]);
                        if ((result << 0x10) != 0) {
                            near_target = 1;
                        }
                    } else {
                        ((S_8016BF74_1 *)actor)->unk_71.u &= 0x7F;
                        return;
                    }
                } else {
                    rebuild_monster_reachable_tiles((u8 *)(position), ((S_8016BF74_5 *)motion)->unk_9C, actor, motion + 0x98);
                }
            }
        } else {
            tile_index = position->unk_26;
            if ((tile_index < 0) || !(D_800E2970[tile_index].flags & 2)) {
                if (!(((S_8016BF74_1 *)actor)->unk_46 & 0x8000)) {
                    initialized_bit = (s32)(place_actor_at_directional_neighbor(actor, position->unk_24.at00.v, position->unk_24.at01.v,
                        (s16) ((S_8016BF74_1 *)actor)->unk_2A.u));
                    if (((void *)initialized_bit == NULL)
                        || !(((S_8016BF74_7 *)(void *)initialized_bit)->unk_1C & 0x2000)
                        || (get_actor_height_difference((void *)initialized_bit, actor) >= 0x81)
                        || ((check_diagonal_side_height(((s32) (((S_8016BF74_1 *)actor)->unk_2A.u << 0x10) >> 0x19) & 0xFFFF,
                        position->unk_24.at00.v, position->unk_24.at01.v,
                        (s16) (((S_8016BF74_1 *)actor)->unk_88 - 0x20)) << 0x10) == 0)) {
                        if (((S_8016BF74_1 *)actor)->unk_1C & 0x20000) {
                            u8 *world_origin;

                            world_origin = (u8 *)&D_80082E80;
                            ((S_8016BF74_1 *)actor)->unk_2A.u = get_rounded_facing_and_rounding_flag(position->unk_24.at00.v,
                                position->unk_24.at01.v, world_origin[0x24], world_origin[0x25], motion + 0x98);
                            if ((compare_monster_neighbor_values(position->unk_24.at00.v, position->unk_24.at01.v, world_origin[0x24],
                                world_origin[0x25]) << 0x10) != 0) {
                                actor_distance = get_actor_height_difference(D_800814A8, actor);
                                if (actor_distance < 0x81) {
                                    result = check_diagonal_side_height(((s32) (((S_8016BF74_1 *)actor)->unk_2A.u << 0x10)
                                        >> 0x19) & 0xFFFF, position->unk_24.at00.v, position->unk_24.at01.v,
                                        (s16) (((S_8016BF74_1 *)actor)->unk_88 - 0x20));
                                    if ((result << 0x10) != 0) {
                                        ((S_8016BF74_1 *)actor)->unk_71.u &= 0x7F;
                                        return;
                                    }
                                }
                            } else {
                            }
                        } else {
                            rebuild_monster_reachable_tiles((u8 *)(position), ((S_8016BF74_5 *)motion)->unk_9C, actor, motion + 0x98);
                        }
                    } else {
                        ((S_8016BF74_1 *)actor)->unk_71.u &= 0x7F;
                        return;
                    }
                }
            } else {
                rebuild_monster_reachable_tiles((u8 *)(position), ((S_8016BF74_5 *)motion)->unk_9C, actor, motion + 0x98);
            }
        }
        turn_index = 0;
        x_offsets = (u8 *)D_8006CCD8;
        do {
            current_angle = ((S_8016BF74_1 *)actor)->unk_2A.s;
            if (((S_8016BF74_5 *)motion)->unk_98 & 2) {
                move_value = D_8006CD00[turn_index];
                candidate_angle = current_angle - move_value;
            } else {
                move_value = D_8006CD00[turn_index];
                candidate_angle = current_angle + move_value;
            }
            if ((check_movement_clearance_and_height(candidate_angle, position, actor, 0x20) << 0x10) > 0) {
                if (turn_index >= 3) {
                    move_value = near_target;
                    if (move_value != 0) {
                        ((S_8016BF74_1 *)actor)->unk_71.u &= 0x7F;
                        return;
                    }
                }
                ((S_8016BF74_1 *)actor)->unk_2A.u = (u16) candidate_angle;
                ((ActorStatusBytesView *)((actor + ((u8) ((S_8016BF74_1 *)actor)->unk_71.s & 0x7F))))->unk_74 =
                    (u8) position->unk_24.at00.v;
                ((ActorStatusBytesView *)((actor + ((u8) ((S_8016BF74_1 *)actor)->unk_71.s & 0x7F))))->unk_7C =
                    (u8) position->unk_24.at01.v;
                next_path_index = (u8) ((S_8016BF74_1 *)actor)->unk_71.s + 1;
                x_offset_ptr = (u8 *)(((S_8016BF74_1 *)actor)->unk_1C & 0x2000);
                ((S_8016BF74_1 *)actor)->unk_71.s = (s8) next_path_index;
                tile_x_or_offset = position->unk_24.at00.v;
                first_tile_y = position->unk_24.at01.v;
                old_tile_mask = 0x3000;
                if ((s32)x_offset_ptr) {
                    old_tile_mask = 0x300;
                }
                update_map_cell_flags_with_item_limit(tile_x_or_offset, first_tile_y, old_tile_mask);
                tile_x_or_offset = ((u16) ((S_8016BF74_1 *)actor)->unk_2A.u >> 8) & 0xE;
                x_offset_ptr = (u8 *)((u32) tile_x_or_offset + (u32) x_offsets);
                position->unk_24.at00.v = (u8) (position->unk_24.at00.v + *x_offset_ptr);
                current_y = position->unk_24.at01.v;
                step_y = get_y_step(tile_x_or_offset);
                next_x = position->unk_24.at00.v;
                position->unk_24.at01.v = (u8) (current_y + step_y);
                new_tile_mask = 0x3000;
                new_tile_flags = ((S_8016BF74_1 *)actor)->unk_1C & 0x2000;
                tile_y = position->unk_24.at01.v;
                if (new_tile_flags) {
                    new_tile_mask = 0x300;
                }
                cycle_map_cell_flags(next_x, tile_y, new_tile_mask);
                break;
            }
            if ((turn_index == 0) && (D_80082EA4 != position->unk_24.at00u.v)
                && ((check_entity_relation(actor, (struct EntityRec *)(((s32)D_800814A8->unk_58) + 0x20)) << 0x10) != 0)) {
                return;
            }
            turn_index += 1;
        } while (turn_index < 8);
        {
            result = turn_index < 8;
            if (result == 0) {
                ((S_8016BF74_1 *)actor)->unk_71.s = (s8) ((u8) ((S_8016BF74_1 *)actor)->unk_71.s & 0x7F);
                ((S_8016BF74_1 *)actor)->unk_46 = (u16) (((S_8016BF74_1 *)actor)->unk_46 & 0x7FFF);
                update_actor_status_and_food(actor);
                return;
            }
            ((S_8016BF74_1 *)actor)->unk_46 = (u16) (((S_8016BF74_1 *)actor)->unk_46 & 0x7FFF);
            ((S_8016BF74_5 *)motion)->unk_9C = (s8) (u8) position->unk_26;
            ((S_8016BF74_1 *)actor)->unk_6D.u = (u8) (((S_8016BF74_1 *)actor)->unk_6D.u - 1);
            g_dungeon_status.activity_counts.parts.pending_movement_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_movement_count) + 1);
            if (((S_8016BF74_1 *)actor)->unk_6D.s == 0) {
                ((S_8016BF74_1 *)actor)->unk_71.u &= 0x7F;
                return;
            }
            turn_index = sample_terrain_surface_height((position->unk_24.at00.v << 6) | 0x20, (position->unk_24.at01.v << 6) | 0x20,
                (s16) (((S_8016BF74_1 *)actor)->unk_88 - 0x20));
            result = turn_index < 0x200;
            if (result != 0) {
                ((S_8016BF74_1 *)actor)->unk_88 = (u16) turn_index;
            }
            return;
        }
    }
    return;
}
