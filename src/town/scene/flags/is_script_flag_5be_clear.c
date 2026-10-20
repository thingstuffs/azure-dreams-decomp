#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80018B5C();                         /* extern */

/* Returns whether func_80018B5C reports zero for ID 0x5BE. */
s32 is_script_flag_5be_clear(void) {
    return func_80018B5C(0x5BE) == 0;
}
