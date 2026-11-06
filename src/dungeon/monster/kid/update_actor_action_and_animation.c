#include "shared/object_node.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/system/random.h"
#include "dungeon/monster/kid.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon.h"
#include "dungeon/actor/motion.h"
#include "dungeon/level.h"

extern s32 get_entity_effect_value(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern void select_sprite_entry(void *, u8, s32);
extern s32 get_tile_chebyshev_distance(void *, void *);
#include "dungeon/player/object/action_state.h"
#include "dungeon/actor.h"
#include "dungeon/monster/kid_frames.h"
extern void update_actor_status_and_mp(void *);
extern void func_80174218(void *, void *, void *, void *);

extern u8 kid_action_resume_address[];

/* Updates an actor's action state and animation before restoring its default callback. */
void update_actor_action_and_animation(ActorRecord *controller_in, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 actor_flags;
    u16 ticks_left;
    s32 state;

    state = controller_in->action_phase.u;
    switch (state) {
    case 0:
        controller_in->unk_90.value += 0x100000;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        sprite->frameTable = kid_alt_spawn_direction_frames;
        actor = (ActorRecord *)((u8 *)actor + 0x2A);
        select_sprite_entry(sprite,
            kid_alt_spawn_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)actor + 0x100) >> 9) & 7],
            0);
        {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        controller_in->action_phase.u++;
        return;

    case 1:
        if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) == 0) {
            sprite->frameTable = kid_frame_set_4;
            select_sprite_entry(sprite,
                kid_frame_set_4[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            actor_flags = actor->flags1C | 0x40000;
            actor->flags1C = actor_flags;
            if (sprite->flags & 0x8000) {
                actor->flags1C = actor_flags & ~0x200;
                controller_in = (ActorRecord *)((u8 *)controller_in + 0x8C);
                *(void **)controller_in = kid_action_resume_address;
                return;
            }
        } else {
            if (g_dungeon_status.flags & 0x1000) {
                return;
            }
            if (actor->hp_delta != 0) {
                if (begin_ready_actor_directional_action(controller_in, motion, sprite, 0) != 0) {
                    return;
                }
            }
            if (actor->mp_value.parts.whole == 0) {
                if (g_dungeon_status.flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(controller_in, motion, sprite, actor);
                return;
            }
            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                return;
            }
            actor_flags = actor->flags1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(controller_in, motion, sprite, actor);
                return;
            }
            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(controller_in, motion, sprite, actor);
                controller_in->unk_A8.s = 0;
                func_80174218(controller_in, motion, sprite, actor);
                return;
            }
            if (actor->pending_turn_updates == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                ActorRecord *owner = primary_actor_record;

                {
                    void *current_body;
                    ActorRecord *current_actor;
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    current_body = actor;
                    current_actor = current_body;
                    previous_node = owner->previous_actor_header;
                    previous_body = previous_node + 1;
                    previous_actor = previous_body;
                    if ((check_entity_relation(current_actor,
                            previous_actor) << 16) != 0) {
                        return;
                    }
                }
            }
            update_actor_status_and_mp(actor);
            on_actor_status_updated(actor);
            if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
                TileObject *origin = &reference_tile_object;
                s8 tile = ((s8)(sprite->room_index));

                if (((tile == origin->room_index) && (tile >= 0)) ||
                    ((s16)get_tile_chebyshev_distance(origin, sprite) < 2)) {
                    if (!(generate_random_value() & 7)) {
                        clear_slots_of_type(actor, STATUS_SLEEP);
                    }
                }
            }
            if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
                return;
            }
            sprite->frameTable = kid_frame_set_4;
            select_sprite_entry(sprite,
                kid_frame_set_4[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            actor_flags = actor->flags1C | 0x40000;
            actor->flags1C = actor_flags;
            if (sprite->flags & 0x8000) {
                actor->flags1C = actor_flags & ~0x200;
                controller_in = (ActorRecord *)((u8 *)controller_in + 0x8C);
                *(void **)controller_in = kid_action_resume_address;
                return;
            }
        }
        controller_in->action_timer.u = 3;
        controller_in->action_state_flags &= 0xBFFF;
        {

            g_dungeon_status.activity_counts.parts.pending_action_count++;
        }
        controller_in->action_phase.u++;
        return;

    case 2:
        ticks_left = controller_in->action_timer.u - 1;
        controller_in->action_timer.u = ticks_left;
        if ((ticks_left << 16) <= 0) {
            controller_in->action_state_flags |= 0x4000;
            motion->velocity_z = 0xFFEC0000;
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        controller_in->unk_A8.s = 0;
        sprite->frameTable = kid_direction_frames;
        select_sprite_entry(sprite,
            kid_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        actor->flags1C &= ~ACTOR_ASLEEP;

        controller_in = (ActorRecord *)((u8 *)controller_in + 0x8C);
        *(void **)controller_in = kid_action_resume_address;

        return;
    }
}
