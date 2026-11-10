#include "town/player/state.h"
#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_8001A054;

/* Calls func_800197D8 with ID 0x403 and returns the address of D_8001A054. */
s32 *run_event_403_get_buffer(void) {
    set_script_flag_bit(F_sbs01_pad14);
    return &D_8001A054;
}
