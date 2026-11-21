#include "town/scene/hooks.h"
#include "town/scene/state_data.h"

void set_global_entry_pair(struct Rec_func_800165F4_arg0 *row, s32 entry_index) {
    scene_saved_choice_row = row;
    scene_saved_choice_index = entry_index;
}
