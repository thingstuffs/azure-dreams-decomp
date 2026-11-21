#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/state_data.h"
#include "town/scene/flags.h"

void set_current_entry_flag(void) {
    ((TownEntryStatus *)town_scene_root->event_data)[town_scene_root->entry_index].state = 1;
}
