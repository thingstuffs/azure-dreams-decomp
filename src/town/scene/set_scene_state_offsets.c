#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"


/* Set the town state's unk4 and unk8 values to 0x6A0 and 0x4A0. */
void set_scene_state_offsets(void) {
    ((TownPositionState *)town_scene_root->position)->x = 0x6A0;
    ((TownPositionState *)town_scene_root->position)->y = 0x4A0;
}
