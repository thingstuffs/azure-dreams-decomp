#include "common.h"
#include "m2c_compat.h"
extern volatile unsigned int D_80016000[0x10];
extern M2C_UNK D_8001C048;
/* Call the scene object's 0x268 method with the D_8001C048 record. */
void func_80016588(void)
{
  M2C_UNK (*handler)(M2C_UNK *, M2C_UNK);
  void **slot;
  s8 *base;
  base = ((s8 *) (*D_80016000)) + 0x20;
  slot = base;
  handler = *((M2C_UNK (**)(M2C_UNK *, M2C_UNK)) (((s8 *) (*slot)) + 0x268));
  handler(&D_8001C048, 1);
}
