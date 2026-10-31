#include "shared/object_node.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/monster/kraken.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_trail_views.h"

typedef struct S_8017352C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    u8 * unk_A4;
    u16 unk_A8;
} S_8017352C_0;   /* arg0 in update_actor_animation_timers_and_transitions */

   /* arg2 in update_actor_animation_timers_and_transitions */

   /* counter_base in update_actor_animation_timers_and_transitions */

typedef struct S_8017352C_5 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_8017352C_5;   /* part20 in update_actor_animation_timers_and_transitions */

   /* part28 in update_actor_animation_timers_and_transitions */


extern s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);
extern void clear_slots_of_type(ActorRecord *owner, s8 match_type);
extern void select_sprite_entry(void *, u8, s32);
extern s32 rand(void);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern s32 get_tile_chebyshev_distance(void *, void *);
#include "dungeon/player/object/action_state.h"
#include "dungeon/actor.h"
extern s32 generate_random_value(void);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern void begin_pushed_actor_move(void *state_in, void *unused, void *position_in, void *actor_in);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void func_80173D10(void *, void *, void *, void *);

extern u8 kraken_action_resume_address[];
extern u8 kraken_frame_set_3[];
extern u8 kraken_frame_set_2[];

/* Updates the actor's animation state, timers, and action transitions. */
void update_actor_animation_timers_and_transitions(ActorRecord *entity, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    S_8017352C_5 *body_part;
    SpriteFrameState *part_anim;
    DungeonGlobalStatus *global_base;
    u8 *body;
    DungeonGlobalStatus *state_zero_counter_base;
    DungeonGlobalStatus *animate_counter_base;
    TrailHeightView *state_two_counter_base;
    s32 actor_flags;
    s32 state;
    u16 timer;
    u16 count;

    body = ((S_8017352C_0 *)entity)->unk_A4;
    state = entity->action_phase.u;
    body_part = (S_8017352C_5 *)(body + 0x20);
    part_anim = body + 0x28;
    switch (state) {
    case 0:
        entity->unk_90.value += 0x80000;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        (sprite->frameTable) = kraken_frame_set_2;
        select_sprite_entry(sprite,
            kraken_frame_set_2[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        state_zero_counter_base = &g_dungeon_status;
        entity->action_timer.u = 0;
        count = ((u16)state_zero_counter_base->activity_counts.parts.pending_action_count) - 1;
        state_zero_counter_base->activity_counts.parts.pending_action_count = count;
        entity->action_phase.u++;
        return;
    case 1:
        if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
            global_base = &g_dungeon_status;
            if (global_base->flags & 0x1000) {
                return;
            }
            if (actor->hp_delta != 0) {
                if (begin_ready_actor_directional_action(entity, motion, sprite, 0) != 0) {
                    return;
                }
            }
            if (actor->mp_value.parts.whole == 0) {
                if (global_base->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(entity, motion, sprite, actor);
                return;
            }
            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                return;
            }
            actor_flags = actor->flags1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(entity, motion, sprite, actor);
                return;
            }
            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(entity, motion, sprite, actor);
                entity->unk_A8.u = 0;
                func_80173D10(entity, motion, sprite, actor);
                return;
            }

            timer = entity->action_timer.u - 1;
            entity->action_timer.u = timer;
            if ((timer << 16) <= 0) {
                body_part->unk_04 &= 0x7FFF;
                select_sprite_entry(part_anim, 0x27, 0);
                entity->action_timer.u = (rand() & 0xF) + 0x20;
            }
            if (part_anim->flags & 0x6000) {
                body_part->unk_04 |= 0x8000;
            }
            if (actor->pending_turn_updates == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                ActorRecord *owner = primary_actor_record;

                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = owner->previous_actor_header;
                    previous_body = previous_node + 1;
                    previous_actor = previous_body;
                    if ((check_entity_relation(actor,
                            previous_actor) << 16) != 0) {
                        return;
                    }
                }
            }
            update_actor_status_and_mp(actor);
            on_actor_status_updated(actor);
            if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
                TileObject *origin = &reference_tile_object;
                s8 tile = *(s8 *)&sprite->room_index;

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
            (sprite->frameTable) = kraken_frame_set_3;
            select_sprite_entry(sprite,
                kraken_frame_set_3[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            actor->flags1C |= 0x40000;
            body_part->unk_04 |= 0x8000;
            if (!(sprite->flags & 0x8000)) {
                animate_counter_base = (u8 *)3;
                entity->action_timer.u = (s32)animate_counter_base;
                entity->action_state_flags &= 0xBFFF;
                animate_counter_base = (u8 *)&g_dungeon_status.turn_scale;
                count = *(u16 *)&animate_counter_base->activity_counts.parts.pending_action_count + 1;
                animate_counter_base->activity_counts.parts.pending_action_count = count;
                entity->action_phase.u++;
                return;
            }
            break;
        } else {
            (sprite->frameTable) = kraken_frame_set_3;
            select_sprite_entry(sprite,
                kraken_frame_set_3[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            actor->flags1C |= 0x40000;
            body_part->unk_04 |= 0x8000;
            if (!(sprite->flags & 0x8000)) {
                animate_counter_base = (u8 *)3;
                entity->action_timer.u = (s32)animate_counter_base;
                entity->action_state_flags &= 0xBFFF;
                animate_counter_base = (u8 *)&g_dungeon_status.turn_scale;
                count = *(u16 *)&animate_counter_base->activity_counts.parts.pending_action_count + 1;
                animate_counter_base->activity_counts.parts.pending_action_count = count;
                entity->action_phase.u++;
                return;
            }
            break;
        }
    case 2:
        timer = entity->action_timer.u - 1;
        entity->action_timer.u = timer;
        if ((timer << 16) <= 0) {
            entity->action_state_flags |= 0x4000;
            motion->velocity_z = 0xFFF80000;
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        state_two_counter_base = (TrailHeightView *)&g_dungeon_status.turn_scale;
        motion->velocity_z = 0;
        entity->unk_A8.u = 0;
        state_two_counter_base->unk_0A--;

        break;
    default:
        return;
    }
    actor->flags1C &= -0x201;
    entity->unk_8C.address = kraken_action_resume_address;
}
