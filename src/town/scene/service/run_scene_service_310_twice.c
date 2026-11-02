#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/service.h"
#include "shared/town_root.h"

typedef void (*TownCallback)(s32, s32, s32);


// Invoke the town callback twice with command 0x2B, passing 0x9000 then zero.
void run_scene_service_310_twice(void)
{
    ((TownCallback)(town_scene_root->services->callback_310))(
        0x2B, 0x200, 0x9000);
    ((TownCallback)(town_scene_root->services->callback_310))(
        0x2B, 0x200, 0);
}
