#include "script_symbols.h"
#include "shared/town_event_state.h"
#include "common.h"
#include "town/scene/event.h"
#include "town/player/state.h"

/* Set three state bytes to 2 and dispatch event 0xA2. */
void set_ending_event_state(void) {
    town_event_state->unk_00 = 2;
    town_event_state->selection_mode = 2;
    town_event_state->dispatchState = 2;
    set_script_flag_bit(F_end_ending);
}
