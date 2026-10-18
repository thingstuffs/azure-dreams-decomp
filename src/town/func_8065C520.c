#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
/* Call the scene object's 0x238 method with (0x11, 0x200). */
void clear_indexed_flag_unless_identifier(void)
{
    (*((M2C_UNK (**)(M2C_UNK, M2C_UNK)) (((s8 *) (*((void **) (((s8 *) (((int)D_80016000))) + 0x20)))) + 0x238)))(0x11,
        0x200);
}
