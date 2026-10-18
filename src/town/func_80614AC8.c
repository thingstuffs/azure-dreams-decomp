#include "common.h"
#include "shared/record_ptrs.h"
/* Call the scene object's 0x248 method, then advance the state's x field by 0x20. */
void func_80614AC8(void)
{
    void *state;
    (*((s32 (**)(s32)) (((s8 *) (*((void **) (((s8 *) (*((void **) (((s8 *) (((s32 *)&D_80016000))) + 0))))
        + 0x20)))) + 0x248)))(0);
    state = *((void **) (((s8 *) (*((void **) (((s8 *) (((s32 *)&D_80016000))) + 0)))) + 0x1C));
    *((s32 *) (((s8 *) state) + 4)) = (s32) ((*((s32 *) (((s8 *) state) + 4))) + 0x20);
}
