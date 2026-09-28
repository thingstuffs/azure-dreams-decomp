#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
/* Call the scene object's 0x238 method with (0x11, 0x200). */
void func_80016908(void)
{
  (*((M2C_UNK (**)(M2C_UNK, M2C_UNK)) (((s8 *) (*((void **) (((s8 *) (((unsigned long)D_80016000))) + 0x20)))) + 0x238)))(0x11, 0x200);
}
