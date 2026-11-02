#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"
#include "town/player/state.h"

/* Invoke the setup handlers with four fixed identifiers. */
s32 invoke_event_setup_handlers(void) {
    set_script_flag_bit(F_s24_door_open);
    clear_script_flag_bit(F_cheriru_first_cheriru);
    clear_script_flag_bit(F_cheriru_first_nadia);
    clear_script_flag_bit(F_cheriru_first_nadia2);
    return 0;
}
