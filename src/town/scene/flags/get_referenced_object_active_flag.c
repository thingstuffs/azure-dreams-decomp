#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



/* Returns the byte at offset 0x114 in the referenced record. */
u8 get_referenced_object_active_flag(void) {
    return ((u8)((TownProgressState *)town_scene_root->event_data)->unk_114);
}
