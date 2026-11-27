#include "dungeon/system.h"
#include "dungeon/actor/status.h"
#include "engine/entity/effect_slots.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/system/random.h"
#include "dungeon/actor.h"
#include "dungeon/actor/state.h"
#include "dungeon/item.h"
#include "dungeon/item/message.h"

extern s32 brainwash_period[];
extern s32 brainwash_protected_message[];
extern s32 brainwash_player_side_prefix_text[];
extern s32 brainwash_applied_message[];
extern s32 brainwash_blocked_message[];

/* Toggle the 0xB/0xC status pair between attacker and target: roll the attacker's 0x3 chance plus its 0x11 bonus against 0x30, apply or clear the status on the target, and report whether the attempt did not fail. */
u32 try_toggle_brainwash_status(ActorRecord *attacker, ActorRecord *target) {
    s32 roll;
    s16 status;
    s32 shifted;
    s32 chance;
    s32 base_chance;

    status = -1;
    if (has_brainwash_protection(target) != 0) {
        if (target->flags14 & ACTOR_PARTY_MEMBER) {
            adjust_source_value_and_finalize(target, &brainwash_protected_message);
        }
        return 0;
    }
    roll = generate_random_value() & 0xFFFF;
    base_chance = attacker->level >> 2;
    if (attacker->luck != 0) {
        chance = roll % attacker->luck + base_chance;
    } else {
        chance = base_chance;
    }
    if (chance >= 0x30) {
        if (attacker->flags1C & 0x2000) {
            if (!(target->flags1C & ACTOR_PLAYER_SIDE)) {
                if ((get_entity_effect_value(target, STATUS_BRAINWASH) << 0x10) != 0) {
                    clear_slots_of_type(target, STATUS_BRAINWASH);
                    status = 0;
                } else {
                    status = set_or_clear_actor_status_slot(target, STATUS_PLAYER_SIDE, 0x10);
                    if ((status << 0x10) < 0) {
                        goto block_error;
                    }
                    {
                        void *session = get_unused_text_buffer();
                        void *saved = session;
                        session = expand_text_control_codes(&brainwash_player_side_prefix_text, session);
                        clear_byte_and_advance(expand_text_control_codes(&brainwash_period, append_entity_display_text(target, session)));
                        display_text_with_fullwidth_adjustment(saved);
                    }
                }
            }
        } else if (target->flags1C & ACTOR_PLAYER_SIDE) {
            if ((get_entity_effect_value(target, STATUS_PLAYER_SIDE) << 0x10) != 0) {
                clear_slots_of_type(target, STATUS_PLAYER_SIDE);
                status = 0;
            } else {
                status = set_or_clear_actor_status_slot(target, STATUS_BRAINWASH, 0x10);
                if ((status << 0x10) < 0) {
                    goto block_error;
                }
                adjust_source_value_and_finalize(target, &brainwash_applied_message);
            }
        }
    }
    shifted = status << 0x10;
    if (shifted < 0) {
block_error:
        if (target->flags14 & ACTOR_PARTY_MEMBER) {
            adjust_source_value_and_finalize(target, &brainwash_blocked_message);
        }
        shifted = status << 0x10;
    }
    shifted = status << 0x10;
    return (u32) ~(shifted >> 0x10) >> 0x1F;
}
