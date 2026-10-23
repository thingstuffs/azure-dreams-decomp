#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



extern u8 D_80019B08;
extern s32 selected_scene_row_index;


/* Set the selected record index from the current object's lookup entry. */
void set_selected_row_from_object_lookup(void) {
    selected_scene_row_index = (s32) *((((TownPositionState *)town_scene_root->position)->unk_34 * 4) + &D_80019B08);
}
