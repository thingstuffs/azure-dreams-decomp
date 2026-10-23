#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
extern M2C_UNK D_8001C048;
/* Call the scene object's 0x268 method with the D_8001C048 record. */
void invoke_scene_record_handler(void)
{
    s32 (*handler)(s32 *, s32);
    void **slot;
    s8 *base;
    base = ((s8 *) (((unsigned int)town_scene_root))) + 0x20;
    slot = base;
    handler = *((s32 (**)(s32 *, s32)) (((s8 *) (*slot)) + 0x268));
    handler(&D_8001C048, 1);
}
