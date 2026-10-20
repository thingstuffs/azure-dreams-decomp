#include "common.h"
#include "shared/record_ptrs.h"
/* Call the scene object's 0x2F4 method with (-1, -5). */
void call_scene_service_2f4_fixed(void)
{
    (*((s32 (**)(s32, s32)) (((s8 *) (*((void **) (((s8 *) (((int)D_80016000))) + 0x20)))) + 0x2F4)))(-1,
        -5);
}
