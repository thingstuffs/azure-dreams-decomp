#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



/* Scale the linked record's value by 64 and add 0x220. */
void scale_record_value_and_add_offset(void) {
    TownPositionState *record;

    record = town_scene_root->position;
    record->x = (s32) ((record->x << 6) + 0x220);
}
