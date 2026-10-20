#include "script_symbols.h"
#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80018B5C();                         /* extern */

/* Return whether func_80018B5C reports zero for 0x11FA. */
s32 is_script_flag_11fa_clear(void) {
    return func_80018B5C(Fp_niko_kenkatyu) == 0;
}
