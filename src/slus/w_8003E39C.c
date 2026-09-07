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
  register S_80083968 *tbl ASM_REG("$6");   /* MATCH pin: slus-diff */
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

  {
    register u32 page ASM_REG("$2") = 0x80080000;   /* MATCH pin: slus-diff */
    ASM_KEEP_NV(page);   /* MATCH pin: slus-diff */
    tbl = (S_80083968 *)(page + 0x3968);
  }
  kff = 0xFF;
  idx = D_800814D1;
  (&tbl[idx])->unk00 = (u8) arg0;
  (&tbl[idx])->unk04 = arg1;
  (&tbl[idx])->unk08[15] = 0;
  if ((arg0 & 0xFF) == kff)
  {
    register S_80083968 *e1 ASM_REG("$2");   /* MATCH pin: slus-diff */
    ASM_KEEP_NV(tbl);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    e1 = &tbl[idx];
    *((s32 *) e1->unk08) = arg2;
  }
  else
    if (arg2 == 1)
  {
    (&tbl[idx])->unk08[15] = kff;
  }
  else
  {
    register u8 *e3 ASM_REG("$2");   /* MATCH pin: slus-diff */
    ASM_KEEP_NV(tbl);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    e3 = (u8 *) tbl + 8;
    if (arg2 != 0)
    {
      e3 = (u8 *) (idx * 24 + (u32) e3);
      *((S_8003E39C_blk16 *) e3) = *((S_8003E39C_blk16 *) arg2);
    }
  }
  {
    register s32 off ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    off = idx * 24;
    D_800814D1 = (D_800814D1 + 1) & 0x1F;
    ASM_SCHED_BARRIER();   /* MATCH pin: slus-diff */
    return (S_80083968 *) ((u8 *) D_80083968 + off);
  }
}
