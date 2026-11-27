#include "common.h"
#include "town/scene/state_data.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"
#include "town/scene/object.h"



extern u8 scene_command_records;

/* Set the selected record index from the current object's lookup entry. */
void set_selected_row_from_object_lookup(void) {
    selected_scene_row_index = (s32) *((town_scene_root->position->unk_34 * 4) + &scene_command_records);
}
