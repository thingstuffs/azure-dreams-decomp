#include "common.h"
#include "town/scene/state_data.h"
#include "town.h"

/* Increments the scene_selection_index halfword with 16-bit wrapping. */
void increment_scene_selection_index(void) {
    scene_selection_index = (u16)(scene_selection_index + 1);
}
