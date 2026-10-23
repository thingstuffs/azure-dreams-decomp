#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"


extern u32 scene_progress_step[];

/* Decrements the object's counter and invokes a callback if the object check succeeds. */
void tick_object_counter_and_invoke_callback(void) {
    TownStateRecord *counter_obj;

    counter_obj = town_scene_root->town_state;
    counter_obj->money = (u32) (((signed int)counter_obj->money) - scene_progress_step[0]);
    if (check_progress_against_callback() != 0) {
        ((s32 (*) (s32, s32))town_scene_root->services->callback_04C)(0x10,
            5);
    }
}
