#include "common.h"

#include "common.h"
extern s32 D_800814A8[4];
extern s32 D_800E3DF0[];
extern int func_80049280(int arg0);
extern int func_80021300(int a0);
extern int func_8002137C(int a0);
/* Resolves an indexed value and converts it unless its code is 2. */
int func_800492B0(int index)
{
  s32 value;
  s32 value_code;
  if (func_80049280(index))
  {
    ASM_KEEP(index);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    value = *((s32 *) (((u8 *) D_800814A8[0]) + 0x124));
  }
  else
  {
    value = D_800E3DF0[index];
  }
  value_code = func_80021300(value);
  if (value_code != 2)
  {
    value = func_8002137C(value_code);
  }
  return value;
}
