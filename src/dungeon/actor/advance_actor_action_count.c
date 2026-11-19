#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "dungeon/player/actor_sprite_sources.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon.h"
#include "dungeon/actor/motion.h"
#include "dungeon/level.h"

#include "dungeon/player/object/action_state.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "slus.h"
#include "dungeon/actor.h"
#include "dungeon/actor/state.h"


/* Advance the actor action state, updating its animation and the dungeon action count. */
void advance_actor_action_count(ActorRecord *controller, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 actor_flags;
    s32 state;

    state = controller->action_phase;
    switch (state) {
    case 0:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        sprite->frameTable = actor_action_frames;
        select_record_entry_and_value(sprite,
            actor_action_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        controller->action_phase++;
        return;
    case 1:
        if (g_dungeon_status.flags & 0x1000) {
            return;
        }
        if (actor->hp_delta != 0) {
            if (begin_ready_actor_directional_action(controller, context, sprite, 0) != 0) {
                return;
            }
        }
        if ((has_pending_actor_or_turn_action(actor) << 0x10) != 0) {
            return;
        }
        actor_flags = actor->flags1C;
        if (actor_flags & 0x100) {
            begin_pushed_actor_move(controller, context, sprite, actor);
            return;
        }
        if (actor_flags & 0x80000) {
            begin_actor_move_to_target_facing(controller, context, sprite, actor);
            finish_actor_parent_motion(controller, context, sprite, actor);
            return;
        }
        if (actor->pending_turn_updates == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(actor) << 0x10) != 0) {
            if ((check_entity_relation(actor,
                    NODE_BODY(primary_actor_record->previous_actor_header)) << 0x10) != 0) {
                return;
            }
        }
        update_actor_status_and_mp(actor);
        on_actor_status_updated(actor);
        if (actor->mp == 0) {
            return;
        }
        sprite->frameTable = actor_action_frames;
        select_record_entry_and_value(sprite,
            actor_action_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        actor->flags1C |= 0x40000;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
        controller->action_phase++;
        return;
    case 2:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        actor->flags1C &= ~0x208;
        controller->unk_8C.handler = update_actor_facing_animation;
        return;
    default:
        return;
    }
}
