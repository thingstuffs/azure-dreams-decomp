#include "script_symbols.h"
#include "shared/town_event_state.h"
#include "common.h"
#include "town/scene/event.h"
#include "town/player/state.h"

/* Dispatch event 0x402 when the state byte is nonzero. */
s32 dispatch_event_402_if_state_set(void) {
    if (town_event_state->dispatchState == 0) {
        return 0;
    }
    set_script_flag_bit(F_sbs01_pad13);
    return 1;
}
