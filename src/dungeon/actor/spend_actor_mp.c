#include "engine/entity.h"
#include "shared/game_state.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/dungeon_status.h"
#include "dungeon/player.h"
#include "dungeon/actor.h"




/*
 * For a positive signed kind ID, subtracts a status-adjusted reduction from the actor's 8.8 MP and
 * applies the stored cap, honoring no-drain, half-drain, and double-drain states. Keeps Kewne and
 * kind 0x39 above zero in dungeon mode one; otherwise handles exhausted MP by clearing lifted
 * links and recording the transition in the pending-action count.
 */
void spend_actor_mp(ActorRecord *entity, s32 base_reduction) {
    s32 remaining_amount;
    s32 reduction;
    s32 one;
    u8 initial_level;
    u8 level_limit;

    reduction = base_reduction;
    if ((s8)entity->species > 0) {
        remaining_amount = *(u16 *)&entity->mp_fraction;
        initial_level = entity->mp;
        if ((get_entity_effect_value(entity, STATUS_NO_MP_DRAIN) << 16) != 0) {
            reduction = 0;
        } else if (entity->status_flags & 0x100) {
            reduction = (reduction + 1) >> 1;
        }
        if ((get_entity_effect_value(entity, STATUS_MP_DRAIN) << 16) != 0) {
            reduction *= 2;
        }
        remaining_amount -= reduction;
        if (remaining_amount < 0) {
            remaining_amount = 0;
        } else if (remaining_amount > 0x10000) {
            remaining_amount = 0xFFFF;
        }
        level_limit = entity->max_mp;
        *(u16 *)&entity->mp_fraction = (u16)remaining_amount;
        if (level_limit < entity->mp) {
            entity->mp = level_limit;
            entity->mp_fraction = 0xFF;
        }
        if (entity->mp == 0) {
            s32 dungeon_mode;

            one = 1;

            dungeon_mode = GAME_STATE->dungeon_mode_state;
            if ((dungeon_mode == one) &&
                ((entity->species == MONSTER_KEWNE) ||
                 (entity->species == 0x39))) {
                entity->mp = dungeon_mode;
                return;
            }
            if (entity->flags1C & ACTOR_LIFTED) {
                clear_player_linked_action_flags();
            }
            if (initial_level != 0) {
                g_dungeon_status.activity_counts.parts.pending_action_count =
                    ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1;
            }
        }
    }
}
