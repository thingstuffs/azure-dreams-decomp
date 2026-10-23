#include "common.h"

extern u16 scene_selection_index[];

/* Decrements the first scene_selection_index halfword. */
void decrement_town_global_counter(void) {
    scene_selection_index[0]--;
}
