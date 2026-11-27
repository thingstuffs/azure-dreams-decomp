#include "shared/actor_property_flags.h"
#include "common.h"
#include "dungeon/item/actor_target.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "dungeon/item.h"
#include "dungeon/actor/effect.h"
#include "dungeon/actor.h"



typedef struct TablePage {
    u8 pad[0x2098];
    s16 entries[1];
} TablePage;


extern u8 status_flag_blocked_action_message[];
extern u8 party_stage_advanced_message[];

/* Checks status flags, advances eligible actor state, or performs the requested action. */
u32 advance_eligible_actor_or_perform_action(ActorRecord *actor, s16 action_arg_1, s16 action_arg_2)
{
    s16 effect_result;
    s32 status_mask;
    s32 slot;
    u8 *slot_entry;
    void *message_target;
    u8 *message;
    ActorRecord *linked_object;
    s32 state_index;
    s32 state_offset;
    s32 next_state;
    TablePage *table_page;

    slot = 1;
    if (((u32)actor->flags14) & ACTOR_PARTY_MEMBER) {
        u8 *object_page;

        object_page = (u8 *)0x800E0000;
        slot_entry = *(u8 **)(object_page + 0x3D7C) + 4;
        status_mask = 0x40000;
        do {
            linked_object = ((ActorRecord *)slot_entry)->unk_AC.address;
            if ((linked_object != 0) && ((u32)(linked_object->status_flags) & status_mask)) {
                message_target = actor;
                message = status_flag_blocked_action_message;
                adjust_source_value_and_finalize(message_target, message);
                return 0;
            }
            slot--;
            slot_entry -= 4;
        } while (slot >= 0);
    } else if (((u32)actor->status_flags) & 0x40000) {
        message_target = actor;
        message = status_flag_blocked_action_message;
        adjust_source_value_and_finalize(message_target, message);
        return 0;
    }

    if (((u32)actor->flags14) & ACTOR_PARTY_MEMBER) {
        state_index = actor->ai_mode;
        if ((state_index != 4) && (actor->species != 0)) {
            actor->ai_mode = state_index + 1;
            state_index = (s16)find_linked_object_slot_index(actor);
            if (state_index >= 0) {
                table_page = (TablePage *)0x80010000;
                state_offset = state_index * 2;
                next_state = actor->ai_mode;
                table_page->entries[state_index] = next_state;
            }
            adjust_source_value_and_finalize(actor, party_stage_advanced_message);
            return 1;
        }
        try_apply_paralysis_effect(actor, action_arg_1, action_arg_2);
        return 1;
    }

    effect_result = try_apply_paralysis_effect(actor, action_arg_1, action_arg_2);
    return (u32)~effect_result >> 31;
}
