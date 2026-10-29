#include "common.h"
#include "town/map.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u32 view_gray_command[];
/* Clears the word addressed by view_gray_command. */
void clear_transition_word(void) {
    *view_gray_command = 0;
}
