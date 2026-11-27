#include "common.h"
#include "shared/game_work.h"
#include "town/menu.h"
#include "town/menu/catalog.h"
#include "town/data.h"
#include "slus.h"
#include "town/menu/catalog_detail_data.h"

/* Handles selection navigation, scrolling, transitions, and the idle toggle timer. */
void handle_catalog_detail_input(CatalogDisplay *state)
{
    u32 buttons;
    s32 max_scroll;
    u8 current_index;
    u8 previous_index;
    u8 next_index;
    u8 side_choice;
    u16 toggle_timer;

    if (((u32)g_game_work.pressed_buttons) & 0x20) {
        SD_Call(0x702);
        reset_catalog_scroll_indicators(state);
        state->phase = 9;
        state->transition_frame = 1;
        state->transition_duration = 0x19;
        return;
    }

    buttons = ((u32)g_game_work.buttons);
    if (buttons & 0x1000) {
        u8 *selection = catalog_selection_state;

        if (selection[9] >= 4) {
            state->phase = 0xD;
            selection[9] -= 4;
        } else {
            selection[9] = 0;
        }
        reset_catalog_scroll_indicators(state);
        update_catalog_scroll_availability(state);
        return;
    }

    if (buttons & 0x4000) {
        u8 *selection;

        max_scroll = (catalog_detail_images[state->selected_entry].count - 3) << 4;
        selection = catalog_selection_state;
        if (((max_scroll & 0xF0) - 4) >= selection[9]) {
            state->phase = 0xE;
            selection[9] += 4;
        } else {
            selection[9] = max_scroll;
        }
        reset_catalog_scroll_indicators(state);
        update_catalog_scroll_availability(state);
        return;
    }

    if (buttons & 0x8000) {
        u8 index_count = 0x32;
        state->previous_entry = state->selected_entry;
        do {
            if (state->selected_entry == 0) {
                state->selected_entry = index_count;
            }
            state->selected_entry--;
        } while (!(is_catalog_entry_available(state->selected_entry) & 0xFF) &&
            state->selected_entry != state->previous_entry);

        if (state->selected_entry == 0x31) {
            state->column_index = 1;
            state->row_index = 0;
            state->page_index = state->selected_entry >> 4;
        } else {
            u32 packed_index;
            u32 index_bits;

            packed_index = state->selected_entry;
            index_bits = packed_index;
            packed_index >>= 4;
            index_bits >>= 3;
            state->page_index = packed_index;
            state->column_index = index_bits & 1;
            state->row_index = state->selected_entry & 7;
        }

        current_index = state->selected_entry;
        previous_index = state->previous_entry;
        if (current_index < previous_index) {
            SD_Call(0x702);
            reset_catalog_scroll_indicators(state);
            state->active_detail_slot ^= 1;
            select_paired_value_tables(state);
            side_choice = state->choices[state->active_detail_slot];
            if (side_choice != state->selected_entry) {
                state->phase = 0xC;
                return;
            }
            state->phase = 0xA;
            state->transition_frame = 1;
            state->transition_duration = 0x19;
            return;
        }
        if (previous_index < current_index) {
            SD_Call(0x702);
            reset_catalog_scroll_indicators(state);
            state->active_detail_slot ^= 1;
            select_paired_value_tables(state);
            if (state->choices[state->active_detail_slot] == state->selected_entry) {
                state->phase = 0xB;
                state->transition_frame = 1;
                state->transition_duration = 0x19;
                return;
            }
            state->phase = 0xC;
        }
        return;
    }

    if (buttons & 0x2000) {
        s32 wrap_limit = 0x32;
        state->previous_entry = state->selected_entry;
        do {
            next_index = state->selected_entry + 1;
            state->selected_entry = next_index;
            if ((next_index & 0xFF) == wrap_limit) {
                state->selected_entry = 0;
            }
        } while (!(is_catalog_entry_available(state->selected_entry) & 0xFF) &&
            state->selected_entry != state->previous_entry);

        if (state->selected_entry == 0x31) {
            state->column_index = 1;
            state->row_index = 0;
            state->page_index = state->selected_entry >> 4;
        } else {
            u32 packed_index;
            u32 index_bits;

            packed_index = state->selected_entry;
            index_bits = packed_index;
            packed_index >>= 4;
            index_bits >>= 3;
            state->page_index = packed_index;
            state->column_index = index_bits & 1;
            state->row_index = state->selected_entry & 7;
        }

        current_index = state->selected_entry;
        previous_index = state->previous_entry;
        if (current_index < previous_index) {
            SD_Call(0x702);
            reset_catalog_scroll_indicators(state);
            state->active_detail_slot ^= 1;
            select_paired_value_tables(state);
            if (state->choices[state->active_detail_slot] != state->selected_entry) {
                state->phase = 0xC;
                return;
            }
            state->phase = 0xA;
            state->transition_frame = 1;
            state->transition_duration = 0x19;
            return;
        }
        if (previous_index < current_index) {
            SD_Call(0x702);
            reset_catalog_scroll_indicators(state);
            state->active_detail_slot ^= 1;
            select_paired_value_tables(state);
            if (state->choices[state->active_detail_slot] == state->selected_entry) {
                state->phase = 0xB;
                state->transition_frame = 1;
                state->transition_duration = 0x19;
                return;
            }
            state->phase = 0xC;
        }
        return;
    }

    toggle_timer = state->scroll_blink_timer + 1;
    state->scroll_blink_timer = toggle_timer;
    if ((s16)toggle_timer >= 8) {
        state->scroll_blink_timer = 0;
        state->scroll_indicator_visible ^= 1;
    }

    update_catalog_scroll_availability(state);

    return;
}
