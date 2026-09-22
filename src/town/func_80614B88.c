#include "common.h"
extern void *D_80016000;
s32 func_80614B88(void)
{
  unsigned int new_var;
  s8 *new_var2;
 new_var = 0xFFFFFFC0U; new_var2 = ((s8 *) D_80016000) + 0x1C; return ((u32) (*((u32 *) (((s8 *) (*((void **) new_var2))) + 0xC)))) >= ((u32) (s32) -64);
}
