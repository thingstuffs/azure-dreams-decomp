#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u32 view_gray_command[];
/* Clears the first word of D_80100D94. */
void clear_transition_word(void) {
    *view_gray_command = 0;
}
