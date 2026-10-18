#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u32 D_80100D94[];
/* Clears the first word of D_80100D94. */
void clear_transition_word(void) {
    *D_80100D94 = 0;
}
