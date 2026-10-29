#include "common.h"
#include "town/scene/counter_access.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"

s16 get_scene_value_35be(void) {
    return town_scene_root->town_state->unk_35BE;
}
