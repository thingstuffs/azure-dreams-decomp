#include "engine/graphics.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/system/random.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/player/object.h"
#include "dungeon/system.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor.h"
#include "dungeon/data.h"

extern u8 tyrant_direction_frames[];
extern s32 tyrant_action_resume_address;
extern u8 D_80173FD8;
extern M2C_UNK D_80173FE0;

/* Run the actor's eight-step sink animation, advancing its state and swapping the sprite each step. */
void run_the_actor_s_eight_step_sink_animation_advancing_state_swapping(ActorRecord *work, ObjectPosition *part_a, SpriteFrameState *part_b, ActorRecord *actor) {
    u8 *unused_ptr;
    s32 value;
    u16 flags;
    s32 state;
    s32 accum;
    s32 timer;

    state = work->action_phase;
    work->action_timer = (u16) (work->action_timer - 1);
    switch (state) {
    case 0:
    case 4:
        play_sound_if_enabled(0x51C);
        flags = part_b->flags;
        if (flags & 0x8000) {
            work->action_phase = 7;
            return;
        }
        if (!(flags & 0xE000)) {
            return;
        }
        part_b->frameTable = &D_80173FD8;
        select_sprite_entry(part_b, (&D_80173FD8)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        work->action_state_flags = (u16) (work->action_state_flags | 8);
        part_a->velocity_z = 0xFFF00000;
        actor->flags1C = (s32) (actor->flags1C & ACTOR_GROUNDED_CLEAR_MASK);
        work->unk_A0.value = 0;
        work->action_timer = 10;
        work->action_phase++;
        return;
    case 1:
    case 5:
        accum = work->unk_90.value;
        value = work->unk_A0.value;
        timer = (s16)(work->action_timer);
        work->unk_90.value = accum - value;
        if (timer != 0) {
            accum = value;
            value = part_a->velocity_z;
            work->unk_A0.value = (s32) (accum + value);
            part_a->velocity_z = (s32) (part_a->velocity_z + 0x30000);
        }
        accum = work->unk_90.value;
        value = work->unk_A0.value;
        timer = (s16)(work->action_timer);
        work->unk_90.value = accum + value;
        if (timer > 0) {
            return;
        }
        work->unk_90.value = 0;
        work->action_state_flags = (u16) (work->action_state_flags & 0xFFF7);
        actor->flags1C = (s32) (actor->flags1C | ACTOR_GROUNDED);
        work->action_phase++;
        return;
    case 2:
    case 6:
        work->action_state_flags = (u16) (work->action_state_flags & 0xFFF7);
        part_a->velocity_z = 0;
        part_a->velocity_y = 0;
        part_a->velocity_x = 0;
        set_record_integer_tile_center(part_a, part_b->tile_x, part_b->tile_y);
        part_b->frameTable = &D_80173FE0;
        select_sprite_entry(part_b, ((u8 *) ((u32) ((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
            + (u32) &D_80173FE0)))[0], 0);
        work->action_phase++;
        return;
    case 3:
        if (!(part_b->flags & 0xE000)) {
            return;
        }
        part_b->frameTable = tyrant_frame_set_1;
        select_sprite_entry(part_b, tyrant_frame_set_1[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        work->action_phase++;
        return;
    case 7:
        if (!(part_b->flags & 0xE000)) {
            return;
        }
        part_b->frameTable = tyrant_direction_frames;
        select_sprite_entry(part_b, tyrant_direction_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        advance_status_timers(actor);
        actor->pending_turn_updates = 0;
        actor->action_flags = (u16) (actor->action_flags & ACTOR_ACTION_CLEAR_PENDING_MASK);
        work->unk_8C.word_ptr = &tyrant_action_resume_address;
        work->action_state_flags = (u16) (work->action_state_flags | 0x8000);
        work->unk_AC.halves.high.s = (s16) ((generate_random_value() & 7) + 8);
        set_or_clear_actor_status_slot(actor, 0x1A, (s8) work->unk_AC.halves.high.s);
        return;
    default:
        return;
    }
}
