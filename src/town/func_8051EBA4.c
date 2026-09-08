#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80018B5C();                         /* extern */

/* Return whether func_80018B5C reports zero for 0x11FA. */
s32 func_8051EBA4(void) {
    return func_80018B5C(0x11FA) == 0;
}
