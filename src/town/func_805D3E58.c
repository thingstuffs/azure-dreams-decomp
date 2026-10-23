#include "common.h"
#include "town/scene/record_services.h"
extern long long D_80016000[0x10];
/* Call the scene object's 0x238 method with (0x11, 0x200). */
void call_scene_service_pair_c(void)
{
    (*((s32 (**)(s32, s32)) (((s8 *) (*((void **) (((s8 *) (*D_80016000)) + 0x20)))) + 0x238)))(0x11,
        0x200);
}
