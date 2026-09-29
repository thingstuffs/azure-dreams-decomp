#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
/* Call the scene object's 0x2F4 method with (-1, -5). */
void func_8001A670(void)
{
    (*((M2C_UNK (**)(M2C_UNK, M2C_UNK)) (((s8 *) (*((void **) (((s8 *) (((int)D_80016000))) + 0x20)))) + 0x2F4)))(-1,
        -5);
}
