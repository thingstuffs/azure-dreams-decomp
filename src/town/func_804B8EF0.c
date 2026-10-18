#include "common.h"
#include "shared/record_ptrs.h"
/* Call the scene object's 0x238 method with (0x11, 0x200). */
void func_800176F0(void)
{
    s8 *base;
    base = (s8 *) (((int)D_80016000));
    (*((s32 (**)(s32, s32)) (((s8 *) (*((void **) (base + 0x20)))) + 0x238)))(0x11, 0x200);
}
