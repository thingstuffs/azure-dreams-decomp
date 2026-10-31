#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor.h"
#include "dungeon/player/object.h"
#include "dungeon/system.h"


extern void clear_slots_of_type(ActorRecord *owner, s8 match_type);
void create_owner_linked_directional_object(ActorRecord *owner_data, ObjectPosition *source_position, SpriteFrameState *source_sprite);

extern u8 uboat_default_frames[];
extern u8 u_boat_aura_frames[];
#include "dungeon/monster/u_boat.h"
#include "engine/graphics.h"

/* Advance a two-phase animation transition and finalize the entity state. */
void leave_actor_aura_mode(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity) {
    u16 start_ticks;
    u16 finish_ticks;
    u8 phase;
    u8 step;
    u32 active_step;

    phase = state->action_phase.u;
    if (phase != 0) {
        if (phase != 1) {
            return;
        }
    } else {
        step = state->unk_B0.bytes[1];
        active_step = 1;
        if (step == 0 || step == active_step) {
            if (step == 0) {
                /* BYTES: sched1/sched2 region barrier or tie: unwrap reorders independent insns (no memory dependence) (ledger/onetrip_loadbearing.jsonl: dungeon/func_80D40884). */
                do {
                    state->unk_B0.bytes[1] = active_step;
                } while (0);
                state->action_timer.u = 4U;
                sprite->frameTable = u_boat_aura_frames;
                select_sprite_entry(sprite, u_boat_aura_frames[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                    0);
                if (!((sprite->flags & 0x8000)
                      || (play_sound_if_enabled(0x801), ((sprite->flags & 0x8000) != 0)))) {
                    return;
                }
            }
            start_ticks = state->action_timer.u;
            state->action_timer.u = (u16)(start_ticks - 1);
            if (((start_ticks << 0x10) <= 0) || (sprite->flags & 0xE000)) {
                motion->velocity_z = 0;
                motion->velocity_y = 0;
                motion->velocity_x = 0;
                set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
                entity->flags1C |= 0x40000;
                state->unk_B4.bytes[1] = 0;
                state->action_state_flags |= 8;
                sprite->frameTable = uboat_default_frames;
                select_sprite_entry(sprite, uboat_default_frames[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                    0);
                state->action_timer.u = 5U;
                state->action_phase.u++;
                state->unk_B0.bytes[1]++;
                if (state->unk_B0.bytes[0] == 0) {
                    create_owner_linked_directional_object(state, motion, sprite);
                }
            }
        }
        if (!(sprite->flags & 0x8000)) {
            return;
        }
    }
    finish_ticks = state->action_timer.u;
    state->action_timer.u = (u16)(finish_ticks - 1);
    if (((finish_ticks << 0x10) <= 0) || (sprite->flags & 0xE000)) {
        sprite->depth_bias = 0;
        state->unk_8C.address = uboat_behavior_entry;
        clear_slots_of_type(entity, STATUS_NO_TILE_OCCUPANCY);
        if (state->unk_B4.bytes[0] == 0) {
            g_dungeon_status.active_actor = 0;
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            entity->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
        try_move_actor_to_valid_position(state, motion, sprite, entity);
    }
}
