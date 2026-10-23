#include "common.h"

extern u16 scene_selection_index[8];

/* Increment the first 16-bit counter in D_80017AA0. */
void increment_scene_selection_index(void) {
    scene_selection_index[0] = (u16)(scene_selection_index[0] + 1);
}
