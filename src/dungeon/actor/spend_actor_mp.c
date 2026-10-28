#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/dungeon_status.h"
#include "dungeon/player.h"

typedef struct S_800AD594_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AD594_1;   /* counterBase in spend_actor_mp */


extern s32 get_entity_effect_value(void *, s32);

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
        remaining_amount = entity->mp_value.whole;
        initial_level = entity->mp_value.parts.whole;
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
        entity->mp_value.whole = (u16)remaining_amount;
        if (level_limit < entity->mp_value.parts.whole) {
            entity->mp_value.parts.whole = level_limit;
            entity->mp_value.parts.fraction = 0xFF;
        }
        if (entity->mp_value.parts.whole == 0) {
            s32 dungeon_mode;

            one = 1;

            dungeon_mode = *(s32 *)0x80012090;
            if ((dungeon_mode == one) &&
                ((entity->species == MONSTER_KEWNE) ||
                 (entity->species == 0x39))) {
                entity->mp_value.parts.whole = dungeon_mode;
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
