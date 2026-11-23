#include "engine/entity/effect_slots.h"
#include "shared/game_state.h"
#include "dungeon/system.h"
#include "dungeon/system/random_range.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/system/random.h"
#include "dungeon/actor/status.h"
#include "dungeon/effect.h"
#include "dungeon/actor.h"
#include "dungeon/actor/effect.h"
#include "dungeon/effect/state.h"
#include "dungeon/item/message.h"
#include "dungeon/item.h"

extern s16 current_dungeon_floor;
extern u8 D_800892C4[];
extern u8 D_800892C8[];
extern u8 D_800E0BC7[];
extern u8 D_800E0BDC[];
extern u8 D_800E0BF3[];
extern u8 D_800E0C09[];
extern u8 D_800E0C1D[];
extern volatile u8 *dungeon_actor_ring_anchor[];
/* Applies secondary spell and event-record effects, updating actor status, values, and displayed messages. */
s32 update_attached_effect_state(s16 tile_index, ActorRecord *target, ActorRecord *caster)
{
    s16 blocked;
    s32 total;
    s32 flag;
    u8 *saved;
    u8 *text;
    s16 code;
    s32 delta;
    s16 amount;
    s16 range;
    DungeonItemEntry *equipped_item;
    s16 value;
    code = resolve_alternate_spell_id(tile_index);
    total = target->hp + target->hp_delta;
    flag = total < 1;
    blocked = flag;
    if (code != 0) {
        switch (code) {
        case 0x10:
        case 0x13:
        {
            if (!blocked) {
                value = generate_random_value();
                range = (dungeon_actor_ring_anchor[0][0xA9] >> 2) + 0x10;
                if (roll_blind_effect(target, dungeon_actor_ring_anchor[0][0xA9] + 0x80, range + (value & 3)) != 0) {
                    saved = get_unused_text_buffer();
                    text = expand_text_control_codes(D_800E0BC7, saved);
                    text = append_entity_display_text(target, text);
                    text = expand_text_control_codes(D_800892C4, text);
                    text = clear_byte_and_advance(text);
                    display_text_with_fullwidth_adjustment(saved);
                }
            }
            break;
        }
        case 0x12:
        case 0x15:
        {
            if (!(blocked || (target->flags1C & ACTOR_PARALYZED))) {
                value = generate_random_value();
                range = (dungeon_actor_ring_anchor[0][0xA9] >> 2) + 2;
                if (roll_paralysis_effect(target, dungeon_actor_ring_anchor[0][0xA9] + 0x80, range + (value & 3)) != 0) {
                    saved = get_unused_text_buffer();
                    text = expand_text_control_codes(D_800E0BDC, saved);
                    text = append_entity_display_text(target, text);
                    text = expand_text_control_codes(D_800892C8, text);
                    text = clear_byte_and_advance(text);
                    display_text_with_fullwidth_adjustment(saved);
                }
            }
            break;
        }
        }
    }

    equipped_item = caster->weapon;

    if (equipped_item == 0) {
        return 0;
    }
    if (equipped_item->kind != 0x10) {
        return 0;
    }
    value = equipped_item->unk_00;
    switch (value) {
    case 3:
    {
        delta = -(target->hp_delta >> 3);

        amount = delta;
        if (amount == 0) {
            return 0;
        }
        caster->hp_delta += delta;
        create_actor_value_popup(0x10, caster, amount, 1);
        return 0;
    }
    case 4:
    {
        if (blocked || (target->flags1C & ACTOR_PARALYZED)) {
            return 0;
        }
        if (roll_paralysis_effect(target, 8, 8) == 0) {
            return 0;
        }
        play_sound_if_enabled(0x700);
        saved = get_unused_text_buffer();
        text = expand_text_control_codes(D_800E0BF3, saved);
        text = append_entity_display_text(target, text);
        text = expand_text_control_codes(D_800892C4, text);
        text = clear_byte_and_advance(text);
        display_text_with_fullwidth_adjustment(saved);
        return 0;
    }
    case 5:
    {
        s32 low; /* MATCH: merge random-range bounds in the retail argument registers. */
        s32 high; /* MATCH: preserve the range-bound delay slots. */
        if (!blocked) {
            return 0;
        }
        saved = &target->carried_item.unk_00;
        if (saved[1] != 0) {
            return 0;
        }
        if ((generate_random_value() & 3) != 0) {
            return 0;
        }
        saved[1] = 0xE;
        if ((GAME_STATE->dungeon_mode_state != 2) && (current_dungeon_floor < 0xC)) {
            low = 0x10;
            high = 0x18;
            saved[0] = 1;
            saved[2] = random_dungeon_range_16(low, high);
            saved[3] = 0;
        }
        else if ((GAME_STATE->dungeon_mode_state != 2) && (current_dungeon_floor < 0x16)) {
            low = 0x50;
            high = 0x78;
            saved[0] = 2;
            saved[2] = random_dungeon_range_16(low, high);
            saved[3] = 0;
        }
        else {
            target->carried_item.unk_00 = 3;
            saved[2] = random_dungeon_range_16(0x10, 0x18);
            saved[3] = 1;
        }
        return 0;
    }
    case 9:
    {
        if (blocked) {
            return 0;
        }
        if ((s16)get_entity_effect_value(target, STATUS_MAGIC_BIND) != 0) {
            return 0;
        }
        if ((generate_random_value() & 7) != 0) {
            return 0;
        }
        if (set_or_clear_actor_status_slot(target, STATUS_MAGIC_BIND, 0x10) < 0) {
            return 0;
        }
        play_sound_if_enabled(0x700);
        saved = get_unused_text_buffer();
        text = expand_text_control_codes(D_800E0C09, saved);
        text = append_entity_display_text(target, text);
        text = expand_text_control_codes(D_800E0C1D, text);
        text = clear_byte_and_advance(text);
        display_text_with_fullwidth_adjustment(saved);
        return 0;
    }
    }
    return 0;
}
