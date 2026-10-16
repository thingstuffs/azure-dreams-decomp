#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 townGetSelectedTableEntry(); /* extern */

/* Loads the monster talk palette (func_koya_mon_talk_pal_ld). */
void scr_func_koya_mon_talk_pal_ld(void) {
    townGetSelectedTableEntry(0, 0, 0, 0);
}
