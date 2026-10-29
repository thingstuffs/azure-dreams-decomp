#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800A9E70_arg0.h"

extern s32 prepare_directional_attack();
extern s16 get_actor_height_difference(ActorRecord *left_record, ActorRecord *right_record);
extern s16 try_claim_dungeon_action_slot(ActorRecord *actor);
extern s32 check_entity_interaction_compatibility();
extern s32 apply_camera_offset_and_select_target(void *object_addr, void *source_pos, s32 helper_arg, s32 slot_value);
#include "dungeon/monster/dreamin.h"
#include "engine/graphics.h"
#include "dungeon/item.h"

/* Attempt an actor transition and update its state and sprite on success. */
s32 attempt_actor_transition(ActorRecord *state, ObjectPosition *action_id, SpriteFrameState *sprite, ActorRecord *actor) {
    u16 *status;
    s32 transitioned;
    ActorRecord *target;

    actor->movement_queue_state &= 0x7F;
    status = ((u16 *)(&g_dungeon_status));
    transitioned = 0;
    if (((u16 *)status)[1] & 0x2000) {
        return -1;
    }
    target = probe_directional_neighbor(actor, sprite->tile_x,
                           sprite->tile_y, actor->facing);
    if ((check_entity_interaction_compatibility(actor, target) << 16) == 0) {
        return transitioned;
    }
    {
        u16 status_flags = status[1];

        if (status_flags & 0x2000) {
            return -1;
        }
        if (!(actor->action_flags & ACTOR_ACTION_PENDING) && (status_flags & 8)) {
            return -1;
        }
    }
    if ((s16)(-get_actor_height_difference(target, actor) + 0x40) >= 0x81U) {
        return transitioned;
    }

    transitioned = 1;
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }
    apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_id, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    {
        u16 state_flags;

        state_flags = state->action_state_flags;
        state->action_phase.u = 0;
        ((Rec_func_800A9E70_arg0 *)state)->unk_8C = 0;
        if (state_flags & 0x8000) {
            state->action_id.u = 0x17;
            actor->unk_84 = 0x10;
            actor->unk_85 = 0x10;
        } else {
            state->action_id.u = 0x11;
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
    }

    sprite->frameTable = dreamin_direction_frames;
    select_sprite_entry(sprite,
                  dreamin_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                  0);
    actor->pending_turn_updates--;
    if (state->action_id.u != 0x11) {
        return transitioned;
    }
    prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
    return transitioned;

}
