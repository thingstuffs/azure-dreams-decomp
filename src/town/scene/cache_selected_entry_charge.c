#include "common.h"
#include "town/scene/state_data.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/scene.h"
#include "town/data.h"


/* Cache the selected record's index and value, then return its value. */
s32 cache_selected_entry_charge(void) {
    TownSceneChargeEntry *selected_record;

    selected_record = (TownSceneChargeEntry *)town_scene_root->event_data + town_scene_root->entry_index;
    selected_scene_row_index = (s32) selected_record->row_index;
    scene_charge = selected_record->charge;
    return selected_record->charge;
}
