#include "shared/town_root.h"
#include "common.h"
#include "town/scene/mode_data.h"
#include "town/scene/state_data.h"
#include "town/scene/entry_requests.h"
#include "shared/record_ptrs.h"
#include "town/scene.h"
#include "town/scene/event.h"

/* Updates the current town entry and clears its state on a nonzero result or global state 1. */
s32 update_entry_state_and_clear(void *object, s32 entry_index)
{
    s32 update_result;
    u8 entry_state;

    update_result = 0;
    entry_state = ((TownEntryStatus *)town_scene_root->event_data)[town_scene_root->entry_index].state;
    scene_cell_dispatch_code = entry_state;
    if (entry_state != 2) {
        update_result = apply_selected_entry_values(object, entry_index);
    }
    if ((update_result != 0) || (invoke_callback_event_11(), scene_cell_dispatch_code == 1)) {
        ((TownEntryStatus *)town_scene_root->event_data)[town_scene_root->entry_index].state = 0;
        scene_cell_dispatch_code = 0;
    }
    return update_result;
}
