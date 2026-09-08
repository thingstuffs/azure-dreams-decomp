#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80018B5C();                         /* extern */

/* Returns whether the query for 0x5C0 yields zero. */
s32 func_80016BE8(void) {
    return func_80018B5C(0x5C0) == 0;
}
