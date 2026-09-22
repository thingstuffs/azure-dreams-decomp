#include "common.h"
#include "m2c_compat.h"
/* Call the object's first virtual method. */
void func_800A32C8(void *obj)
{
  M2C_UNK (*handler)();
  handler = *((M2C_UNK (**)()) obj);
  handler();
}
