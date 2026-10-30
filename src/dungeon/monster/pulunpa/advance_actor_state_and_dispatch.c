#include "shared/object_node.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"

typedef struct S_801733F0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0xB];
    u8 unk_A7;
} S_801733F0_0;   /* arg0 in advance_actor_state_and_dispatch */

extern void select_sprite_entry(void *, u8, s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
#include "dungeon/player/object/action_state.h"
extern void update_actor_status_and_mp(ActorRecord *entity);
extern void begin_pushed_actor_move(void *state_in, void *unused, void *position_in, void *actor_in);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, u8 *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void update_object_or_select_directional_data(void *, void *, void *, void *);

extern u8 pulunpa_action_resume_address[];
extern u8 pulunpa_variant_action_address[];
#include "dungeon/monster/pulunpa.h"
#include "dungeon/actor.h"
extern u8 D_80176308[];
extern u8 pulunpa_frame_set_3[];
extern u8 D_80176368[];

/* Advance the actor state, select directional sprite data, and dispatch entity actions. */
void advance_actor_state_and_dispatch(S_801733F0_0 *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity)
{
    u8 state;

    state = actor->unk_9B;
    switch (state) {
    case 0:
    {

        if ((sprite->flags & 0xE000) == 0) {
            return;
        }

        g_dungeon_status.activity_counts.parts.pending_action_count--;
        if (actor->unk_A7 != 0) {
            sprite->frameTable = pulunpa_frame_set_3;
        } else {
            sprite->frameTable = pulunpa_direction_frames;
        }
        select_sprite_entry(
            sprite,
            ((u8 *)sprite->frameTable)[
                ((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        goto increment_state;
    }

    case 1:
        if (entity->mp_value.parts.whole != 0) {
            if (actor->unk_A7 != 0) {
                sprite->frameTable = D_80176368;
            } else {
                sprite->frameTable = D_80176308;
            }
        } else {
            if (g_dungeon_status.flags & 0x1000) {
                return;
            }

            if ((entity->hp_delta != 0) &&
                begin_ready_actor_directional_action(actor, context, sprite, 0)) {
                return;
            }

            if ((s16)has_pending_actor_or_turn_action(entity) != 0) {
                return;
            }

            if (((u32)entity->flags1C) & ACTOR_PUSH_PENDING) {
                begin_pushed_actor_move(actor, context, sprite, entity);
                return;
            }

            if (((u32)entity->flags1C) & ACTOR_LIFTED) {
                begin_actor_move_to_target_facing(actor, context, sprite, entity);
                update_object_or_select_directional_data(actor, context, sprite, entity);
                return;
            }

            if (entity->pending_turn_updates == 0) {
                return;
            }

            if ((s16)has_pending_actor_or_turn_action(entity) != 0) {
                ActorRecord *owner;

                owner = primary_actor_record;
                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = owner->previous_actor_header;
                    previous_body = previous_node + 1;
                    previous_actor = previous_body;
                    if ((s16)check_entity_relation(
                            entity, previous_actor) != 0) {
                        return;
                    }
                }
            }

            update_actor_status_and_mp(entity);
            on_actor_status_updated(entity);
            if (entity->mp_value.parts.whole == 0) {
                return;
            }

            if (actor->unk_A7 != 0) {
                sprite->frameTable = D_80176368;
            } else {
                sprite->frameTable = D_80176308;
            }
        }
        select_sprite_entry(
            sprite,
            ((u8 *)sprite->frameTable)[
                ((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        {

            g_dungeon_status.activity_counts.parts.pending_action_count++;
        }

increment_state:
        actor->unk_9B++;
        return;

    case 2:
    {

        if ((sprite->flags & 0xE000) == 0) {
            return;
        }

        g_dungeon_status.activity_counts.parts.pending_action_count--;
        entity->flags1C &= ~ACTOR_ASLEEP;
        if (actor->unk_A7 != 0) {
            actor->unk_8C = pulunpa_variant_action_address;
        } else {
            actor->unk_8C = pulunpa_action_resume_address;
        }
        return;
    }
    }
}
