#include "common.h"
#include "shared/record_ptrs.h"
/* Call the scene object's 0x238 method with (0x11, 0x200). */
void clear_indexed_flag_unless_identifier(void)
{
    (*((s32 (**)(s32, s32)) (((s8 *) (*((void **) (((s8 *) (((int)town_scene_root))) + 0x20)))) + 0x238)))(0x11,
        0x200);
}
