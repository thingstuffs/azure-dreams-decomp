#include "common.h"
#include "m2c_compat.h"
extern void func_80017AC8(u8 *);
extern void *D_80016000;
extern u8 D_80019B08;
extern s32 D_80019B88;
void func_805D3B14(void)
{
  func_80017AC8(&D_80019B08);
  D_80019B88 = (*((s32 (**)(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *)) (((s8 *) (*((void **) (((s8 *) D_80016000) + 0x20)))) + 0x68)))(0, 0, 0, &D_80019B08);
 do { } while (0);
}
