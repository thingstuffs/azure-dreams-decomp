#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/scene/service.h"



/* Dispatches the supplied value with bit 0x8000 set. */
void call_scene_service_280_with_flag_8000(s32 value) {
    town_scene_root->services->play_sound(value | 0x8000);
}
