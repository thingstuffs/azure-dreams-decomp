#include "common.h"


#ifdef NON_MATCHING
#define ASM_REG(reg)
#define ASM_KEEP(var)   ((void)0)
#else
#define ASM_REG(reg)    asm(reg)
#define ASM_KEEP(var)   __asm__ __volatile__("" : "+r"(var))
#endif
typedef struct S_80084918
{
  s32 field0;
  s32 field4;
  s16 field8;
  s16 fieldA;
  s16 fieldC;
  s16 fieldE;
} S_80084918;
typedef struct S_80055E84
{
  u16 unk0;
  u8 pad2[0xE];
  u16 unk10;
  u16 unk12;
  u8 pad14[0x2D];
  u8 unk41;
  u8 unk42;
  s8 unk43;
  u8 unk44;
  u8 pad45[3];
  s32 unk48;
  s32 unk4C;
  u8 unk50;
  u8 unk51;
  u8 unk52;
  u8 pad53;
  s32 unk54;
  s32 unk58;
  u8 pad5c[0x10];
  s16 unk6C;
} S_80055E84;
extern S_80084918 D_80084918;
extern s16 D_80084920[8];
extern s32 D_80073740[];
extern s32 func_8005F134(S_80084918 *arg, S_80055E84 *arg1);
void func_80055E84(S_80055E84 *arg0)
{
  s32 t;
  s8 fac;
  s32 p;
  s8 n;
  s32 v;
  if (arg0->unk4C != 0)
  {
    if (arg0->unk42 != arg0->unk50)
    {
      arg0->unk42 = arg0->unk42 + 1;
    }
    else
    {
      if (arg0->unk44 >= arg0->unk51)
      {
        arg0->unk48 = arg0->unk4C;
      }
      else
      {
        if (arg0->unk44 != 0)
        {
          arg0->unk48 = arg0->unk48 + arg0->unk54;
        }
        else
        {
          arg0->unk48 = arg0->unk54;
        }
        arg0->unk44 = arg0->unk44 + 1;
      }
      arg0->unk43 = arg0->unk43 + arg0->unk52;
      arg0->unk41 = 0;
      n = arg0->unk43;
      if (n < 0)
      {
        register s32 a ASM_REG("$4");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
        s32 b;
        s32 x = -n;
        a = x << 1;
        b = a;
        if ((x << 25) < 0)
        {
          b = -a;
        }
        p = arg0->unk48 * (s8) b;
        if (p > 0)
        {
          p = -p;
        }
      }
      else
      {
        register s32 a ASM_REG("$4");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
        s32 b;
        s32 x = n;
        a = x << 1;
        b = a;
        if ((x << 25) < 0)
        {
          b = -a;
        }
        p = arg0->unk48 * (s8) b;
        if (p < 0)
        {
          p = -p;
        }
      }
      if (p != 0)
      {
        if (p < 0)
        {
          p = p + 0xFF;
        }
        arg0->unk58 = p >> 8;
      }
      else
      {
        arg0->unk58 = 0;
      }
    }
    if (arg0->unk6C != arg0->unk58)
    {
      arg0->unk6C = (u16) arg0->unk58;
      D_80084918.field4 = 0xF;
      D_80084918.field0 = D_80073740[arg0->unk0];
      v = arg0->unk10 + arg0->unk58;
      if (v < 0)
      {
        v = 0;
      }
      else
        if (v >= 0x4000)
      {
        v = 0x3FFF;
      }
      D_80084920[0] = v;
      v = arg0->unk12 + arg0->unk58;
      if (v < 0)
      {
        v = 0;
      }
      else
        if (v >= 0x4000)
      {
        v = 0x3FFF;
      }
      D_80084918.fieldA = v;
      D_80084918.fieldC = 0;
      D_80084918.fieldE = 0;
      func_8005F134(&D_80084918, arg0);
    }
  }
}
