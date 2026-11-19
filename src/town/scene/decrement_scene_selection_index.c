#include "common.h"
#include "town/scene/state_data.h"

/* Decrements the scene_selection_index halfword. */
void decrement_scene_selection_index(void) {
    scene_selection_index--;
}
