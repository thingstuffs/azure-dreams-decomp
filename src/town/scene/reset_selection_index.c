#include "common.h"

extern s16 D_80017AA0;

/* Clears D_80017AA0. */
void reset_selection_index(void) {
    D_80017AA0 = 0;
}
