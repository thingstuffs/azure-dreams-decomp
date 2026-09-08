#include "common.h"

#ifdef NON_MATCHING
#define FLAGS_PAGE ((u8 *)D_80082E60)
#define FLAGS_OFFSET 0
#define BASE_PAGE ((u8 *)&D_80083160)
#define BASE_OFFSET 0
#else
/* ADDR_ALIAS: retail materialises ONE %hi page base in $a1 and folds the %lo of
 * D_80082E60 into both the load and the store (words 99/102/112).  maspsx's
 * _fold_lo_into_accesses only collapses a %hi base reached through an INDEXED
 * derivation (`addu $D,$idx,$seed`), so the natural `&D_80082E60` spelling leaves
 * a real `addiu $a1,$a1,%lo` behind.  The page constant reproduces retail exactly. */
#define FLAGS_PAGE ((u8 *)0x80080000)
#define FLAGS_OFFSET 0x2E60
/* ADDR_ALIAS: retail splits the D_80083160 base into `lui $v1,%hi` (word 1) and
 * `addiu $v1,$v1,%lo` (word 4) and schedules the D_80082E6F load between them.
 * `&D_80083160` compiles to a single `la` macro, which GNU `as` expands as an
 * atomic pair -- no scheduler can interleave it.  The page constant emits the two
 * halves as separate instructions, which is what retail's assembler input had. */
#define BASE_PAGE ((u8 *)0x80080000)
#define BASE_OFFSET 0x3160
#endif
typedef struct 
{
  char pad0[8];
  int field8;
  char padC[4];
  int field10;
} S_8003D92C_80083160;
extern S_8003D92C_80083160 D_80083160;
extern u8 D_80082E6F[16];
extern u8 D_80080A84[16];
extern short D_80080ABC;
extern short D_80080ABE;
extern short D_80080A94[8];
extern short D_80080A98[8];
extern short D_80080A9C[8];
extern u8 D_80080A8A[16];
extern u8 D_80080A88[16];
extern u8 D_80080AA0[16];
extern int D_80082E60[4];
extern void func_8003F320(void);
extern int func_80053EF0(int);
extern void func_8003E758(void);
extern void func_80044618(int);
extern short func_80053DA8(int a0);
extern void func_80040AA0(int);
extern void func_80053DCC(short arg0);
extern void func_80053DF0(short);
extern void func_80053E14(short a0);
extern void func_8003D468(void);
int func_8003D92C(void)
{
  int a;
  int b;
  register int flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
  int saved;
  u8 *page = BASE_PAGE;
  register S_8003D92C_80083160 *p ASM_REG("$3");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
  ASM_KEEP_NV(page);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
  p = (S_8003D92C_80083160 *)(page + BASE_OFFSET);
  if (D_80082E6F[0] & 0x80)
  {
    return 0;
  }
  ASM_KEEP_NV(p);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
  a = p->field10;
  if (a & 0x100)
  {
    if (!(p->field8 & 0x800))
    {
      D_80080ABE = 1;
    }
  }
  else
    if (a & 0x800)
  {
    if (p->field8 & 0x100)
    {
      D_80080ABE = 1;
    }
    else
    {
      D_80080ABE = 0;
      D_80080ABC = 0;
      return 0;
    }
  }
  b = p->field8;
  if (!(b & 0x100))
  {
    D_80080ABE = 0;
    D_80080ABC = 0;
    return 0;
  }
  if (D_80080ABE != 0)
  {
    if (b & 0x800)
    {
      D_80080ABC += D_80080A84[0];
      if (D_80080ABC >= 0x169)
      {
        D_80080ABC = 0x168;
      }
    }
    else
    {
      D_80080ABC = 0;
    }
  }
  if ((0x78 / D_80080A84[0]) < D_80080ABC)
  {
    D_80080ABE = 0;
    D_80080ABC = 0;
 func_8003F320(); while (func_80053EF0(4) == 0x100) { func_8003E758();
      func_80044618(2);
    }

    func_80053DA8(0x74);
    while (func_80053EF0(4) != 0)
    {
      func_8003E758();
      func_80044618(2);
    }

    func_8003F320();
    func_80040AA0(3);
    {
      u8 *flags_base = FLAGS_PAGE;
      saved = D_80080A94[0];
      ASM_KEEP(flags_base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      flags = *(int *)(flags_base + FLAGS_OFFSET);
      D_80080A8A[0] = 0;
      D_80080A88[0] = 0;
      D_80080AA0[0] = 0;
      *(int *)(flags_base + FLAGS_OFFSET) = flags & ~2;
      func_80053DCC(saved);
    }
    func_80053DF0(D_80080A98[0]);
    func_80053E14(D_80080A9C[0]);
    func_80053DA8(0x7F);
    func_8003D468();
    D_80080A84[0] = 2;
    return 1;
  }
  return 0;
}
