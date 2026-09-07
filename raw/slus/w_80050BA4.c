#include "common.h"

typedef struct S_80050BA4_s1
{
  u8 pad00[0xC];
  void *field_0xC;
  void *field_0x10;
  u8 pad14[0x1E - 0x14];
  u16 field_0x1E;
  u8 pad20[0x78 - 0x20];
  u8 field_0x78;
} S_80050BA4_s1;

typedef struct S_80050BA4_sub
{
  u8 pad00[0x28];
  void *field_0x28;
  u8 pad2c[(0x64 - 0x28) - 4];
  void *field_0x64;
  void *field_0x68;
  u16 *field_0x6c;
  u8 pad70[0xA0 - 0x70];
  void *field_0xA0;
} S_80050BA4_sub;

extern void *func_8003FC64(s32 a0);
extern s32 func_80050AF0(void *a0, s32 a1);
extern void *func_80050B7C(void *a0);
extern void func_80050A00(void *a0, void *a1);
extern void *func_8004FDE0(void *a0);
extern void func_8004E130(void);
extern void func_8004491C(void *a0, void *a1);
extern void func_8004B248(u16 **a0);
extern void func_80050694(void *a0);
extern int func_8004CAA0(void *a0, int a1, void *a2);

/* Retail materializes a fresh %hi(D_800814A0) for the store after the |= load
 * destroyed the address register; cdk cc1 otherwise CSEs the address across
 * load+store. The absolute-bound section alias (LEAD-24 idiom, same cohort as
 * w_80050DA8/w_80051F58, same global) forces per-access lui. */
extern s32 D_800814A0_abs __attribute__((section(".data")));
__asm__(".set D_800814A0_abs, 0x800814A0");

void *func_80050BA4(s32 a0)
{
  void *s2;
  S_80050BA4_s1 *s1;
  S_80050BA4_sub *s0;
  void *v0;

  s2 = func_8003FC64(0);
  if (s2 == 0)
  {
    return 0;
  }
  s1 = func_8003FC64(0);
  if (s1 != 0)
  {
    s0 = (S_80050BA4_sub *) (((u8 *) s1) + 0x20);
    s0->field_0xA0 = s2;
    if (func_80050AF0(s0, 0x11) != 0)
    {
      s1->field_0xC = &s1->field_0x78;
      s0->field_0x64 = func_80050B7C(s0->field_0x68);
      func_80050A00(s0, (void *) a0);
      s1->field_0x10 = (void *) func_80050694;
      v0 = func_8004FDE0((void *) 2);
      s0->field_0x28 = v0;
      if (v0 != 0)
      {
        func_8004E130();
        func_8004491C(s1, (void *) func_8004CAA0);
        return s2;
      }
    }
    func_8004B248(&s0->field_0x6c);
    do { s1->field_0x1E |= 0x8000; D_800814A0_abs |= 0x8000; } while (0);
  }
  return s2;
}
