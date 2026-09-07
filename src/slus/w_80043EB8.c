#include "common.h"

#include "common.h"

typedef struct S_80083160_ctx
{
  u8 pad[0x8AC];
  s32 ot[9];
  void *cur;
} S_80083160_ctx;
extern S_80083160_ctx *D_80083160[3];
extern u8 D_801C9E40[];
typedef struct S_80081480
{
  s32 field_0;
  s8 pad[8];
} S_80081480;
typedef struct S_8008148C
{
  s32 field_0;
  s8 pad[8];
} S_8008148C;
extern S_80081480 D_80081480;
extern S_8008148C D_8008148C;
extern u8 D_80080A84[16];
extern u8 D_80080A85[16];
extern void PutDispEnv(void *a0);
extern void PutDrawEnv(void *a0);
extern void DrawOTag(s32 *a0);
extern void ClearOTagR(s32 *a0, s32 a1);
extern void DrawSync(s32 a0);
extern void VSync(s32 a0);
extern void func_800411AC(void);
extern void func_80048B28(void);
extern void func_8003E758(void);
extern void func_800542BC(void);
extern void func_8003E2D8(void);
extern void func_8003F6F4(void);
extern void func_800400B8(void);
void func_80043EB8(void)
{
  void *next;
  s32 copied;
  u32 suppress;
  u32 sync;
#ifdef NON_MATCHING
  u8 *copy_base;
#else
  register u8 *copy_base ASM_REG("$1");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
#endif

  PutDispEnv(((u8 *) D_80083160[0]) + 0x5C);
  PutDrawEnv(D_80083160[0]);
  DrawOTag(&D_80083160[0]->ot[8]);
  func_8003E758();
  func_800542BC();
  copied = D_8008148C.field_0;
#ifdef NON_MATCHING
  copy_base = (u8 *)&D_80081480 - 0x1480;
#else
  copy_base = (u8 *)0x80080000;
#endif
  *(volatile s32 *)(copy_base + 0x1480) = copied;
  func_800411AC();
  func_8003E2D8();
  next = D_801C9E40;
  if (D_80083160[0] == ((S_80083160_ctx *) next))
  {
    next = next + 0x108D4;
  }
  else
  {
    next = D_801C9E40;
  }
  D_80083160[0] = (S_80083160_ctx *) next;
  ClearOTagR((s32 *) (((u8 *) next) + 0x70), 0x218);
  D_80083160[0]->cur = ((u8 *) D_80083160[0]) + 0x8D4;
  func_8003F6F4();
  func_800400B8();
  func_80048B28();
  DrawSync(0);
  suppress = D_80080A85[0];
  if (suppress == 0)
  {
    ASM_KEEP(suppress);   /* MATCH pin: slus-diff */
#ifdef NON_MATCHING
    sync = D_80080A84[0];
#else
    sync = 0x80080000;
    sync = *(u8 *)(sync + 0xA84);
#endif
    VSync((sync != 1) ? (2) : (0));
  }
}
