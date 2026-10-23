#include "common.h"
#include "town/scene/counter_access.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

s16 read_scene_counter_b(void) {
    return town_scene_root->town_state->unk_35C0;
}
