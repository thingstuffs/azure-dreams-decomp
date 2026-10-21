#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 check_neighbor_tile_blocking();             /* extern */
s32 find_valid_nearby_position();      /* extern */
void *prepare_directional_attack(); /* extern */
void apply_attack_power_and_element_effects(); /* extern */
u8 find_active_rect_containing_point();                           /* extern */
s32 update_actor_proximity_flag(); /* extern */
void set_record_integer_tile_center();              /* extern */
void begin_actor_random_warp(); /* extern */
s16 sample_terrain_surface_height();                   /* extern */

/* Advance tile movement, handle object contact, and finalize the stopping position. */
s32 update_thrown_actor_travel(void *move_state, ObjectPosition *motion, SpriteFrameState *tile_pos, ActorRecord *actor) {
    u16 resolved_x;
    u16 resolved_y;
    s32 contact_tile_mask;
    s32 stop_tile_mask;
    s32 contact_flags;
    s32 stop_flags;
    u8 contact_x;
    u8 contact_y;
    u8 stop_x;
    u8 stop_y;
    s16 move_ticks;
    s32 target_x;
    s32 axis_pos;
    s16 ticks_left;
    s16 ground_height;
    void *hit_object;

    move_ticks = ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16;
    if (move_ticks != 0) {
        target_x = tile_pos->unk_24;
        axis_pos = motion->x.w.i;
        target_x <<= 6;
        axis_pos -= 0x20;
        motion->velocity_x = (s32) ((s32) ((target_x - axis_pos) << 0x10) / move_ticks);
        axis_pos = motion->y.w.i - 0x20;
        motion->velocity_y = (s32) ((s32) (((tile_pos->unk_25 << 6) - axis_pos)
            << 0x10) / (s16) ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16);
    }
    ticks_left = (u16) ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16 - 1;
    ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        hit_object = prepare_directional_attack(actor, tile_pos, ((s16)actor->movement_facing), 0, 0);
        if (hit_object != NULL) {
            apply_attack_power_and_element_effects(actor, 4, 1, 8, (s32) (s16) ((u16) ((s16)actor->movement_facing) + 0x800), 0, 1);
            apply_attack_power_and_element_effects(hit_object, 8, 1, 8, (s32) ((s16)actor->movement_facing), 0, 1);
            ((Rec_func_800A9E70_arg0 *)move_state)->unk_98 =
                (u16) (((Rec_func_800A9E70_arg0 *)move_state)->unk_98 & 0xFFF7);
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            actor->flags1C = (s32) (actor->flags1C | 0x40000000);
            ((Rec_func_800A9E70_arg0 *)move_state)->unk_9C.as_u8 = (u8) tile_pos->unk_26;
            tile_pos->unk_26 = find_active_rect_containing_point(tile_pos->unk_24, tile_pos->unk_25);
            update_actor_proximity_flag(tile_pos, actor, 3, 6, move_state + 0x9C);
            if ((find_valid_nearby_position(actor, tile_pos->unk_24, tile_pos->unk_25, &resolved_x, &resolved_y) << 0x10) == 0) {
                set_record_integer_tile_center(motion, tile_pos->unk_24, tile_pos->unk_25);
                begin_actor_random_warp(move_state, motion, tile_pos, actor);
                return 0;
            } else {
                tile_pos->unk_24 = resolved_x;
                tile_pos->unk_25 = resolved_y;
                set_record_integer_tile_center(motion, tile_pos->unk_24, tile_pos->unk_25);
                contact_flags = actor->flags1C;
                contact_x = tile_pos->unk_24;
                contact_y = tile_pos->unk_25;
                contact_tile_mask = 0x3000;
                if (contact_flags & 0x2000) {
                    contact_tile_mask = 0x300;
                }
                cycle_map_cell_flags(contact_x, contact_y, contact_tile_mask);
                actor->flags1C = (s32) (actor->flags1C & 0xFFDFFFFF);
                g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
                ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16 = 0;
                actor->movement_queue_state = 0;
                return 1;
            }
        }
        if ((check_neighbor_tile_blocking(((s16)actor->movement_facing), motion, tile_pos) << 0x10) != 0 && --actor->unk_8A > 0) {
            tile_pos->unk_24 = (u8) (tile_pos->unk_24 + *(((u16) ((s16)actor->movement_facing) >> 9 & 7) + dir_step_x));
            tile_pos->unk_25 = (u8) (tile_pos->unk_25 + *(((u16) ((s16)actor->movement_facing) >> 9 & 7) + dir_step_y));
            ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16 = 2;
        } else {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            ((Rec_func_800A9E70_arg0 *)move_state)->unk_98 =
                (u16) (((Rec_func_800A9E70_arg0 *)move_state)->unk_98 & 0xFFF7);
            ((Rec_func_800A9E70_arg0 *)move_state)->unk_9C.as_u8 = (u8) tile_pos->unk_26;
            tile_pos->unk_26 = find_active_rect_containing_point(tile_pos->unk_24, tile_pos->unk_25);
            update_actor_proximity_flag(tile_pos, actor, 3, 6, move_state + 0x9C);
            ground_height = sample_terrain_surface_height((tile_pos->unk_24 << 6) | 0x20, (tile_pos->unk_25 << 6) | 0x20,
                (s16) (((u16)motion->z.w.i) - 0x20));
            if (ground_height < 0x200) {
                ((Rec_func_800A9E70_arg0 *)move_state)->unk_90.at02_s16.v = 0;
                actor->ground_height = ground_height;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
            ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16 = 0;
            actor->flags1C = (s32) ((actor->flags1C | 0x40000000) & 0xFFDFFFFF);
            if ((find_valid_nearby_position(actor, tile_pos->unk_24, tile_pos->unk_25, &resolved_x, &resolved_y) << 0x10) == 0) {
                set_record_integer_tile_center(motion, tile_pos->unk_24, tile_pos->unk_25);
                begin_actor_random_warp(move_state, motion, tile_pos, actor);
                return 0;
            } else {
                tile_pos->unk_24 = resolved_x;
                tile_pos->unk_25 = resolved_y;
                set_record_integer_tile_center(motion, tile_pos->unk_24, tile_pos->unk_25);
                stop_flags = actor->flags1C;
                stop_x = tile_pos->unk_24;
                stop_y = tile_pos->unk_25;
                stop_tile_mask = 0x3000;
                if (stop_flags & 0x2000) {
                    stop_tile_mask = 0x300;
                }
                cycle_map_cell_flags(stop_x, stop_y, stop_tile_mask);
                actor->movement_queue_state = 0;
                return 1;
            }
        }
    }
    return 0;
}
