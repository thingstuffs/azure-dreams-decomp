#include "common.h"
#include "town/map.h"
#include "town/data.h"

/* Clears the word addressed by view_gray_command. */
void clear_transition_word(void) {
    *view_gray_command = 0;
}
