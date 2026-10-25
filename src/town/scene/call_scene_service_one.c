#include "common.h"
#include "town/scene.h"
#include "shared/town_root.h"
#include "shared/record_ptrs.h"

/* Submit value one to the scene service at table offset 0x258. */
void call_scene_service_one(void)
{
    town_scene_root->services->callback_258(1);
}
