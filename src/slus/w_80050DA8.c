#include "common.h"

typedef struct 
{
  u8 pad1E[0x1E];
  u16 flags1E;
} S_80050DA8_sub;
extern s32 D_80080B98;
extern s32 D_800814A0_abs __attribute__((section(".data")));
__asm__(".set D_800814A0_abs, 0x800814A0");
extern void func_80050CDC(void);
extern void func_8004FE78(void *arg0);
void func_80050DA8(u8 *a0)
{
  u8 *s0 = a0 + 0x20;
  s32 t_1c;
  void *t_28;
  S_80050DA8_sub *sub;
  if (a0 != 0)
  {
    *((s32 *) (s0 + 0x08)) = 2;
    t_1c = *((s32 *) (s0 + 0x1C));
    t_28 = *((void **) (s0 + 0x28));
    *((void (**)(void)) (s0 - 0x10)) = func_80050CDC;
    D_80080B98 = t_1c;
    func_8004FE78(t_28);
    sub = *((S_80050DA8_sub **) (s0 + 0xA0));
    D_800814A0_abs |= 0x8000;
    sub->flags1E |= 0x8000;
    *((void **) (s0 + 0x28)) = 0;
  }
}
