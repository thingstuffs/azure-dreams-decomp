#include "common.h"
#include "town.h"

extern s16 scene_selection_index;

/* Increments the scene_selection_index halfword with 16-bit wrapping. */
void increment_scene_selection_index(void) {
    scene_selection_index = (u16)(scene_selection_index + 1);
}
