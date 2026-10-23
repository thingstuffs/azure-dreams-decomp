#include "common.h"
#include "shared/record_ptrs.h"
/* Call the scene object's 0x238 method with (0x11, 0x200). */
void invoke_scene_method_event_11(void)
{
    (*((s32 (**)(s32, s32)) (((s8 *) (*((void **) (((s8 *) (((unsigned int)town_scene_root))) + 0x20))))
        + 0x238)))(0x11, 0x200);
}
