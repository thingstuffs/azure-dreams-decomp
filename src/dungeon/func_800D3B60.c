#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/actor_status.h"

typedef struct S_800D92C0_0 {
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
    s8 unk_71;
    u8 pad_72[0x16];
    u16 unk_88;
} S_800D92C0_0;   /* arg3 in advance_actor_traversable_heading */

typedef struct S_800D92C0_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x2C];
    s32 unk_58;
} S_800D92C0_1;   /* *D_800814A8 in advance_actor_traversable_heading */

typedef struct S_800D92C0_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    s8 unk_26;
} S_800D92C0_2;   /* arg2 in advance_actor_traversable_heading */


   /* (arg3 + ((u8) ((S_800D92C0_0 *)arg3)->unk_71 & 0x7F)) in advance_actor_traversable_heading */


typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonEntry;

/* Load-bearing second view of D_80082E80: the asm label gives cc1 a distinct SYMBOL_REF ("*D_80082E80") so cse
 * does not share the base register with the plain D_80082E80 uses (retail rebuilds the address after the calls). */
extern TileObject D_80082E80_initial __asm__("D_80082E80");
extern s16 D_8006CD00[];
void update_map_cell_flags_with_item_limit();
s32 check_entity_relation();
s32 cycle_map_cell_flags();
s32 check_movement_clearance_and_height();
s32 compare_monster_neighbor_values();
s32 rebuild_monster_reachable_tiles();
s32 get_rounded_facing_and_rounding_flag();
s32 update_actor_proximity_flag();
s32 generate_random_value();
void update_actor_status_and_food();
s16 sample_terrain_surface_height();

