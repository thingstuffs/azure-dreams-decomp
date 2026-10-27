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

extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
#include "dungeon/player/object/action_state.h"
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void update_directional_sprite_state_and_signals(void *, void *, SpriteFrameState *, void *);

extern u8 hikewne_frame_set_2[];
extern u8 hikewne_frame_set_3[];

/* Advance actor states, select directional animations, and process entity actions. */
void advance_actor_states_and_process_actions(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *animation, ActorRecord *entity) {
    s32 state;

    state = ((Rec_func_8017360C_arg0 *)actor)->unk_9B;
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
        ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
        return;
    }
    case 1:
    {
        u32 entity_flags;

        if (entity->mp != 0) {

            (animation->frameTable) = hikewne_frame_set_3;
            select_sprite_entry(animation,
                hikewne_frame_set_3[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            entity->flags1C |= 0x40000;
            g_dungeon_status.activity_counts.parts.pending_action_count++;
            ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
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
            stored_value = ((Rec_func_8017360C_arg0 *)actor)->unk_92;
            pending_decrement = ((Rec_func_8017360C_arg0 *)actor)->unk_A2;
            ((Rec_func_8017360C_arg0 *)actor)->unk_A2 = 0;
            ((Rec_func_8017360C_arg0 *)actor)->unk_9E = 0;
            ((Rec_func_8017360C_arg0 *)actor)->unk_92 = stored_value - pending_decrement;
            update_directional_sprite_state_and_signals(actor, context, animation, entity);
            return;
        }

        if (entity->pending_turn_updates == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            if ((check_entity_relation(entity,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_mp(entity);
        on_actor_status_updated(entity);
        if (entity->mp == 0) {
            return;
        }

        (animation->frameTable) = hikewne_frame_set_3;
        select_sprite_entry(animation,
            hikewne_frame_set_3[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        entity->flags1C |= 0x40000;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
        ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
    }
        break;
    case 2:
        if (animation->flags & 0xE000) {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
            entity->flags1C &= ~ACTOR_MP_EMPTY;
            ((Rec_func_8017360C_arg0 *)actor)->unk_8C.as_pv = update_actor_behavior_animation_and_facing;
        }

        return;
    }
}
