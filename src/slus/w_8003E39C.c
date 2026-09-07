#include "common.h"
typedef struct S_80083968
{
  u8 unk00;
  u8 pad1[3];
  s32 unk04;
  u8 unk08[16];
} S_80083968;
extern S_80083968 D_80083968[32];
extern u8 D_800814D1;
extern void func_8003E758(void);
typedef struct
{
  u8 b[16];
} S_8003E39C_blk16;
S_80083968 *func_8003E39C(s16 arg0, s32 arg1, s32 arg2)
{
  S_80083968 *e;
  u8 idx;
  s32 kff;
  u8 *hdr;
  u8 *hdr2;
  hdr = (u8 *) (&D_800814D1);
  if (((D_800814D1 + 1) & 0x1F) == hdr[-1])
  {
    hdr2 = hdr;
    do
    {
      func_8003E758();
    }
    while (((D_800814D1 + 1) & 0x1F) == hdr2[-1]);
  }

  kff = 0xFF;
  idx = D_800814D1;
  ;
  (&D_80083968[idx])->unk00 = (u8) arg0;
  (&D_80083968[idx])->unk04 = arg1;
  (&D_80083968[idx])->unk08[15] = 0;
  if ((arg0 & 0xFF) == kff)
  {
    *((s32 *) (&D_80083968[idx])->unk08) = arg2;
  }
  else
    if (arg2 == 1)
  {
    (&D_80083968[idx])->unk08[15] = kff;
  }
  else
    if (arg2 != 0)
  {
    *((S_8003E39C_blk16 *) (&D_80083968[idx])->unk08) = *((S_8003E39C_blk16 *) arg2);
  }
  {
    register s32 off ASM_REG("$3");   /* MATCH pin: slus-diff */
    off = idx * 24;
    D_800814D1 = (D_800814D1 + 1) & 0x1F;
    return (S_80083968 *) ((u8 *) D_80083968 + off);
  }
}
