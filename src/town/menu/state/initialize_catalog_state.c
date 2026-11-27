#include "common.h"
#include "town/menu/catalog.h"
#include "town/menu.h"
#include "town/menu/animation.h"
#include "town/menu/state.h"

extern void initialize_catalog_view_records(void *, void *, void *);

/* Initialize state defaults and run the associated setup routines. */
void initialize_catalog_state(CatalogDisplay *state) {
    s32 one = 1;

    state->transition_frame = 0;
    state->transition_duration = 0;
    state->scroll_blink_timer = 0;
    state->phase = 0;
    state->texture_load_phase = 0;
    state->scroll_indicator_visible = one;
    state->texture_load_done = 0;
    state->scroll_direction_mask = 0;
    state->page_index = 0;
    state->column_index = 0;
    state->row_index = 0;
    state->previous_row_index = 0;
    state->selected_entry = 0;
    state->previous_entry = 0;
    state->active_detail_slot = 0;
    state->choices[0] = 0xFF;
    state->choices[1] = 0xFF;

    if ((is_catalog_entry_available(0x31) & 0xFF) ||
        (is_catalog_entry_available(0x30) & 0xFF)) {
        state->final_page_locked = 0;
    } else {
        state->final_page_locked = one;
    }

    initialize_catalog_view_records((u8 *)state + 0x48, (u8 *)state + 0x20,
                  (u8 *)state + 0x30);
    select_paired_value_tables(state);
    initialize_catalog_slot_records();
    layout_catalog_frame();
    layout_catalog_entry_grid();
    refresh_catalog_entry_grid(state);
}
