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
/* Starts the fade callback, releases the attachment, and sets global and child flags. */
void func_80050DA8(u8 *object)
{
  u8 *object_data = object + 0x20;
  s32 saved_value;
  void *attachment;
  S_80050DA8_sub *child;
  if (object != 0)
  {
    *((s32 *) (object_data + 0x08)) = 2;
    saved_value = *((s32 *) (object_data + 0x1C));
    attachment = *((void **) (object_data + 0x28));
    *((void (**)(void)) (object_data - 0x10)) = func_80050CDC;
    D_80080B98 = saved_value;
    func_8004FE78(attachment);
    child = *((S_80050DA8_sub **) (object_data + 0xA0));
    D_800814A0_abs |= 0x8000;
    child->flags1E |= 0x8000;
    *((void **) (object_data + 0x28)) = 0;
  }
}
