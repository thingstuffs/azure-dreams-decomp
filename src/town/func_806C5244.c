#include "common.h"
#include "shared/record_ptrs.h"
/* Call the scene object's 0x214, 0x20C and 0x228 methods with 0. */
void func_806C5244(void)
{
    (*((s32 (**)(s32)) (((s8 *) (*((void **) (((s8 *) (*((void **) (((s8 *) (((s32 *)&D_80016000))) + 0))))
        + 0x20)))) + 0x214)))(0);
    (*((s32 (**)(s32)) (((s8 *) (*((void **) (((s8 *) (*((void **) (((s8 *) (((s32 *)&D_80016000))) + 0))))
        + 0x20)))) + 0x20C)))(0);
    (*((s32 (**)(s32)) (((s8 *) (*((void **) (((s8 *) (*((void **) (((s8 *) (((s32 *)&D_80016000))) + 0))))
        + 0x20)))) + 0x228)))(0);
}
