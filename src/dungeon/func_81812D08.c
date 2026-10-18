#include "modules/dungeon_ovl_1831cd8.h"

void update_menu_progress_bar(ovl_1831cd8_81812D08_ProgressState *state) {
    store_scaled_menu_ratio(state->entries, state->current, state->maximum);
    draw_menu_progress_bar(state, state->current, state->maximum);
    set_menu_object_scale_fields(state->entries, state->current, state->maximum);
    refresh_menu_entry_resources(state->entries, state->resource_names);
    advance_timed_tagged_stream(state->cursor);
}
