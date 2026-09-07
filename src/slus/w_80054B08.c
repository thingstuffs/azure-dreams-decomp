#include "common.h"
typedef struct S_800847D0
{
  u32 flags1;
  u32 flags2;
  u32 field8;
  u32 fieldC;
  volatile u32 field10;
  volatile u32 field14;
  u32 field18;
  s16 field1C;
  s16 field1E;
  s16 field20;
  s16 field22;
  u8 pad24[2];
  s16 field26;
  u8 field28;
  u8 pad29[7];
  s8 field30;
  s8 field31;
  s8 field32;
  s8 field33;
} S_800847D0;
typedef struct S_80084858
{
  void (*field0)(void);
  s32 field4;
  s16 field8;
  s16 fieldA;
  s32 fieldC;
  s16 field10;
  s16 field12;
  s16 field14;
  s16 field16;
  s16 field18;
} S_80084858;
typedef struct S_80084864
{
  s32 v;
  u8 pad4[8];
} S_80084864;
extern S_800847D0 D_800847D0;
extern S_80084858 D_80084858;
extern S_80084864 D_80084864;
extern int *func_8003F534(void);
extern int func_80054AF0(int arg0);
extern void func_80054C58(void);
extern void func_80054CD4(void);
extern void func_80054E00(s32 arg0);
void func_80054B08(s32 arg0)
{
  s32 msg = arg0 & 0xF000;
  switch (msg)
  {
    case 0:
    {
      register S_800847D0 *status ASM_REG("$7");   /* MATCH pin: slus-diff */
      register u32 mask ASM_REG("$6");   /* MATCH pin: slus-diff */
      u16 t1;
      u32 t2;
      register u32 t3 ASM_REG("$4");   /* MATCH pin: slus-diff */
      int *p;
      int a1;
      u8 high2;
      u8 high3;
      u32 flags;
      p = func_8003F534();
      mask = 0xFF0000;
      ASM_KEEP(mask);   /* MATCH pin: slus-diff */
      t1 = *((u16 *) p);
      status = &D_800847D0;
      status->field1C = t1;
      a1 = p[1];
      ASM_SCHED_BARRIER();   /* MATCH pin: slus-diff */
      t2 = p[2];
      mask |= 0xFFFF;
      status->field10 = t2;
      t3 = p[3];
      high2 = (u8) (t2 >> 24);
      t2 = t2 & mask;
      status->field10 = t2;
      t2 = t2 - 0x20;
      t2 = t2 + a1;
      status->field31 = high2;
      status->field10 = t2;
      status->field18 = 0;
      high3 = (u8) (t3 >> 24);
      status->field14 = t3;
      t3 = t3 & mask;
      status->field14 = t3;
      t3 = t3 + 0x20;
      status->field33 = high3;
      flags = D_800847D0.flags1;
      t3 = t3 + a1;
      *(u32 *) &status->field14 = t3;
      if (flags & 0x400)
      {
        D_800847D0.flags1 = flags | 0x4000;
        D_80084864.v = 2;
        break;
      }
      if (status->flags2 & 0x200)
      {
        break;
      }
      {
        S_80084858 *ts0 = &D_80084858;
        s16 x = (s16) t1;
        int r;
        ts0->field4 = 0;
        r = func_80054AF0(x);
        ts0->field8 = r;
        ts0->fieldA = r;
      }
      func_80054C58();
      func_80054CD4();
      break;
    }

    case 0x1000:
      func_80054E00(0x74);
      break;

    case 0x2000:
      func_80054E00(0xE4);
      break;

    case 0x4000:
      func_80054E00(0xF4);
      break;

  }

}
