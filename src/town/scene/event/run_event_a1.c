#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"
#include "town/player/state.h"

/* Calls func_8001E578 with 0xA1. */
void run_event_a1(void) {
    set_script_flag_bit(F_tw_rain_del);
}
