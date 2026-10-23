#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"


/* Sets the referenced object's flag at offset 0x114 to 1. */
void set_referenced_object_active_flag(void) {
    ((TownProgressState *)town_scene_root->event_data)->unk_114 = 1;
}
