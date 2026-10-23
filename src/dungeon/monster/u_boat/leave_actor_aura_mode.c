#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80176084_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x14];
    u8 unk_B0;
    u8 unk_B1;
    u8 pad_B2[0x2];
    u8 unk_B4;
    s8 unk_B5;
} S_80176084_0;   /* arg0 in leave_actor_aura_mode */

extern void clear_slots_of_type();
extern void select_sprite_entry();
extern void set_record_integer_tile_center();
extern s32 play_sound_if_enabled();
extern s32 try_move_actor_to_valid_position();
void create_owner_linked_directional_object(u8 *owner_data, u8 *source_position, u8 *source_sprite);

extern u8 uboat_default_frames[];
extern u8 D_800E2448[];
#include "dungeon/monster/u_boat.h"

/* Advance a two-phase animation transition and finalize the entity state. */
void leave_actor_aura_mode(void *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity) {
    u16 start_ticks;
    u16 finish_ticks;
    u8 phase;
    u8 step;
    u32 active_step;

    phase = ((S_80176084_0 *)state)->unk_9B;
    if (phase != 0) {
        if (phase != 1) {
            return;
        }
    } else {
        step = ((S_80176084_0 *)state)->unk_B1;
        active_step = 1;
        if (step == 0 || step == active_step) {
            if (step == 0) {
                do {
                    ((S_80176084_0 *)state)->unk_B1 = active_step;
                } while (0);
                ((S_80176084_0 *)state)->unk_96 = 4U;
                sprite->frameTable = (u8 *)D_800E2448;
                select_sprite_entry(sprite, D_800E2448[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                    0);
                if (!((sprite->flags & 0x8000)
                      || (play_sound_if_enabled(0x801), ((sprite->flags & 0x8000) != 0)))) {
                    return;
                }
            }
            start_ticks = ((S_80176084_0 *)state)->unk_96;
            ((S_80176084_0 *)state)->unk_96 = (u16)(start_ticks - 1);
            if (((start_ticks << 0x10) <= 0) || (sprite->flags & 0xE000)) {
                motion->velocity_z = 0;
                motion->velocity_y = 0;
                motion->velocity_x = 0;
                set_record_integer_tile_center(motion, sprite->unk_24, sprite->unk_25);
                entity->flags1C |= 0x40000;
                ((S_80176084_0 *)state)->unk_B5 = 0;
                ((S_80176084_0 *)state)->unk_98 |= 8;
                sprite->frameTable = (u8 *)uboat_default_frames;
                select_sprite_entry(sprite, uboat_default_frames[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                    0);
                ((S_80176084_0 *)state)->unk_96 = 5U;
                ((S_80176084_0 *)state)->unk_9B++;
                ((S_80176084_0 *)state)->unk_B1++;
                if (((S_80176084_0 *)state)->unk_B0 == 0) {
                    create_owner_linked_directional_object(state, motion, sprite);
                }
            }
        }
        if (!(sprite->flags & 0x8000)) {
            return;
        }
    }
    finish_ticks = ((S_80176084_0 *)state)->unk_96;
    ((S_80176084_0 *)state)->unk_96 = (u16)(finish_ticks - 1);
    if (((finish_ticks << 0x10) <= 0) || (sprite->flags & 0xE000)) {
        sprite->unk_06 = 0;
        ((S_80176084_0 *)state)->unk_8C = (u8 *)uboat_behavior_entry;
        clear_slots_of_type(entity, 0x1B);
        if (((S_80176084_0 *)state)->unk_B4 == 0) {
            g_dungeon_status.active_actor = 0;
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            entity->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
        try_move_actor_to_valid_position(state, motion, sprite, entity);
    }
}
