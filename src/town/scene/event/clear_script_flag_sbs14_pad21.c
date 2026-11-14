#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"
#include "town/player/state.h"


/* Calls func_80019458 with value 0x639. */
void clear_script_flag_sbs14_pad21(void) {
    clear_script_flag_bit(F_sbs14_pad21);
}
