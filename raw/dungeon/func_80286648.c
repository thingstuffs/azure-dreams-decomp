#include "common.h"

extern s8 D_80012D52;

void func_80019648(void)
{
  s32 index;
  u8 *base;
  u8 *entry;

  index = D_80012D52;
  
  if (index >= 0)
  {
    base = (u8 *)0x800121E8;
    
    index *= 4;
    
    entry = (u8 *)((u32)index + (u32)base);
    
    if (*entry == 2)
    {
      *entry = 0x39;
    }
  }
}

/* MECHANISM: Frameless leaf; split and pin index=$v0, literal page base=$v1,
   and entry=$a0 so their live ranges reproduce retail. The absolute base
   selects lui/ori; in-place index *= 4 preserves index-first addu order. */
