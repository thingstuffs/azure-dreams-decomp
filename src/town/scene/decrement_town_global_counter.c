#include "common.h"

extern u16 scene_selection_index[];

/* Decrements the first value in D_80017AA0. */
void decrement_town_global_counter(void) {
    scene_selection_index[0]--;
}
