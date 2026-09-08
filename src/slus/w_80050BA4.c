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

/* Creates an owner and its companion object, flagging failed setup for cleanup. */
void *func_80050BA4(s32 context)
{
  void *owner;
  S_80050BA4_s1 *object;
  S_80050BA4_sub *state;
  void *resource;

  owner = func_8003FC64(0);
  if (owner == 0)
  {
    return 0;
  }
  object = func_8003FC64(0);
  if (object != 0)
  {
    state = (S_80050BA4_sub *) (((u8 *) object) + 0x20);
    state->field_0xA0 = owner;
    if (func_80050AF0(state, 0x11) != 0)
    {
      object->field_0xC = &object->field_0x78;
      state->field_0x64 = func_80050B7C(state->field_0x68);
      func_80050A00(state, (void *) context);
      object->field_0x10 = (void *) func_80050694;
      resource = func_8004FDE0((void *) 2);
      state->field_0x28 = resource;
      if (resource != 0)
      {
        func_8004E130();
        func_8004491C(object, (void *) func_8004CAA0);
        return owner;
      }
    }
    func_8004B248(&state->field_0x6c);
    object->field_0x1E |= 0x8000;
    D_800814A0_abs |= 0x8000;
  }
  return owner;
}
