#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Returns whether the query for 0x5C0 yields zero. */
s32 check_query_0x5c0_zero(void) {
    return func_80018B5C(F_sbs11_pad29) == 0;
}
