#include "common.h"

extern u16 scene_selection_index[8];

/* Increments the first scene_selection_index halfword with 16-bit wrapping. */
void increment_scene_selection_index(void) {
    scene_selection_index[0] = (u16)(scene_selection_index[0] + 1);
}
