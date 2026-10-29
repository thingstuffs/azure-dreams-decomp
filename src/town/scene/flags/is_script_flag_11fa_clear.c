#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Return whether func_80018B5C reports zero for 0x11FA. */
s32 is_script_flag_11fa_clear(void) {
    return func_80018B5C(Fp_niko_kenkatyu) == 0;
}
