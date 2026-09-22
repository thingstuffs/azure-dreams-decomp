#include "common.h"
#include "m2c_compat.h"
/* Call the object's first virtual method. */
void func_800B6754(void *obj)
{
  (*((M2C_UNK (**)()) obj))();
}
