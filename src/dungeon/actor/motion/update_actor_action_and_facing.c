#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/player/position.h"
#include "dungeon/actor/motion.h"
#include "dungeon/actor.h"

extern void select_record_entry_and_value(void *state, void *entries, short index);
extern void clear_slots_of_type(void *actor, s32 value);

extern void *actor_default_frames[8];

/* Refresh the directional sprite and advance the actor state when sprite flags are set. */
void update_actor_action_and_facing_2(Rec_func_8008ACDC_arg0 *state, EntityRec *motion, SpriteFrameState *sprite, EntityRec *actor)
{
    s32 tracked_addr;

    if (state->unk_9B.as_u8 == 0) {
        apply_clamped_actor_value_delta(actor);
        state->unk_9B.as_u8++;
    }

    if (sprite->flags & 0xE000) {
        sprite->frameTable = actor_default_frames;
        select_record_entry_and_value(
            sprite,
            actor_default_frames[
                ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);

        tracked_addr = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_addr == (u32)((u8 *)actor - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_addr & 0x7FFFFFFF;
        }

        if (actor->unk_28 == 0) {
            actor->unk_28 = 0;
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            clear_slots_of_type(actor, STATUS_FROG);
            reset_actor_motion_at_sprite_tile(state, motion, sprite, actor);
            return;
        }

        state->unk_96.as_s16 = 8;
        state->unk_8C.as_pv = handle_actor_commands_and_facing;
    }
}
