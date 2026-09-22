#include "common.h"
#include "m2c_compat.h"
extern int D_80016000[0x10];
/* Call the scene object's 0x238 method with (0x11, 0x200). */
void func_800176F0(void)
{
  s8 *base;
  base = (s8 *) (*D_80016000);
  (*((M2C_UNK (**)(M2C_UNK, M2C_UNK)) (((s8 *) (*((void **) (base + 0x20)))) + 0x238)))(0x11, 0x200);
}
