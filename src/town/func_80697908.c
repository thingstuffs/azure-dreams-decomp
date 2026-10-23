#include "common.h"
#include "town/scene/record_services.h"
#include "shared/record_ptrs.h"
/* Call the scene object's 0x238 method with (0x11, 0x200). */
void call_scene_service_pair_a(void)
{
    (*((s32 (**)(s32, s32)) (((s8 *) (*((void **) (((s8 *) (((unsigned long)town_scene_root))) + 0x20))))
        + 0x238)))(0x11, 0x200);
}
