/* Update slot countdowns, choices, and resource colors (G00621). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B6384, CL:town/func_800B63B8, CL:town/func_800B64A4. */
#include "town/shop/slot_resource_updates_g00621.h"

/* Move three channel values a quarter of the way toward 0x80, snapping when within four. */
void move_color_channels_toward_neutral(u8 *channels)
{
    s32 delta;
    s32 magnitude;
    s32 adjusted_delta;
    u8 value;

    if ((*(u32 *)channels << 8) == 0x80808000) {
        return;
    }

    value = channels[0];
    delta = 0x80 - value;
    magnitude = (s16)delta;
    if (delta < 0) {
        magnitude = 0 - magnitude;
    }
    if (magnitude >= 5) {
        adjusted_delta = delta;
        if (adjusted_delta < 0) {
            adjusted_delta += 3;
        }
        channels[0] = value + (adjusted_delta >> 2);
    } else {
        channels[0] = 0x80;
    }

    value = channels[1];
    delta = 0x80 - value;
    magnitude = delta;
    magnitude = abs(magnitude);
    if (magnitude >= 5) {
        adjusted_delta = delta;
        if (adjusted_delta < 0) {
            adjusted_delta += 3;
        }
        channels[1] = value + (adjusted_delta >> 2);
    } else {
        channels[1] = 0x80;
    }

    value = channels[2];
    delta = 0x80 - value;
    magnitude = delta;
    magnitude = abs(magnitude);
    if (magnitude >= 5) {
        adjusted_delta = delta;
        channels[2] = value + (adjusted_delta / 4);
    } else {
        channels[2] = 0x80;
    }
}

/* Maps pressed buttons to choices 2, 3, or 4, marks the choice slot, and returns -1 when none is pressed. */
s32 select_choice_from_input_flags(s32 *choice_values)
{
    s32 choice;
    s32 town_flags;
    s32 selected_value;

    choice = -1;
    if (g_game_work.buttons != 0) {
        town_flags = (g_game_work.pressed_buttons);
        if (town_flags & 0x40) {
            choice = 2;
        } else if (town_flags & 0x10) {
            choice = 3;
        } else if (town_flags & 0x20) {
            choice = 4;
        }
    }
    selected_value = 4;
    if (choice != -1) {
        choice_values[choice + 3] = selected_value;
    }
    return choice;
}

/* Decrement countdowns for slots 2 through 4, processing resources whose countdown is zero. */
void process_resources_for_expired_slot_countdowns(void *state) {
    s32 countdown;
    s32 resource_addr;
    u32 slot_offset;
    s32 *table;
    s32 *entry;
    s32 slot;
    void *owner;
    void *count_cursor;

    owner = state;
    slot = 2;
    count_cursor = owner + 8;
    do {
        countdown = ((S_800B3C74_0 *)count_cursor)->unk_0C;
        slot_offset = slot << 2;
        if (countdown == 0) {
            table = ((S_800B3C74_1 *)owner)->unk_5C;
            entry = (s32 *)(slot_offset + (long)table);
            resource_addr = *entry;
            count_cursor += 4;
            move_color_channels_toward_neutral(((S_800B3C74_2 *)((s32 *)resource_addr))->unk_04);
        } else {
            countdown--;
            ((S_800B3C74_0 *)count_cursor)->unk_0C = countdown;
            count_cursor += 4;
        }
        slot += 1;
    } while (slot < 5);
}
