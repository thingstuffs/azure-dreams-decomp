#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/actor.h"
#include "shared/dungeon_status.h"
#include "dungeon/effect.h"
#include "dungeon.h"
#include "dungeon/actor/motion.h"
#include "engine/entity.h"
#include "dungeon/player/object.h"

#include "dungeon/item/find_active_rect_containing_point_api.h"
extern void * find_compatible_adjacent_actor(void *entity, u16 x, u16 y);
#include "dungeon/player/object/action_state.h"

extern void update_actor_transform_from_parent_callback(void *, s32, void *, void *);

/* Dispatch an target action and update the actor and destination state. */
void dispatch_target_action(ActorRecord *actor, s32 action_context, SpriteFrameState *destination, ActorRecord *target)
{
    DungeonGlobalStatus *flags = &g_dungeon_status;
    ActorRecord *idle_actor = actor;


    if (!(flags->flags & 0x1000)) {
        if (target->mp_value.parts.whole == 0) {
            actor->unk_AC.bytes[1] = 0;
            begin_actor_flagged_action(idle_actor, action_context, destination, target);
            return;
        }

        if ((get_entity_effect_value(target, STATUS_SLEEP) << 16) == 0) {
            if (!(flags->flags & 0x2000)) {
                if (target->flags1C & 0x100) {
                    begin_pushed_actor_move(actor, action_context, destination, target);
                    return;
                }

                if (actor->action_id != 0xE) {
                    actor->action_id = 0xE;
                }
                actor->action_state_flags &= 0xFFF3;

                if ((target->hp_delta != 0) &&
                    (begin_ready_actor_directional_action(actor, action_context, destination, 0) != 0)) {
                    return;
                }

                if (target->flags1C & 0x80000) {
                    begin_actor_move_to_target_facing(actor, action_context, destination, target);
                    update_actor_transform_from_parent_callback(actor, action_context, destination, target);
                    return;
                }

                if ((can_entity_gain_level(target) << 16) != 0) {
                    actor->unk_AC.bytes[1] = 0;
                    begin_actor_flagged_action(actor, action_context, destination, target);
                    return;
                }
            }

            destination->room_index = find_active_rect_containing_point(destination->tile_x,
                                                     destination->tile_y);
            if (target->pending_turn_updates <= 0) {
                return;
            }
            if (g_dungeon_status.flags & 0x1000) {
                return;
            }
            if ((has_pending_actor_or_turn_action(0) << 16) != 0) {
                return;
            }
            if (find_compatible_adjacent_actor(target, destination->tile_x,
                              destination->tile_y) != 0) {
                actor->unk_AC.bytes[1] = 0;
                begin_actor_flagged_action(actor, action_context, destination, target);
                return;
            }
        } else {
            actor->unk_AC.bytes[1] = 0;
            begin_actor_flagged_action(actor, action_context, destination, target);
            return;
        }
        target->pending_turn_updates = 0;
    }
}
