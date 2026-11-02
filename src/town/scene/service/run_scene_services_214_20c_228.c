#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/service.h"
#include "shared/town_root.h"
/* Call the scene object's 0x214, 0x20C and 0x228 methods with 0. */
void run_scene_services_214_20c_228(void)
{
    (*(s32 (**)(s32))((u8 *)town_scene_root->services + 0x214))(0);
    (*(s32 (**)(s32))((u8 *)town_scene_root->services + 0x20C))(0);
    town_scene_root->services->callback_228(0);
}
