#include "common.h"
#include "shared/record_ptrs.h"
/* Call the scene object's 0x20C and 0x228 methods with 0. */
void run_scene_services_20c_228(void)
{
    (*((s32 (**)(s32)) (((s8 *) (*((void **) (((s8 *) (*((void **) (((s8 *) (((s32 *)&D_80016000))) + 0))))
        + 0x20)))) + 0x20C)))(0);
    (*((s32 (**)(s32)) (((s8 *) (*((void **) (((s8 *) (*((void **) (((s8 *) (((s32 *)&D_80016000))) + 0))))
        + 0x20)))) + 0x228)))(0);
}
