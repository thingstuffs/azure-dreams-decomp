#include "common.h"

#include "common.h"

typedef struct S_80080A86
{
  u8 val;
  u8 pad[8];
} S_80080A86;
extern S_80080A86 D_80080A86;

typedef struct S_800814A0
{
  volatile s32 val;
  s32 pad[2];
} S_800814A0;
extern S_800814A0 D_800814A0;
extern s32 D_800814A0_store;
__asm__(".set D_800814A0_store, 0x800814A0");

typedef struct S_800400B8_D80083160
{
  u8 pad_00[0x18];
  u8 field_18[0x20 - 0x18];
  u8 field_20[0x1DC - 0x20];
  s32 field_1DC;
} S_800400B8_D80083160;
extern S_800400B8_D80083160 D_80083160;

extern void func_80046884(void *a0, void *a1, s32 a2);
extern void func_8003BFE4(void);
extern void func_80040190(void);
extern void func_800401FC(void);
extern void func_8004027C(void);
extern void func_8004D70C(void);
extern void func_800AC3EC(void);
extern void func_800AC4C4(void);
extern void func_800402F4(void);
extern void func_80044B48(void);

/* Runs node callbacks, removes flagged nodes, and updates movement and drawing state. */
void func_800400B8(void)
{
  S_800400B8_D80083160 *state = &D_80083160;
  s32 mode;
  if ((D_80080A86.val == 0) && (state->field_1DC != 0))
  {
    func_80046884(state->field_18, state->field_20, 0);
    func_8003BFE4();
  }
  func_80040190();
  if (D_800814A0.val & 0x8000)
  {
    func_800401FC();
  }
  __asm__ __volatile__("");
  mode = D_80080A86.val;
  D_800814A0_store = 0;
  if (mode == 0)
  {
    func_8004027C();
    func_8004D70C();
    if (state->field_1DC != 0)
    {
      func_800AC3EC();
      func_800AC4C4();
    }
  }
  func_800402F4();
  func_80044B48();
}