/* Advances an actor along a traversable heading and updates its movement state. */
void advance_actor_traversable_heading(void *move_state, void *context, S_800D92C0_2 *position, void *actor) {
    M2C_UNK tile_mask;
    s32 target_y;
    s32 target_x;
    s16 candidate_heading;
    s32 heading_delta;
    s16 target_heading;
    s16 direction_or_x;
    s32 next_y;
    s32 room_cache;
    s32 turn_flags;
    s32 flags_or_heading;
    s32 actor_flags;
    s32 movement_bits;
    s32 target_direction;
    s32 limit_turn;
    s8 room_id;
    s16 turn_index;
    u8 *turn_offsets;

    limit_turn = 0;
    if ((g_dungeon_status.flags & 0x4000) || (((S_800D92C0_0 *)actor)->unk_71 >= 0)) {
        update_actor_status_and_food(actor);
        return;
    }
    if (g_dungeon_status.flags & 0x2000) {
        room_cache = move_state + 0x9C;
        update_actor_proximity_flag(position, actor, 3, 6, room_cache);
        flags_or_heading = ((S_800D92C0_0 *)actor)->unk_1C;
        movement_bits = flags_or_heading & 0x410;
        if (movement_bits) {
            movement_bits = flags_or_heading & 0x400;
            if (movement_bits) {
                s32 marked_flags = ((S_800D92C0_0 *)actor)->unk_14;
                if (marked_flags >= 0) {
                    flags_or_heading = 0x80000000;
                    marked_flags |= flags_or_heading;
                    ((S_800D92C0_0 *)actor)->unk_14 = marked_flags;
                    ((S_800D92C0_0 *)actor)->unk_2A.u = (u16)(((S_800D92C0_0 *)actor)->unk_2A.u + ((generate_random_value() & 7) << 9));
                }
            }
            goto init_loop;
        }
        if ((((S_800D92C0_0 *)actor)->unk_71 < 0) && (g_dungeon_status.flags & 0x2000)) {
            update_actor_proximity_flag(position, actor, 3, 6, room_cache);
            actor_flags = ((S_800D92C0_0 *)actor)->unk_1C;
            if (actor_flags & 0x2000) {
                if (actor_flags & 0x20000) {
                    {
                        
                        target_direction = (((S_800D92C0_0 *)actor)->unk_45
                            + ((s32) (((S_800D92C0_1 *)(((int)D_800814A8)))->unk_2A << 0x10) >> 0x19)) & 7;
                        target_x = D_80082E80_initial.tileX + ((u16 *)dir_step_x)[target_direction];
                        target_y = D_80082E80_initial.tileY + ((u16 *)dir_step_y)[target_direction];
                    }
                    if ((position->unk_24.at00.v != (target_x & 0xFFFF))
                        || (position->unk_24.at01.v != (target_y & 0xFFFF))) {
                        turn_flags = move_state + 0x98;
                        target_heading = get_rounded_facing_and_rounding_flag(position->unk_24.at00u.v & 0xFF, position->unk_24.at01.v, (s16)target_x,
                            (s16)target_y, turn_flags);
                        ((S_800D92C0_0 *)actor)->unk_2A.u = (u16) target_heading;
                        if ((check_movement_clearance_and_height(target_heading, position, actor, 0x20) << 0x10) <= 0) {
                                                        ((S_800D92C0_0 *)actor)->unk_2A.u = get_rounded_facing_and_rounding_flag(position->unk_24.at00.v,
                                position->unk_24.at01.v, D_80082E80.tileX, D_80082E80.tileY, turn_flags);
                        }
                        {
                                                        s32 distance_result;
                            distance_result = compare_monster_neighbor_values(position->unk_24.at00.v, position->unk_24.at01.v,
                                D_80082E80.tileX, D_80082E80.tileY);
                            if ((distance_result << 0x10) != 0) {
                                limit_turn = 1;
                            }
                            turn_index = 0;
                        }
                        goto loop_entry;
                    }
                    ((S_800D92C0_0 *)actor)->unk_71 = (s8) ((u8) ((S_800D92C0_0 *)actor)->unk_71 & 0x7F);
                    return;
                }
            } else {
                room_id = position->unk_26;
                if ((room_id < 0) || !(D_800E2970[room_id].flags & 2)) {
                    if (((S_800D92C0_0 *)actor)->unk_46 & 0x8000) {
                        goto init_loop;
                    }
                }
            }
            rebuild_monster_reachable_tiles(position, ((Rec_func_800A9E70_arg0 *)move_state)->unk_9C.as_s8, actor, move_state + 0x98);
init_loop:
            turn_index = 0;
loop_entry:
            turn_offsets = (u8 *)D_8006CD00;
try_heading:
            flags_or_heading = ((S_800D92C0_0 *)actor)->unk_2A.s;
            if (((Rec_func_800A9E70_arg0 *)move_state)->unk_98 & 2) {
                heading_delta = ((s16 *)turn_offsets)[turn_index];
                candidate_heading = flags_or_heading - heading_delta;
            } else {
                heading_delta = ((s16 *)turn_offsets)[turn_index];
                candidate_heading = flags_or_heading + heading_delta;
            }
            if ((check_movement_clearance_and_height((s16)candidate_heading, position, actor, 0x20) << 0x10) > 0) {
                if (turn_index >= 3) {
                    s16 checked_limit = limit_turn;
                    if (checked_limit != 0) {
                        goto mask_and_return;
                    }
                }
                {
                    ((S_800D92C0_0 *)actor)->unk_2A.u = (u16) candidate_heading;
                    ((ActorStatusBytesView *)((actor + ((u8) ((S_800D92C0_0 *)actor)->unk_71 & 0x7F))))->unk_74 =
                        (u8) position->unk_24.at00.v;
                    ((ActorStatusBytesView *)((actor + ((u8) ((S_800D92C0_0 *)actor)->unk_71 & 0x7F))))->unk_7C =
                        (u8) position->unk_24.at01.v;
                    ((S_800D92C0_0 *)actor)->unk_71 = (s8) ((u8) ((S_800D92C0_0 *)actor)->unk_71 + 1);
                    update_map_cell_flags_with_item_limit(position->unk_24.at00.v, position->unk_24.at01.v,
                                  (((S_800D92C0_0 *)actor)->unk_1C & 0x2000) ? 0x300 : 0x3000);
                    direction_or_x = ((u16) ((S_800D92C0_0 *)actor)->unk_2A.u >> 8) & 0xE;
                    {
                        u8 *x_table_base = (u8 *)dir_step_x;
                        u8 next_x = position->unk_24.at00.v;
                        next_x += x_table_base[direction_or_x];
                        position->unk_24.at00.v = (u8) next_x;
                    }
                    position->unk_24.at01.v = (u8) (position->unk_24.at01.v + ((u8 *)dir_step_y)[direction_or_x]);
                    direction_or_x = position->unk_24.at00.v;
                    next_y = position->unk_24.at01.v;
                    tile_mask = 0x3000;
                    if (((S_800D92C0_0 *)actor)->unk_1C & 0x2000) {
                        tile_mask = 0x300;
                    }
                    cycle_map_cell_flags(direction_or_x, next_y, tile_mask);
                    goto post_loop;
                }
            }
            if (turn_index == 0) {
                if (*(u16 *)(&D_80082E80.tileX) == position->unk_24.at00u.v) {
                    if (++turn_index < 8) {
                        goto try_heading;
                    }
                    goto post_loop;
                }
                if ((check_entity_relation(actor, ((S_800D92C0_1 *)(((int)D_800814A8)))->unk_58 + 0x20) << 0x10) != 0) {
                    do {
                        return;
                    } while (0);
                }
            }
            if (++turn_index < 8) {
                goto try_heading;
            }

post_loop:
            {
                s32 post_index = turn_index;
                if (post_index >= 8) {
                    ((S_800D92C0_0 *)actor)->unk_71 = (s8) ((u8) ((S_800D92C0_0 *)actor)->unk_71 & 0x7F);
                    ((S_800D92C0_0 *)actor)->unk_46 = (u16) (((S_800D92C0_0 *)actor)->unk_46 & 0x7FFF);
                    update_actor_status_and_food(actor);
                    return;
                }
            }
            ((Rec_func_800A9E70_arg0 *)move_state)->unk_9C.as_s8 = (s8) (u8) position->unk_26;
            ((S_800D92C0_0 *)actor)->unk_6D.u = (u8) (((S_800D92C0_0 *)actor)->unk_6D.u - 1);
            {
                g_dungeon_status.unk_08 = (u16)(((u16)g_dungeon_status.unk_08) + 1);
            }
            if (((S_800D92C0_0 *)actor)->unk_6D.s == 0) {
mask_and_return:
                ((S_800D92C0_0 *)actor)->unk_71 = (s8) ((u8) ((S_800D92C0_0 *)actor)->unk_71 & 0x7F);
                return;
            }

            turn_index = sample_terrain_surface_height((position->unk_24.at00.v << 6) | 0x20, (position->unk_24.at01.v << 6) | 0x20,
                (s16) (((S_800D92C0_0 *)actor)->unk_88 - 0x20));
            if (turn_index < 0x200) {
                ((S_800D92C0_0 *)actor)->unk_88 = (u16) turn_index;
            }
        }
    }
}
