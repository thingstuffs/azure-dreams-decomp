#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80018B5C();                         /* extern */

/* Returns whether the query for 0x5BC yields a nonzero result. */
s32 func_8051EC3C(void) {
    return func_80018B5C(0x5BC) != 0;
}
