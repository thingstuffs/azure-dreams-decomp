#include "common.h"
#include "town/scene/record_services.h"
#include "shared/record_ptrs.h"
/* Call the scene object's 0x238 method with (0x11, 0x200). */
void call_scene_service_pair_b(void)
{
    s8 *scene_root;
    scene_root = (s8 *) ((town_scene_root));
    (*((s32 (**)(s32, s32)) (((s8 *) (*((void **) (scene_root + 0x20)))) + 0x238)))(0x11, 0x200);
}
