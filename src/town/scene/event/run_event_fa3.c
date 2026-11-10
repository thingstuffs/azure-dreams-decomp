#include "town/player/state.h"
#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/scene/event.h"


/* Calls func_80017DD4 with 0xFA3 and returns zero. */
s32 run_event_fa3(void) {
    clear_script_flag_bit(F_shospital_first_hush);
    return 0;
}
