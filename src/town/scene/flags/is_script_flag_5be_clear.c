#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Returns whether func_80018B5C reports zero for ID 0x5BE. */
s32 is_script_flag_5be_clear(void) {
    return func_80018B5C(F_sbs11_pad27) == 0;
}
