#include "town/scene/event.h"
#include "town/scene/flags.h"
#include "town/scene/state_data.h"

void forward_stored_pair(void) {
    set_indexed_entry_flag(scene_saved_choice_row, scene_saved_choice_index);
}
