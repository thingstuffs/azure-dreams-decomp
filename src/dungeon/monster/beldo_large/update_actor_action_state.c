#include "shared/object_node.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

typedef struct S_8016CC70_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x10];
    u8 unk_AC;
} S_8016CC70_0;   /* obj in update_actor_action_state_2 */


s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);
void clear_slots_of_type(ActorRecord *owner, s8 match_type);
void select_sprite_entry(void *, s32, s32);
s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
s16 get_tile_chebyshev_distance(void *, void *);
#include "dungeon/player/object/action_state.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"

s32 generate_random_value(void);
void update_actor_status_and_mp(ActorRecord *entity);
s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
void update_multi_form_actor_movement(ActorRecord *object, ObjectPosition *update_param, SpriteFrameState *state, ActorRecord *input);
void beldo_large_action_resume_address(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);
extern u8 beldo_large_frame_set_4[];
extern u8 beldo_large_frame_set_7[];

/* Processes object action states, dispatches actor_arg actions, and updates directional tiles. */
void update_actor_action_state_2(ActorRecord *obj_arg, ObjectPosition *context_arg, SpriteFrameState *target_arg, ActorRecord *actor_arg) {
    SpriteFrameState *target;

    DungeonGlobalStatus *held_base;
    void *callback;
    TileObject *room_base;
    DungeonGlobalStatus *counter_base;
    s32 counter_value;
    s32 action_state;
    s32 obj_kind;
    s32 actor_flags;
    s8 target_room;

    action_state = obj_arg->action_phase.u;
    switch (action_state) {
    case 0:
        if (!(target_arg->flags & 0xE000)) {
            return;
        }
        obj_kind = obj_arg->unk_AC.byte;
        if (obj_kind == 0xE || (obj_kind < 0xF ? obj_kind == 0xD : obj_kind == 0xF)) {
            (target_arg->frameTable) = beldo_large_frame_set_4;
            select_sprite_entry(target_arg, beldo_large_frame_set_4[((g_game_work.view.camera_rotation.parts.viewAngle + actor_arg->facing + 0x100)
                >> 9) & 7], 0);
        }
        counter_base = &g_dungeon_status;
        counter_value = *(u16 *)&counter_base->activity_counts.parts.pending_action_count;
        counter_value--;
        counter_base->activity_counts.parts.pending_action_count = counter_value;
        obj_arg->action_phase.u++;
        return;

    case 1:
        obj_kind = obj_arg->unk_AC.byte;
        if (obj_kind == 0xE || (obj_kind < 0xF ? obj_kind == 0xD : obj_kind == 0xF)) {
            if (*(u8 **)&target_arg->frameTable != beldo_large_frame_set_4) {
                (target_arg->frameTable) = beldo_large_frame_set_4;
                select_sprite_entry(target_arg, beldo_large_frame_set_4[((g_game_work.view.camera_rotation.parts.viewAngle + actor_arg->facing + 0x100)
                    >> 9) & 7], 0);
            }
        }
        target = target_arg;
        if ((get_entity_effect_value(actor_arg, STATUS_SLEEP) << 0x10) == 0) {
            obj_kind = obj_arg->unk_AC.byte;
            if (obj_kind == 0xE || (obj_kind < 0xF ? obj_kind == 0xD : obj_kind == 0xF)) {
                (target->frameTable) = beldo_large_frame_set_7;
                select_sprite_entry(target, beldo_large_frame_set_7[((g_game_work.view.camera_rotation.parts.viewAngle + actor_arg->facing + 0x100)
                    >> 9) & 7], 0);
            }
        } else {
            held_base = &g_dungeon_status;
            if (held_base->flags & 0x1000) {
                return;
            }
            if (actor_arg->hp_delta != 0) {
                if (begin_ready_actor_directional_action(obj_arg, context_arg, target, 0) != 0) {
                    return;
                }
            }
            if (actor_arg->mp_value.parts.whole == 0) {
                if (held_base->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(obj_arg, context_arg, target, actor_arg);
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_arg) << 0x10) != 0) {
                return;
            }
            actor_flags = actor_arg->flags1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(obj_arg, context_arg, target, actor_arg);
                return;
            }
            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(obj_arg, context_arg, target, actor_arg);
                update_multi_form_actor_movement(obj_arg, context_arg, target, actor_arg);
                return;
            }
            if (actor_arg->pending_turn_updates == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_arg) << 0x10) != 0) {
                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = primary_actor_record->previous_actor_header;
                    previous_body = previous_node + 1;
                    previous_actor = previous_body;
                    if ((check_entity_relation(actor_arg, previous_actor) << 0x10) != 0) {
                        return;
                    }
                }
            }
            update_actor_status_and_mp(actor_arg);
            on_actor_status_updated(actor_arg);
            if ((get_entity_effect_value(actor_arg, STATUS_SLEEP) << 0x10) != 0) {
                room_base = &reference_tile_object;
                target_room = *(s8 *)&target->room_index;
                if (!(((target_room != room_base->room_index) || (target_room < 0))
                      && get_tile_chebyshev_distance(room_base, target) >= 2)) {
                    if ((generate_random_value() & 7) == 0) {
                        clear_slots_of_type(actor_arg, STATUS_SLEEP);
                    }
                }
            }
            if ((get_entity_effect_value(actor_arg, STATUS_SLEEP) << 0x10) != 0) {
                return;
            }
            obj_kind = obj_arg->unk_AC.byte;
            if (obj_kind == 0xE || (obj_kind < 0xF ? obj_kind == 0xD : obj_kind == 0xF)) {
                (target->frameTable) = beldo_large_frame_set_7;
                select_sprite_entry(target, beldo_large_frame_set_7[((g_game_work.view.camera_rotation.parts.viewAngle + actor_arg->facing + 0x100)
                    >> 9) & 7], 0);
            }
        }
        if (target->flags & 0x8000) {
            break;
        }
        counter_base = &g_dungeon_status;
        counter_value = *(u16 *)&counter_base->activity_counts.parts.pending_action_count;
        counter_value++;
        counter_base->activity_counts.parts.pending_action_count = counter_value;
        obj_arg->action_phase.u++;
        return;

    case 2:
        target = target_arg;
        if (!(target->flags & 0xE000)) {
            return;
        }
        counter_base = &g_dungeon_status;
        counter_value = *(u16 *)&counter_base->activity_counts.parts.pending_action_count;
        counter_value--;
        counter_base->activity_counts.parts.pending_action_count = counter_value;
        break;

    default:
        return;
    }
    callback = &beldo_large_action_resume_address;
    obj_arg->unk_8C.address = callback;
}
