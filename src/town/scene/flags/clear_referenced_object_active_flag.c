#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"
#include "town/scene/flags.h"



/* Clears the byte at offset 0x114 in the linked record. */
void clear_referenced_object_active_flag(void) {
    ((TownProgressState *)town_scene_root->event_data)->unk_114 = 0;
}
