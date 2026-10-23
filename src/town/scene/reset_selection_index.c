#include "common.h"

extern s16 scene_selection_index;

/* Clears D_80017AA0. */
void reset_selection_index(void) {
    scene_selection_index = 0;
}
