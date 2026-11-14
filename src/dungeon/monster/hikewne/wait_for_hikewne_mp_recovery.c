#include "engine/graphics/select_sprite_entry_api.h"
#include "shared/actor_status_flags.h"
#include "dungeon/monster/hikewne.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"
#include "records/Rec_func_8017360C_arg0.h"
#include "dungeon.h"
#include "dungeon/level.h"

#include "dungeon/player/object/action_state.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "dungeon/monster/hikewne_frames.h"

#include "dungeon/actor/state.h"

extern void update_directional_sprite_state_and_signals(void *, void *, SpriteFrameState *, void *);

/* Advance actor states, select directional animations, and process entity actions. */
void wait_for_hikewne_mp_recovery(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *animation, ActorRecord *entity) {
    s32 state;

    state = actor->action_phase;
    switch (state) {
    case 0:
    {
        u8 *direction_anims;

        if (!(animation->flags & 0xE000)) {
            return;
        }

        g_dungeon_status.activity_counts.parts.pending_action_count--;
        direction_anims = hikewne_frame_set_2;
        (animation->frameTable) = direction_anims;
        select_sprite_entry(animation,
            direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        actor->action_phase++;
        return;
    }
    case 1:
    {
        u32 entity_flags;

        if (entity->mp_value.parts.whole != 0) {

            (animation->frameTable) = hikewne_frame_set_3;
            select_sprite_entry(animation,
                hikewne_frame_set_3[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            entity->flags1C |= 0x40000;
            g_dungeon_status.activity_counts.parts.pending_action_count++;
            actor->action_phase++;
            return;
        }

        if (g_dungeon_status.flags & 0x1000) {
            return;
        }

        if (entity->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, context, animation, 0) != 0) {
                return;
            }
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        entity_flags = ((u32)entity->flags1C);
        if (entity_flags & 0x100) {
            begin_pushed_actor_move(actor, context, animation, entity);
            return;
        }

        if (entity_flags & 0x80000) {
            u16 stored_value;
            u16 pending_decrement;

            begin_actor_move_to_target_facing(actor, context, animation, entity);
            stored_value = actor->unk_90.parts.high;
            pending_decrement = actor->unk_A0.parts.high;
            actor->unk_A0.parts.high = 0;
            actor->unk_9E = 0;
            actor->unk_90.parts.high = stored_value - pending_decrement;
            update_directional_sprite_state_and_signals(actor, context, animation, entity);
            return;
        }

        if (entity->pending_turn_updates == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            if ((check_entity_relation(entity,
                    NODE_BODY(primary_actor_record->previous_actor_header)) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_mp(entity);
        on_actor_status_updated(entity);
        if (entity->mp_value.parts.whole == 0) {
            return;
        }

        (animation->frameTable) = hikewne_frame_set_3;
        select_sprite_entry(animation,
            hikewne_frame_set_3[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        entity->flags1C |= 0x40000;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
        actor->action_phase++;
    }
        break;
    case 2:
        if (animation->flags & 0xE000) {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
            entity->flags1C &= ~ACTOR_MP_EMPTY;
            actor->unk_8C.address = update_hikewne_actor_behavior;
        }

        return;
    }
}
