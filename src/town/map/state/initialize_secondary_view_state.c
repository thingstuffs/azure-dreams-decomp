#include "common.h"
#include "shared/game_work.h"
#include "town/map/state.h"
#include "town/map.h"
#include "town/map/object_callbacks_api.h"
#include "town/data.h"




/* Initialize paired state values and install the two callbacks. */
void initialize_secondary_view_state(MapSecondaryCallbackState *state) {
    u16 initial_ac;
    u16 initial_ae;

    initial_ac = ((u16)g_game_work.view.view_offset.parts.view_offset_x);
    state->current_x = initial_ac;
    state->saved_x = initial_ac;

    initial_ae = ((u16)g_game_work.view.view_offset.parts.view_offset_y);
    state->current_y = initial_ae;
    state->saved_y = initial_ae;

    g_game_work.view.view_offset.parts.view_offset_z = 0x400;
    state->current_z = 0x400;
    state->saved_z = 0x400;
    state->select_title = select_title_object_handler;
    state->update_coordinates = update_current_and_saved_coordinates;
}
