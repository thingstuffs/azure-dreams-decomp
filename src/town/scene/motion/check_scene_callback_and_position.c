#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/motion.h"
#include "shared/town_root.h"


typedef s32 (*FuncT)(s32);

/* Calls the state callback with one and checks whether the position value is below 0x501. */
s32 check_scene_callback_and_position(void) {
    ((FuncT)(town_scene_root->services->callback_248))(1);
    return town_scene_root->position->y < 0x501;
}
