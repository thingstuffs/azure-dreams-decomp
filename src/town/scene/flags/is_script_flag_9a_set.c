#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80018B5C();                         /* extern */

/* Returns whether the query for ID 0x9A is nonzero. */
s32 is_script_flag_9a_set(void) {
    return func_80018B5C(0x9A) != 0;
}
