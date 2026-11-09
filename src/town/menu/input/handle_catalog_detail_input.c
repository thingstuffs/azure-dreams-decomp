#include "common.h"
#include "shared/game_work.h"
#include "town/menu.h"
#include "town/menu/catalog.h"
#include "town/data.h"

typedef struct {
    void **images;
    u8 count;
    u8 pad[3];
} ImageList;


extern void SD_Call(s32);

extern ImageList catalog_detail_images[];

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
        state->unk_0A = 9;
        state->unk_04 = 1;
        state->unk_06 = 0x19;
        return;
    }

    buttons = ((u32)g_game_work.buttons);
    if (buttons & 0x1000) {
        u8 *selection = catalog_selection_state;

        if (selection[9] >= 4) {
            state->unk_0A = 0xD;
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

        max_scroll = (catalog_detail_images[state->unk_13].count - 3) << 4;
        selection = catalog_selection_state;
        if (((max_scroll & 0xF0) - 4) >= selection[9]) {
            state->unk_0A = 0xE;
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
        state->unk_14 = state->unk_13;
        do {
            if (state->unk_13 == 0) {
                state->unk_13 = index_count;
            }
            state->unk_13--;
        } while (!(is_catalog_entry_available(state->unk_13) & 0xFF) &&
            state->unk_13 != state->unk_14);

        if (state->unk_13 == 0x31) {
            state->unk_10 = 1;
            state->unk_11 = 0;
            state->unk_0F = state->unk_13 >> 4;
        } else {
            u32 packed_index;
            u32 index_bits;

            packed_index = state->unk_13;
            index_bits = packed_index;
            packed_index >>= 4;
            index_bits >>= 3;
            state->unk_0F = packed_index;
            state->unk_10 = index_bits & 1;
            state->unk_11 = state->unk_13 & 7;
        }

        current_index = state->unk_13;
        previous_index = state->unk_14;
        if (current_index < previous_index) {
            SD_Call(0x702);
            reset_catalog_scroll_indicators(state);
            state->unk_16 ^= 1;
            select_paired_value_tables(state);
            side_choice = state->choices[state->unk_16];
            if (side_choice != state->unk_13) {
                state->unk_0A = 0xC;
                return;
            }
            state->unk_0A = 0xA;
            state->unk_04 = 1;
            state->unk_06 = 0x19;
            return;
        }
        if (previous_index < current_index) {
            SD_Call(0x702);
            reset_catalog_scroll_indicators(state);
            state->unk_16 ^= 1;
            select_paired_value_tables(state);
            if (state->choices[state->unk_16] == state->unk_13) {
                state->unk_0A = 0xB;
                state->unk_04 = 1;
                state->unk_06 = 0x19;
                return;
            }
            state->unk_0A = 0xC;
        }
        return;
    }

    if (buttons & 0x2000) {
        s32 wrap_limit = 0x32;
        state->unk_14 = state->unk_13;
        do {
            next_index = state->unk_13 + 1;
            state->unk_13 = next_index;
            if ((next_index & 0xFF) == wrap_limit) {
                state->unk_13 = 0;
            }
        } while (!(is_catalog_entry_available(state->unk_13) & 0xFF) &&
            state->unk_13 != state->unk_14);

        if (state->unk_13 == 0x31) {
            state->unk_10 = 1;
            state->unk_11 = 0;
            state->unk_0F = state->unk_13 >> 4;
        } else {
            u32 packed_index;
            u32 index_bits;

            packed_index = state->unk_13;
            index_bits = packed_index;
            packed_index >>= 4;
            index_bits >>= 3;
            state->unk_0F = packed_index;
            state->unk_10 = index_bits & 1;
            state->unk_11 = state->unk_13 & 7;
        }

        current_index = state->unk_13;
        previous_index = state->unk_14;
        if (current_index < previous_index) {
            SD_Call(0x702);
            reset_catalog_scroll_indicators(state);
            state->unk_16 ^= 1;
            select_paired_value_tables(state);
            if (state->choices[state->unk_16] != state->unk_13) {
                state->unk_0A = 0xC;
                return;
            }
            state->unk_0A = 0xA;
            state->unk_04 = 1;
            state->unk_06 = 0x19;
            return;
        }
        if (previous_index < current_index) {
            SD_Call(0x702);
            reset_catalog_scroll_indicators(state);
            state->unk_16 ^= 1;
            select_paired_value_tables(state);
            if (state->choices[state->unk_16] == state->unk_13) {
                state->unk_0A = 0xB;
                state->unk_04 = 1;
                state->unk_06 = 0x19;
                return;
            }
            state->unk_0A = 0xC;
        }
        return;
    }

    toggle_timer = state->unk_08 + 1;
    state->unk_08 = toggle_timer;
    if ((s16)toggle_timer >= 8) {
        state->unk_08 = 0;
        state->unk_0C ^= 1;
    }

    update_catalog_scroll_availability(state);

    return;
}
