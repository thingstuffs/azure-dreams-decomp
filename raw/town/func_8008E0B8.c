#include "common.h"

typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
M2C_UNK func_80033C1C();
M2C_UNK func_80033D08();
M2C_UNK func_800375C0();
M2C_UNK func_8003DB94(void *, M2C_UNK *, s32);
M2C_UNK func_8004491C();
M2C_UNK func_8008B8DC();
M2C_UNK func_8008B914();
extern M2C_UNK D_80033D54;
extern M2C_UNK D_80037714;
extern M2C_UNK D_800794AC;
extern s32 D_80082ABC;
extern M2C_UNK D_8008B9D8;
extern M2C_UNK D_8008BA00;
extern s32 D_800CFB74[];
extern u8 D_800CFC38[];
extern s32 D_800CFC44[];
void func_8008B818(s32 arg0, s32 *arg1, void *arg2, void *arg3)
{
  s32 temp_a1;
  s32 var_a1;
  void *temp_s0;
  void *temp_s2;
  void *temp_s4;
  s32 *temp_table;
  s32 *new_var;
  s32 *temp_table2;
  register s32 *temp_index_ptr ASM_REG("$2");
  register void *temp_s3 ASM_REG("$19");
  temp_s3 = arg3;
  *((M2C_UNK **) (((s8 *) arg2) + 0x10)) = &D_8008B9D8;
  func_8004491C(arg2, &D_80033D54);
  var_a1 = 0;
  temp_s4 = *((void **) (((s8 *) arg2) + 8));
  temp_s2 = *((void **) (((s8 *) arg2) + 0xC));
  temp_s0 = arg2 + 0x20;
  if (arg1 != 0)
  {
    var_a1 = *arg1;
  }
  func_80033C1C(temp_s3, var_a1);
  {
    register s32 temp_two ASM_REG("$2");
    temp_two = 2;
    temp_table = D_800CFB74;
    *((void **) (((s8 *) arg2) + 0x20)) = temp_s3;
    *((s32 *) (((s8 *) temp_s3) + 0x60)) = temp_two;
    ASM_KEEP(temp_two);
    ASM_KEEP(temp_table);
  }
  *((s32 *) (((s8 *) temp_s0) + 4)) = 0;
  *((s16 *) (((s8 *) temp_s0) + 0x66)) = arg0;
  temp_index_ptr = temp_table - (-arg0);
  ASM_KEEP(temp_index_ptr);
  temp_a1 = *temp_index_ptr;
  if (temp_a1 != 0)
  {
    register u32 page ASM_REG("$2");
    *((M2C_UNK **) (((s8 *) temp_s0) + 8)) = &D_80037714;
    func_800375C0(temp_s0, temp_a1);
    page = 0x00800000;
    ASM_PAGEBASE_PIN(page);
    func_8008B8DC();
    return;
  }
  *((M2C_UNK **) (((s8 *) temp_s0) + 8)) = 0;
  ASM_KEEP(temp_s0);
  *((s16 *) (((s8 *) temp_s0) + 0x60)) = 0;
  *((s32 *) (((s8 *) temp_s2) + 0xC)) = 0x808080;
  if (((u32) (arg0 - 9)) < 2U)
  {
    func_8003DB94(temp_s2, &D_800794AC, 0);
    func_8008B914();
    return;
  }
  *((s32 *) (((s8 *) temp_s2) + 8)) = 0;
  ASM_CLOBBER("$0");
  if (arg0 == 0)
  {
    *((s16 *) (((s8 *) temp_s4) + 2)) = 0x20;
    *((s16 *) (((s8 *) temp_s4) + 6)) = -0x20;
    *((s16 *) (((s8 *) temp_s4) + 0xA)) = 0x200;
  }
  if (arg0 == 0xA)
  {
    *((s32 *) (((s8 *) temp_s0) + 0x74)) = 0;
    D_80082ABC = (s32) (*(*((u8 **) (((s8 *) temp_s0) + 0x7C))));
  }
  *((M2C_UNK **) (((s8 *) temp_s0) + 0x68)) = &D_8008BA00;
  new_var = D_800CFC44;
  temp_table2 = new_var;
  *((s16 *) (((s8 *) temp_s0) + 0x64)) = (s16) ((s8) D_800CFC38[arg0]);
  ASM_CLOBBER("$4");
  *((s32 *) (((s8 *) temp_s0) + 0x6C)) = temp_table2[arg0];
  ASM_KEEP(temp_table2);
  if (arg0 == 9)
  {
    func_80033D08(temp_s0);
  }
  ASM_KEEP(temp_s3);
}
