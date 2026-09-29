#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
/* Call the scene object's 0x30C method with 0x8000. */
void func_8001A634(void)
{
    (*((M2C_UNK (**)(M2C_UNK)) (((s8 *) (*((void **) (((s8 *) (((unsigned int)D_80016000))) + 0x20))))
        + 0x30C)))(0x8000);
}
