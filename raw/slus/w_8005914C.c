#include "common.h"


#include "common.h"
typedef struct 
{
  s32 unk00;
  s32 unk04;
  u32 unk08;
  u8 pad0C[0x10 - 0x0C];
  s32 unk10;
  s32 unk14;
  u8 pad18[0x2C - 0x18];
  s32 unk2C;
  s32 unk30;
  u8 pad34[0x40 - 0x34];
  s32 unk40;
  s32 unk44;
  u8 pad48[0x4A - 0x48];
  u8 unk4A;
  u8 unk4B;
  u8 pad4C[0x50 - 0x4C];
} S_80085FA8;
typedef struct 
{
  u8 pad00[0x4D];
  u8 unk4D;
  u8 pad4E[0x9C - 0x4E];
} S_80084960;
extern S_80085FA8 D_80085FA8[];
extern S_80084960 D_80084960[];
extern s32 D_800869B4[3];
extern s32 D_800869B8[3];
#ifdef NON_MATCHING
#define D_800869B4_PAGE D_800869B4
#define D_800869B4_PAGE_INDEX 0
#else
#define D_800869B4_PAGE ((s32 *)0x80080000)
#define D_800869B4_PAGE_INDEX (0x69B4 / sizeof(s32))
#endif
extern void func_80056E10(s32 a0, s32 a1, s32 a2);
extern void func_80057948(s32 a0, s32 a1, s32 a2);
extern void func_80057A48(s32 a0, s32 a1, s32 a2);
extern void func_80057D20(s32 a0, s32 a1, s32 a2);
extern void func_8005845C(s32 a0, s32 a1);
extern void func_8005848C(s32 a0, s32 a1);
extern void func_80058494(s32 a0, s32 a1, s32 a2);
void func_8005914C(S_80085FA8 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
  register s32 chan ASM_REG("$11");
  u32 i;
  s32 count;
  S_80085FA8 *s;
  register S_80085FA8 *p ASM_REG("$13");
  register s32 a2copy ASM_REG("$10");
  p = arg0;
  chan = arg1 & 0xF;
  a2copy = arg2;
  switch (arg1 & 0xF0)
  {
    case 0x80:
      func_80057948(chan, a2copy & 0xFF, arg3 & 0xFF);
      return;

    case 0x90:
      if ((arg3 & 0xFF) != 0)
    {
      func_80056E10(chan, a2copy & 0xFF, arg3 & 0xFF);
    }
    else
    {
      func_80057948(chan, a2copy & 0xFF, 0);
    }
 do { return; } while (0);

    case 0xA0:
      func_80057A48(chan, a2copy & 0xFF, arg3 & 0xFF);
      return;

    case 0xB0:
      ASM_KEEP(p);
      if ((a2copy & 0xFF) == 0x63)
    {
      if ((arg3 & 0xFF) == 0x14)
      {
        if (D_800869B8[0] != 0)
        {
          register s32 *countPage ASM_REG("$12");
          countPage = D_800869B4_PAGE;
          if (countPage[D_800869B4_PAGE_INDEX] != 0)
          {
            s32 x0;
            s32 x1;
            s32 x2;
            s32 x3;
            s32 loopCount;
            register u8 x4 ASM_REG("$6");
            register s32 twenty ASM_REG("$14");
            i = 0;
            twenty = 0x14;
            s = D_80085FA8;
            do
            {
              x0 = *(volatile s32 *)&s->unk00;
              x1 = *(volatile s32 *)&s->unk10;
              x2 = *(volatile s32 *)&s->unk40;
              x3 = *(volatile s32 *)&s->unk2C;
              x4 = *(volatile u8 *)&s->unk4A;
              s->unk04 = x0;
              s->unk4B = x4;
              loopCount = countPage[D_800869B4_PAGE_INDEX];
              i++;
              s->unk08 = twenty;
              s->unk14 = x1;
              s->unk44 = x2;
              s->unk30 = x3;
              s++;
            }
            while (i < ((u32) loopCount));
          }
        }
        else
        {
          p->unk08 = 0x7F;
          p->unk04 = p->unk00;
        }
      }
      else
        if ((arg3 & 0xFF) == 0x1E)
      {
        if (p->unk08 != 0)
        {
          if (p->unk08 < 0x7FU)
          {
            p->unk08 = p->unk08 - 1;
          }
          if (D_800869B8[0] != 0)
          {
            register s32 *countPage ASM_REG("$12");
            countPage = D_800869B4_PAGE;
            if (countPage[D_800869B4_PAGE_INDEX] != 0)
            {
              s32 x0;
              s32 x1;
              s32 x2;
              s32 x3;
              s32 loopCount;
              register u8 x4 ASM_REG("$6");
              i = 0;
              s = D_80085FA8;
              do
              {
                x0 = *(volatile s32 *)&s->unk04;
                x1 = *(volatile s32 *)&s->unk14;
                x2 = *(volatile s32 *)&s->unk44;
                x3 = *(volatile s32 *)&s->unk30;
                x4 = *(volatile u8 *)&s->unk4B;
                s->unk00 = x0;
                s->unk4A = x4;
                loopCount = countPage[D_800869B4_PAGE_INDEX];
                i++;
                s->unk10 = x1;
                s->unk40 = x2;
                s->unk2C = x3;
                s++;
              }
              while (i < ((u32) loopCount));
            }
          }
          else
          {
            p->unk00 = p->unk04;
          }
        }
      }
    }
      if ((a2copy & 0xFF) == 6)
    {
      if (D_80084960[chan & 0xFF].unk4D == 0x14)
      {
        if (D_800869B8[0] != 0)
        {
          if (D_800869B4[0] != 0)
          {
            register s32 value ASM_REG("$5");
            register S_80085FA8 *broadcast;
            i = 0;
            value = arg3 & 0xFF;
            count = D_800869B4[0];
            broadcast = D_80085FA8;
            do
            {
              broadcast->unk08 = value;
              broadcast++;
              i++;
            }
            while (i < ((u32) count));
          }
        }
        else
        {
          p->unk08 = arg3 & 0xFF;
          return;
        }
      }
    }
      func_80057D20(chan, a2copy & 0xFF, arg3 & 0xFF);
      return;

    case 0xE0:
      func_80058494(chan, a2copy & 0xFF, arg3 & 0xFF);
      return;

    case 0xC0:
      func_8005845C(chan, a2copy & 0xFF);
      return;

    case 0xD0:
      func_8005848C(chan, a2copy & 0xFF);
      return;

  }

}
