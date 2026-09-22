#include "common.h"
#include "m2c_compat.h"
/* Call the object's first virtual method. */
void func_800A34E0(void *obj)
{
  M2C_UNK (**vtable)();
  M2C_UNK (*handler)();
  vtable = (M2C_UNK (**)()) obj;
  handler = *vtable;
  handler();
}
