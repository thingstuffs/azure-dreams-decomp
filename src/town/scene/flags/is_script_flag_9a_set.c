#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Returns whether the query for ID 0x9A is nonzero. */
s32 is_script_flag_9a_set(void) {
    return func_80018B5C(F_viv_engei_ok) != 0;
}
