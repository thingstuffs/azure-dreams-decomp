#include "shared/object_node.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"

extern void select_sprite_entry(void *, u8, s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
#include "dungeon/player/object/action_state.h"
extern void update_actor_status_and_mp(ActorRecord *entity);
extern void begin_pushed_actor_move(void *state_in, void *unused, void *position_in, void *actor_in);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, u8 *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void update_object_or_select_directional_data(void *, ObjectPosition *, void *, ActorRecord *);

extern u8 pulunpa_action_resume_address[];
extern u8 pulunpa_variant_action_address[];
#include "dungeon/monster/pulunpa.h"
#include "dungeon/actor.h"
extern u8 D_80176308[];
extern u8 pulunpa_frame_set_3[];
extern u8 D_80176368[];

/* Advance the actor state, select directional sprite data, and dispatch entity actions. */
void advance_actor_state_and_dispatch(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor)
{
    u8 state;

    state = body->action_phase.u;
    switch (state) {
    case 0:
    {

        if ((sprite->flags & 0xE000) == 0) {
            return;
        }

        g_dungeon_status.activity_counts.parts.pending_action_count--;
        if (body->unk_A4.bytes[3] != 0) {
            sprite->frameTable = pulunpa_frame_set_3;
        } else {
            sprite->frameTable = pulunpa_direction_frames;
        }
        select_sprite_entry(
            sprite,
            ((u8 *)sprite->frameTable)[
                ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        goto increment_state;
    }

    case 1:
        if (actor->mp_value.parts.whole != 0) {
            if (body->unk_A4.bytes[3] != 0) {
                sprite->frameTable = D_80176368;
            } else {
                sprite->frameTable = D_80176308;
            }
        } else {
            if (g_dungeon_status.flags & 0x1000) {
                return;
            }

            if ((actor->hp_delta != 0) &&
                begin_ready_actor_directional_action(body, position, sprite, 0)) {
                return;
            }

            if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
                return;
            }

            if (((u32)actor->flags1C) & ACTOR_PUSH_PENDING) {
                begin_pushed_actor_move(body, position, sprite, actor);
                return;
            }

            if (((u32)actor->flags1C) & ACTOR_LIFTED) {
                begin_actor_move_to_target_facing(body, position, sprite, actor);
                update_object_or_select_directional_data(body, position, sprite, actor);
                return;
            }

            if (actor->pending_turn_updates == 0) {
                return;
            }

            if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
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
                            actor, previous_actor) != 0) {
                        return;
                    }
                }
            }

            update_actor_status_and_mp(actor);
            on_actor_status_updated(actor);
            if (actor->mp_value.parts.whole == 0) {
                return;
            }

            if (body->unk_A4.bytes[3] != 0) {
                sprite->frameTable = D_80176368;
            } else {
                sprite->frameTable = D_80176308;
            }
        }
        select_sprite_entry(
            sprite,
            ((u8 *)sprite->frameTable)[
                ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        {

            g_dungeon_status.activity_counts.parts.pending_action_count++;
        }

increment_state:
        body->action_phase.u++;
        return;

    case 2:
    {

        if ((sprite->flags & 0xE000) == 0) {
            return;
        }

        g_dungeon_status.activity_counts.parts.pending_action_count--;
        actor->flags1C &= ~ACTOR_ASLEEP;
        if (body->unk_A4.bytes[3] != 0) {
            body->unk_8C.address = pulunpa_variant_action_address;
        } else {
            body->unk_8C.address = pulunpa_action_resume_address;
        }
        return;
    }
    }
}
