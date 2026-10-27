#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/actor.h"
#include "shared/dungeon_status.h"
#include "dungeon/effect.h"

extern s32 get_entity_effect_value(void *, s32);
extern s8 find_active_rect_containing_point(u8, u8);
extern void * find_monster_neighbor_candidate(void *entity, u16 x, u16 y);
extern s32 can_entity_gain_level(void *);
#include "dungeon/player/object/action_state.h"
extern void begin_pushed_actor_move(void *,void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, u8 *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);

extern void update_actor_transform_from_parent_callback(void *, s32, void *, void *);

/* Dispatch an target action and update the actor and destination state. */
void dispatch_target_action(u8 *actor, s32 action_context, u8 *destination, u8 *target)
{
    DungeonGlobalStatus *flags = &g_dungeon_status;
    u8 *idle_actor = actor;


    if (!(flags->flags & 0x1000)) {
        if (*(u8 *)(target + 0x25) == 0) {
            *(s8 *)(actor + 0xAD) = 0;
            begin_actor_flagged_action(idle_actor, action_context, destination, target);
            return;
        }

        if ((get_entity_effect_value(target, STATUS_SLEEP) << 16) == 0) {
            if (!(flags->flags & 0x2000)) {
                if (*(s32 *)(target + 0x1C) & 0x100) {
                    begin_pushed_actor_move(actor, action_context, destination, target);
                    return;
                }

                if (*(u8 *)(actor + 0x9A) != 0xE) {
                    *(u8 *)(actor + 0x9A) = 0xE;
                }
                *(u16 *)(actor + 0x98) &= 0xFFF3;

                if ((*(s16 *)(target + 0x64) != 0) &&
                    (begin_ready_actor_directional_action(actor, action_context, destination, 0) != 0)) {
                    return;
                }

                if (*(s32 *)(target + 0x1C) & 0x80000) {
                    begin_actor_move_to_target_facing(actor, action_context, destination, target);
                    update_actor_transform_from_parent_callback(actor, action_context, destination, target);
                    return;
                }

                if ((can_entity_gain_level(target) << 16) != 0) {
                    *(s8 *)(actor + 0xAD) = 0;
                    begin_actor_flagged_action(actor, action_context, destination, target);
                    return;
                }
            }

            *(s8 *)(destination + 0x26) = find_active_rect_containing_point(*(u8 *)(destination + 0x24),
                                                     *(u8 *)(destination + 0x25));
            if (*(s8 *)(target + 0x6D) <= 0) {
                return;
            }
            if (g_dungeon_status.flags & 0x1000) {
                return;
            }
            if ((has_pending_actor_or_turn_action(0) << 16) != 0) {
                return;
            }
            if (find_monster_neighbor_candidate(target, *(u8 *)(destination + 0x24),
                              *(u8 *)(destination + 0x25)) == 0) {
                goto clear;
            }
        } else {
            *(s8 *)(actor + 0xAD) = 0;
            begin_actor_flagged_action(actor, action_context, destination, target);
            return;
        }

fail:
        *(s8 *)(actor + 0xAD) = 0;
        begin_actor_flagged_action(actor, action_context, destination, target);
        return;

clear:
        *(s8 *)(target + 0x6D) = 0;
    }

    return;
}
