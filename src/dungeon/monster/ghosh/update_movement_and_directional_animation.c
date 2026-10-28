#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"

extern void select_sprite_entry(void *, s32, s32);
extern s32 rsin(s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void on_actor_status_updated(void *);

extern u8 ghosh_action_resume_address[];
extern u8 ghosh_frame_set_3[];
extern u8 ghosh_frame_set_4[];

typedef struct S_8016CB80_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    s32 unk_A0;
    u8 pad_A4[0xF];
    u8 unk_B3;
} S_8016CB80_0;   /* arg0 in update_movement_and_directional_animation */

/* Updates movement, directional animation, and action completion. */
void update_movement_and_directional_animation(void *state, void *motion_arg, void *actor_arg, void *entity_arg) {
    void *motion = motion_arg;
    SpriteFrameState *actor= actor_arg;
    void *entity = entity_arg;
    u16 direction_info;
    s32 move_ticks;
    s32 next_move_ticks;
    s32 tile_x;
    s32 pixel_offset;
    s32 pixel_y;
    s32 entity_flags;
    u16 action_ticks;
    u16 status_flags;
    s32 phase;
    register void *current_anims;
    u8 *anims;

    phase = ((S_8016CB80_0 *)state)->unk_9B;
    switch (phase) {
    case 0:
        ((S_8016CB80_0 *)state)->unk_98 = (u16) (((S_8016CB80_0 *)state)->unk_98 | 8);
        ((EntityRec *)entity)->flags1C = (s32) (((EntityRec *)entity)->flags1C & ACTOR_GROUNDED_CLEAR_MASK);
        ((S_8016CB80_0 *)state)->unk_9E = 5;
        ((S_8016CB80_0 *)state)->unk_A0 = 0;
        ((S_8016CB80_0 *)state)->unk_9B = (u8) (((S_8016CB80_0 *)state)->unk_9B + 1);
    case 1:
        move_ticks = ((S_8016CB80_0 *)state)->unk_9E;
        ((S_8016CB80_0 *)state)->unk_90 = (s32) (((S_8016CB80_0 *)state)->unk_90 - ((S_8016CB80_0 *)state)->unk_A0);
        if (move_ticks != 0) {
            tile_x = actor->tile_x << 6;
            pixel_offset = ((EntityRec *)motion)->x.w.i - 0x20;
            ((EntityRec *)motion)->unk_0C = (s32) ((s32) ((tile_x - pixel_offset) << 0x10) / move_ticks);
            pixel_y = ((EntityRec *)motion)->y.w.i - 0x20;
            ((EntityRec *)motion)->unk_10 = (s32) ((s32) (((actor->tile_y << 6) - pixel_y)
                << 0x10) / (s16) ((S_8016CB80_0 *)state)->unk_9E);
            ((S_8016CB80_0 *)state)->unk_A0 = (s32) ((0 - rsin(((S_8016CB80_0 *)state)->unk_9E * 0x199))
                << 0xA);
        }
        ((S_8016CB80_0 *)state)->unk_90 = (s32) (((S_8016CB80_0 *)state)->unk_90 + ((S_8016CB80_0 *)state)->unk_A0);
        next_move_ticks = (u16) ((S_8016CB80_0 *)state)->unk_9E - 1;
        ((S_8016CB80_0 *)state)->unk_9E = next_move_ticks;
        if ((next_move_ticks << 0x10) < 0) {
            ((S_8016CB80_0 *)state)->unk_90 = 0;
            ((S_8016CB80_0 *)state)->unk_98 = (u16) (((S_8016CB80_0 *)state)->unk_98 & 0xFFF7);
            ((EntityRec *)entity)->flags1C = (s32) (((EntityRec *)entity)->flags1C | ACTOR_GROUNDED);
            ((S_8016CB80_0 *)state)->unk_9B = (u8) (((S_8016CB80_0 *)state)->unk_9B + 1);
        }
    case 2:
        if (((EntityRec *)entity)->flags1C & ACTOR_GROUNDED) {
            ((S_8016CB80_0 *)state)->unk_98 = (u16) (((S_8016CB80_0 *)state)->unk_98 & 0xFFF7);
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion, actor->tile_x, actor->tile_y);
            ((S_8016CB80_0 *)state)->unk_9B = (u8) (((S_8016CB80_0 *)state)->unk_9B + 1);
        }
        break;
    case 3:
        if (((S_8016CB80_0 *)state)->unk_B3 == 0) {
            current_anims = actor->frameTable;
            anims = (u8 *)&ghosh_frame_set_3;
            if (current_anims != anims) {
                (actor->frameTable) = anims;
                select_sprite_entry(actor, *(u8 *)((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100)
                    >> 9) & 7) + (u32)anims), 0);
            }
        } else {
            current_anims = actor->frameTable;
            anims = ghosh_frame_set_4;
            if (current_anims != anims) {
                (actor->frameTable) = anims;
                select_sprite_entry(actor, *(u8 *)((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100)
                    >> 9) & 7) + (u32)anims), 0);
            }
        }
        break;
    }

    action_ticks = ((S_8016CB80_0 *)state)->unk_96 - 1;
    ((S_8016CB80_0 *)state)->unk_96 = action_ticks;
    if ((action_ticks << 0x10) <= 0) {
        ((EntityRec *)motion)->flags14 = 0;
        ((EntityRec *)motion)->unk_10 = 0;
        ((EntityRec *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion, actor->tile_x, actor->tile_y);
        advance_status_timers(entity);
        if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
            g_dungeon_status.activity_counts.parts.pending_movement_count = (s16) ((u16) g_dungeon_status.activity_counts.parts.pending_movement_count - 1);
        }
        entity_flags = ((EntityRec *)entity)->flags1C;
        if (entity_flags & 0x2000) {
            status_flags = ((EntityRec *)entity)->unk_46;
            if (status_flags & 0x8000) {
                ((EntityRec *)entity)->unk_46 = status_flags & 0x7FFF;
            }
        } else {
            if (!(entity_flags & 0x410)) {
                if (entity_flags & 0x20000) {
                    ((EntityRec *)entity)->facing = get_rounded_facing_and_rounding_flag(actor->tile_x,
                        actor->tile_y, reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &direction_info);
                }
            }
        }
        if ((check_actor_floor_trap(actor, entity) << 0x10) > 0) {
            ((S_8016CB80_0 *)state)->unk_8C = ghosh_action_resume_address;
            on_actor_status_updated(entity);
        }
    }
}

