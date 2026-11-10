#include "town/player/state.h"
#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"


/* Calls func_8001E578 with 0x400. */
void trigger_event_resource_400_again(void) {
    set_script_flag_bit(F_sbs01_pad11);
}
