#include "common.h"

extern s16 scene_selection_index;

/* Decrements the scene_selection_index halfword. */
void decrement_scene_selection_index(void) {
    scene_selection_index--;
}
