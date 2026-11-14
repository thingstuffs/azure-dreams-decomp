#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"
#include "town/scene/object.h"
#include "town/scene/progress_data.h"

/* Decrements the object's counter and invokes a callback if the object check succeeds. */
void pay_progress_step_and_build_land(void) {
    TownStateRecord *counter_obj;

    counter_obj = town_scene_root->town_state;
    counter_obj->money = (u32) (((signed int)counter_obj->money) - scene_progress_step);
    if (check_progress_against_callback() != 0) {
        ((s32 (*) (s32, s32))town_scene_root->services->BuildLandBuilding)(0x10,
            5);
    }
}
