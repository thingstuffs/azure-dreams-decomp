#include "common.h"

#include "common.h"
extern s32 D_800814A8[4];
extern s32 D_800E3DF0[];
extern int func_80049280(int arg0);
extern int func_80021300(int a0);
extern int func_8002137C(int a0);
int func_800492B0(int arg0)
{
  s32 v1;
  s32 ret;
  if (func_80049280(arg0))
  {
    ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    v1 = *((s32 *) (((u8 *) D_800814A8[0]) + 0x124));
  }
  else
  {
    v1 = D_800E3DF0[arg0];
  }
  ret = func_80021300(v1);
  if (ret != 2)
  {
    v1 = func_8002137C(ret);
  }
  return v1;
}
