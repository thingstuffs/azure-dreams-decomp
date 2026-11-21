#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/state_data.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"

s32 update_object_entry_flag(Rec_func_800165F4_arg0 *entry, s32 entry_index) {
    set_script_flag_bit(entry->unk_18);
    ((TownEntryStatus *)town_scene_root->event_data)[town_scene_root->entry_index].state = 0;
    return apply_selected_entry_values(entry, entry_index);
}
