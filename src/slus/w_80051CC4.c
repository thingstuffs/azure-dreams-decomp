#include "common.h"

#include "common.h"
typedef struct S_80071A68
{
  s32 field_0x00;
} S_80071A68;
extern S_80071A68 D_80071A68[];
extern u32 D_800814A0;
typedef struct S_80051CC4_Owner
{
  u8 unk00[0x6];
  u16 field_0x06;
  u8 unk08[0xC];
  u32 field_0x14;
} S_80051CC4_Owner;
typedef struct S_80051CC4_Sub
{
  S_80051CC4_Owner *owner;
  s16 field_0x04;
  s16 field_0x06;
  u8 pad08[2];
  s16 field_0x0A;
  s16 field_0x0C;
} S_80051CC4_Sub;
typedef struct S_80051CC4_Ptr
{
  u8 pad0[8];
  s32 field_0x08;
  u8 field_0x0C;
  u8 field_0x0D;
  u8 field_0x0E;
} S_80051CC4_Ptr;
void func_80051CC4(S_80051CC4_Sub *a0, void *a1_unused, S_80051CC4_Ptr *a2)
{
  u8 *usedPage;
  u16 newField6 = a0->field_0x06 + 1;
  s32 mode = a0->field_0x04;
  u16 origField4 = *((volatile u16 *) (&a0->field_0x04));
  u16 resetVal;
  u32 used;
  a0->field_0x06 = newField6;
  switch (mode)
  {
    case 0:
      if (a0->field_0x0C != 0)
    {
      resetVal = a0->field_0x04;
      a0->field_0x0C = 0;
      goto reset_bump;
    }
      break;

    case 1:
    {
      u8 val = a2->field_0x0E + 4;
      a2->field_0x0E = val;
      a2->field_0x0D = val;
      a2->field_0x0C = val;
    }
      if (a0->field_0x06 < 0x20)
    {
      break;
    }
      resetVal = a0->field_0x04;
      reset_bump:
    do { a0->field_0x06 = 0; } while (0);

      a0->field_0x04 = resetVal + 1;
      break;

    case 2:
      if (((s16) newField6) >= 0x3F)
    {
      a0->field_0x04 = origField4 + 1;
      a0->field_0x06 = 0;
    }
      break;

    case 3:
    {
      u8 val = a2->field_0x0E - 4;
      a2->field_0x0E = val;
      a2->field_0x0D = val;
      a2->field_0x0C = val;
    }
      if (a0->field_0x06 < 0x20)
    {
      break;
    }
    {
      s16 idx = a0->field_0x0A + 1;
      a0->field_0x0A = idx;
      if (idx != 7)
      {
        idx = idx % 7;
        a0->field_0x0A = idx;
        a2->field_0x08 = (*(&D_80071A68[idx])).field_0x00;
        a0->field_0x04 = 0;
        a0->field_0x06 = 0;
        return;
      }
    }
      goto shared_end;

    default:
      a2->field_0x0E = 0;
      a2->field_0x0D = 0;
      a2->field_0x0C = 0;
      shared_end:
    a0->owner->field_0x14 = 0;

      a0->owner->field_0x06 = a0->owner->field_0x06 + 1;
      *((u16 *) (((u8 *) a0) - 2)) |= 0x8000;
      used = D_800814A0;
      
      used |= 0x8000;
      
      usedPage = (u8 *) 0x80080000;
      
      *((u32 *) (usedPage + 0x14A0)) = used;
      
      break;

  }

}
