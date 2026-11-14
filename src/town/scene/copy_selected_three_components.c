#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/scene/fixed_position.h"
#include "town/scene.h"



extern s16 D_80017B30[];


/* Pass the callback-selected eight-byte table entry to set_scene_position_triple. */
void copy_selected_three_components(void) {
    set_scene_position_triple((town_scene_root->services->callback_2D4(0) * 4) + D_80017B30);
}
