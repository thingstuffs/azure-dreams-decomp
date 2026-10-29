#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Returns whether func_80018B5C reports a nonzero value for 0x5BD. */
s32 is_script_flag_5bd_set(void) {
    return func_80018B5C(F_sbs11_pad26) != 0;
}
