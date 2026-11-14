#include "script_symbols.h"
#include "common.h"
#include "town/player/state.h"

/* Calls func_800198D0 with argument 0x15. */
void check_open_end_script_flag(void) {
    get_script_flag_mask(sn_open_end);
}
