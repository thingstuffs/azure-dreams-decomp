#include "common.h"

typedef s32 M2C_UNK;
M2C_UNK func_800478B8();
s32 func_800644B8();
s32 func_80064584();
extern M2C_UNK D_800814A0;
void func_800241E4(void *arg0, void *arg1, M2C_UNK arg2)
{
  s32 temp_lo;
  void *new_var;
  void *page;
  void *temp_v1;
  temp_v1 = *((void **) (((s8 *) arg0) + 0));
  *((u16 *) (((s8 *) temp_v1) + 0x14)) = (u16) ((*((u16 *) (((s8 *) temp_v1) + 0x14))) + 1);
  *((u16 *) (((s8 *) arg0) + 4)) = (u16) ((*((u16 *) (((s8 *) arg0) + 4))) + 1);
  func_800478B8(arg2);
  *((s32 *) (((s8 *) arg1) + 0)) = (s32) ((*((s32 *) (((s8 *) arg1) + 0))) + ((func_80064584(*((s16 *) (((s8 *) arg0) + 0xA))) >> 4) * (((*((s16 *) (((s8 *) arg0) + 8))) - ((s16) (*((u16 *) (((s8 *) arg0) + 4))))) << 8)));
  temp_lo = (func_800644B8(*((s16 *) (((s8 *) arg0) + 0xA))) >> 4) * (((*((s16 *) (((s8 *) arg0) + 8))) - ((s16) (*((u16 *) (((s8 *) arg0) + 4))))) << 8);
  *((s32 *) (((s8 *) arg1) + 8)) = (s32) ((*((s32 *) (((s8 *) arg1) + 8))) + 0xFFFE0000);
  new_var = arg0;
  *((s32 *) (((s8 *) arg1) + 4)) = (s32) ((*((s32 *) (((s8 *) arg1) + 4))) + temp_lo);
  if (((s16) (*((u16 *) (((s8 *) new_var) + 4)))) > (*((s16 *) (((s8 *) new_var) + 6))))
  {
    *((u16 *) (((s8 *) new_var) + (-2))) = (u16) ((*((u16 *) (((s8 *) new_var) + (-2)))) | 0x8000);
    page = (void *) 0x80080000;
    ASM_KEEP(page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    *((s32 *) (((s8 *) page) + 0x14A0)) = (s32) ((*((s32 *) (((s8 *) page) + 0x14A0))) | 0x8000);
  }
}
/* MECHANISM: The seed preserves the 0x20 frame and the long-lived s1/s0 argument bases.
   A literal 0x80080000 page local held by ASM_KEEP emits the branch-delay lui in v1.
   Both flag RMW accesses use +0x14A0 from that base, closing all three addressing words. */
