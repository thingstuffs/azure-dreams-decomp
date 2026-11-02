#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/scene/event.h"

extern void clear_script_flag_bit(s32 bit_index); /* placed copy of clear_script_flag_bit */

/* Calls func_80017DD4 with 0xFA3 and returns zero. */
s32 run_event_fa3(void) {
    clear_script_flag_bit(F_shospital_first_hush);
    return 0;
}
