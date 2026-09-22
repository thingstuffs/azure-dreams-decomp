#include "common.h"
extern void *D_80016000;
/* True when the scene state's counter has reached the -64 threshold. */
s32 func_80614B88(void)
{
  s8 *slot;
 slot = ((s8 *) D_80016000) + 0x1C; return ((u32) (*((u32 *) (((s8 *) (*((void **) slot))) + 0xC)))) >= ((u32) (s32) -64);
}
