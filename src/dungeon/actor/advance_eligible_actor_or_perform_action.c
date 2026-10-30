#include "shared/actor_property_flags.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "dungeon/item.h"
#include "dungeon/actor/effect.h"

typedef struct S_800C8150_1 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800C8150_1;   /* entry in advance_eligible_actor_or_perform_action */

typedef struct S_800C8150_2 {
    u8 pad_00[0x54];
    u32 unk_54;
} S_800C8150_2;   /* object in advance_eligible_actor_or_perform_action */

typedef struct TablePage {
    u8 pad[0x2098];
    s16 entries[1];
} TablePage;

extern s16 find_entity_slot_by_field_ac(void *);

extern u8 D_800E18F5[];
extern u8 D_800E195C[];

/* Checks status flags, advances eligible actor state, or performs the requested action. */
u32 advance_eligible_actor_or_perform_action(EntityRec *actor, s16 action_arg_1, s16 action_arg_2)
{
    s16 effect_result;
    s32 status_mask;
    s32 slot;
    u8 *slot_entry;
    void *message_target;
    u8 *message;
    S_800C8150_2 *linked_object;
    s32 state_index;
    s32 raw_state_index;
    s32 state_offset;
    s32 next_state;
    s32 shifted_index;
    TablePage *table_page;

    slot = 1;
    if (((u32)actor->flags14) & ACTOR_PARTY_MEMBER) {
        u8 *object_page;

        object_page = (u8 *)0x800E0000;
        slot_entry = *(u8 **)(object_page + 0x3D7C) + 4;
        status_mask = 0x40000;
        do {
            linked_object = ((S_800C8150_1 *)slot_entry)->unk_AC;
            if ((linked_object != 0) && (linked_object->unk_54 & status_mask)) {
                message_target = actor;
                message = D_800E18F5;
                adjust_source_value_and_finalize(message_target, message);
                return 0;
            }
            slot--;
            slot_entry -= 4;
        } while (slot >= 0);
    } else if (((u32)actor->unk_54) & 0x40000) {
        message_target = actor;
        message = D_800E18F5;
        adjust_source_value_and_finalize(message_target, message);
        return 0;
    }

    if (((u32)actor->flags14) & ACTOR_PARTY_MEMBER) {
        state_index = (*(u8 *)((u8 *)&actor->unk_10 + 2));
        if ((state_index != 4) && ((*(u8 *)((u8 *)&actor->unk_10 + 3)) != 0)) {
            (*(u8 *)((u8 *)&actor->unk_10 + 2)) = state_index + 1;
            raw_state_index = find_entity_slot_by_field_ac(actor);
            shifted_index = raw_state_index << 16;
            state_index = shifted_index >> 16;
            if (state_index >= 0) {
                table_page = (TablePage *)0x80010000;
                state_offset = state_index * 2;
                next_state = (*(u8 *)((u8 *)&actor->unk_10 + 2));
                table_page->entries[state_index] = next_state;
            }
            adjust_source_value_and_finalize(actor, D_800E195C);
            return 1;
        }
        try_apply_effect_four_by_chance(actor, action_arg_1, action_arg_2);
        return 1;
    }

    effect_result = try_apply_effect_four_by_chance(actor, action_arg_1, action_arg_2);
    return (u32)~effect_result >> 31;
}
