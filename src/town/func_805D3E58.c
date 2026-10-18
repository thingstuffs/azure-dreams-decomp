#include "common.h"
extern long long D_80016000[0x10];
/* Call the scene object's 0x238 method with (0x11, 0x200). */
void func_80017E58(void)
{
    (*((s32 (**)(s32, s32)) (((s8 *) (*((void **) (((s8 *) (*D_80016000)) + 0x20)))) + 0x238)))(0x11,
        0x200);
}
