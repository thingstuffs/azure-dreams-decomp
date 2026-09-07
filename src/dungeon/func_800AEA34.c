#include "common.h"

typedef struct Entity800B4194
{
  u8 pad00[0x1C];
  u32 flags1C;
  u8 pad20[8];
  u8 value28;
  u8 pad29[0x1F];
  u8 state48;
  u8 state49;
  u8 state4A;
  u8 state4B;
  u8 pad4C[0x18];
  s16 value64;
} Entity800B4194;
typedef struct Context800B4194
{
  u8 pad00[0x4C];
  u8 *event4C;
  u8 pad50[0x14];
  u16 value64;
} Context800B4194;
extern s32 D_80012090[];
extern s16 D_8008146C[];
extern u8 D_800892C4[];
extern u8 D_800892C8[];
extern u8 D_800E0BC7[];
extern u8 D_800E0BDC[];
extern u8 D_800E0BF3[];
extern u8 D_800E0C09[];
extern u8 D_800E0C1D[];
extern volatile u8 *D_800E3D7C[];
extern s16 func_80042900(Entity800B4194 *, s32);
extern u8 *func_800990FC(void);
extern u8 *func_80099194(u8 *, u8 *);
extern u8 *func_80099290(u8 *);
extern u8 *func_80099734(Entity800B4194 *, u8 *);
extern s16 func_800A48F0(Entity800B4194 *, s32, s32);
extern void func_800A56E0(s32);
extern void func_800A5720(u8 *);
extern s32 func_800A6D30(void);
extern s32 func_800A6DA4(s32, s32);
extern s16 func_800A9400(s16);
extern s32 func_800B4328(u8 *);
extern s32 func_800B4340(void);
extern s32 func_800B44E0(s32, s32);
extern s32 func_800B45A4(u8 *);
extern s32 func_800B45BC(void);
extern s32 func_800B45C0(void);
extern void func_800B4C7C(s32, void *, s32, s32);
extern s32 func_800C8980(Entity800B4194 *, s32, s32);
extern s32 func_800C8C1C(Entity800B4194 *, s32, s32);
s32 func_800B4194(s16 arg0, Entity800B4194 *entity, Context800B4194 *context)
{
  Entity800B4194 *entityp = entity;
  Context800B4194 *contextp;
  s32 blocked;
  s32 total;
  s32 flag;
  u8 *saved;
  u8 *text;
  s32 code;
  s32 delta;
  s16 amount;
  s16 range;
  u8 *event;
  s16 value;
  ASM_KEEP_NV(entityp);   /* MATCH pin: retail schedule: same instructions, different order without it */
  contextp = context;
  ASM_KEEP_NV(contextp);   /* MATCH pin: retail schedule: same instructions, different order without it */
  code = func_800A9400(arg0);
  total = entityp->value28 + entityp->value64;
  flag = total < 1;
  ASM_KEEP_NV(flag);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
  blocked = flag;
  ASM_KEEP_NV(blocked);   /* MATCH pin: load-bearing for the whole function shape */
  if (code == 0)
  {
    goto common;
  }
  if (code == 0x12)
  {
    goto mode18;
  }
  if (code < 0x13)
  {
    if (code == 0x10)
    {
      goto mode16;
    }
    return func_800B4340();
  }
  if (code == 0x13)
  {
    goto mode19;
  }
  if (code == 0x15)
  {
    goto mode21;
  }
  return func_800B4340();
  mode19:
  mode16:
  {
    s32 modeTest = blocked;
    ASM_KEEP_NV(modeTest);   /* MATCH pin: retail delay-slot fill depends on it */
    if (modeTest)
    {
      goto common;
    }
    value = func_800A6D30();
    range = (D_800E3D7C[0][0xA9] >> 2) + 0x10;
    if (func_800C8C1C(entityp, D_800E3D7C[0][0xA9] + 0x80, range + (value & 3)) == 0)
    {
      goto common;
    }
    saved = func_800990FC();
    ASM_KEEP_NV(saved);   /* MATCH pin: retail delay-slot fill depends on it */
    text = func_80099194(D_800E0BC7, saved);
    text = func_80099734(entityp, text);
    return func_800B4328(D_800892C4);
  }


  mode18:
  mode21:
  {
    s32 modeTest = blocked;
    ASM_KEEP_NV(modeTest);   /* MATCH pin: retail delay-slot fill depends on it */
    if (modeTest || (entityp->flags1C & 0x20))
    {
      goto common;
    }
    value = func_800A6D30();
    range = (D_800E3D7C[0][0xA9] >> 2) + 2;
    if (func_800C8980(entityp, D_800E3D7C[0][0xA9] + 0x80, range + (value & 3)) == 0)
    {
      goto common;
    }
    saved = func_800990FC();
    text = func_80099194(D_800E0BDC, saved);
    text = func_80099734(entityp, text);
    text = func_80099194(D_800892C8, text);
    text = func_80099290(text);
    func_800A5720(saved);
  }


  common:
  event = contextp->event4C;

  if (event == 0)
  {
    return 0;
  }
  if (event[1] != 0x10)
  {
    return 0;
  }
  value = event[0];
  if (value == 4)
  {
    goto event4;
  }
  if (value < 5)
  {
    if (value == 3)
    {
      goto event3;
    }
    return func_800B45C0();
  }
  if (value == 5)
  {
    goto event5;
  }
  if (value == 9)
  {
    goto event9;
  }
  return func_800B45C0();
  event3:
  {
  s32 eventZero = 0;
  ASM_KEEP(eventZero);   /* MATCH pin: retail delay-slot contents depend on it */
  delta = -(((s16) (*((u16 *) (((u8 *) entityp) + 0x64)))) >> 3);

  amount = delta;
  if (amount == 0)
  {
    return 0;
    func_800B45C0();
  }
  contextp->value64 += delta;
  func_800B4C7C(0x10, contextp, amount, 1);
  return 0;
  }
  event4:
  {
    s32 eventTest = blocked;
    ASM_KEEP_NV(eventTest);   /* MATCH pin: retail delay-slot fill depends on it */
    if (eventTest || (entityp->flags1C & 0x20))
    {
      return 0;
    }
    if (func_800C8980(entityp, 8, 8) == 0)
    {
      return 0;
    }
    func_800A56E0(0x700);
    saved = func_800990FC();
    ASM_KEEP_NV(saved);   /* MATCH pin: retail delay-slot fill depends on it */
    text = func_80099194(D_800E0BF3, saved);
    text = func_80099734(entityp, text);
    return func_800B45A4(D_800892C4);
  }

  event5:
  {
    s32 eventTest = blocked;
    ASM_KEEP_NV(eventTest);   /* MATCH pin: retail delay-slot fill depends on it */
    if (!eventTest)
    {
      return 0;
    }
    saved = &entityp->state48;
    if (saved[1] != 0)
    {
      return 0;
    }
    if ((func_800A6D30() & 3) != 0)
    {
      return 0;
    }
    saved[1] = 0xE;
    if ((D_80012090[0] != 2) && (D_8008146C[0] < 0xC))
    {
      register s32 low ASM_REG("$4") = 0x10;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
      s32 high = 0x18;
      ASM_KEEP_NV(low);   /* MATCH pin: retail schedule: same instructions, different order without it */
      ASM_KEEP_NV(high);   /* MATCH pin: retail schedule: same instructions, different order without it */
      saved[0] = 1;
      return func_800B44E0(low, high);
    }
    if ((D_80012090[0] != 2) && (D_8008146C[0] < 0x16))
    {
      register s32 low ASM_REG("$4") = 0x50;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
      register s32 high ASM_REG("$5") = 0x78;   /* MATCH pin: retail delay-slot fill depends on it */
      saved[0] = 2;
      ASM_USE(saved);   /* MATCH pin: retail delay-slot fill depends on it */
      saved[2] = func_800A6DA4(low, high);
      saved[3] = 0;
      return func_800B45BC();
    }
    entityp->state48 = 3;
    saved[2] = func_800A6DA4(0x10, 0x18);
    saved[3] = 1;
    return func_800B45BC();
  }

  event9:
  {
  s32 eventZero = 0;
  s32 eventTest;
  ASM_KEEP(eventZero);   /* MATCH pin: retail delay-slot contents depend on it */
  eventTest = blocked;
  ASM_KEEP_NV(eventTest);   /* MATCH pin: retail delay-slot fill depends on it */

  if (eventTest)
  {
    return 0;
  }
  if (func_80042900(entityp, 6) != 0)
  {
    return 0;
  }
  if ((func_800A6D30() & 7) != 0)
  {
    return 0;
  }
  if (func_800A48F0(entityp, 6, 0x10) < 0)
  {
    return 0;
  }
  func_800A56E0(0x700);
  saved = func_800990FC();
  text = func_80099194(D_800E0C09, saved);
  text = func_80099734(entityp, text);
  text = func_80099194(D_800E0C1D, text);
  text = func_80099290(text);
  func_800A5720(saved);
  return 0;
  }
}
