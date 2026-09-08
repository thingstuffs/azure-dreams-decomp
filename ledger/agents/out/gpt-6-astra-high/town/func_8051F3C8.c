#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80018B5C();                         /* extern */

/* Returns whether func_80018B5C reports zero for ID 0x5BF. */
s32 func_80016BC8(void) {
    return func_80018B5C(0x5BF) == 0;
}
