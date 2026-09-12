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
extern void func_800B4C7C(s32, void *, s32, s32);
extern s32 func_800C8980(Entity800B4194 *, s32, s32);
extern s32 func_800C8C1C(Entity800B4194 *, s32, s32);
s32 func_800B4194(s16 arg0, Entity800B4194 *entity, Context800B4194 *context)
{
  Entity800B4194 *entityp = entity;
  Context800B4194 *contextp;
  s16 blocked;
  s32 total;
  s32 flag;
  u8 *saved;
  u8 *text;
  s16 code;
  s32 delta;
  s16 amount;
  s16 range;
  u8 *event;
  s16 value;
  ASM_KEEP_NV(entityp);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  contextp = context;
  ASM_KEEP_NV(contextp);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  code = func_800A9400(arg0);
  total = entityp->value28 + entityp->value64;
  flag = total < 1;
  blocked = flag;
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
    goto common;
  }
  if (code == 0x13)
  {
    goto mode19;
  }
  if (code == 0x15)
  {
    goto mode21;
  }
  goto common;
  mode19:
  mode16:
  {
    s32 modeTest = blocked;
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
       /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    text = func_80099194(D_800E0BC7, saved);
    text = func_80099734(entityp, text);
    text = func_80099194(D_800892C4, text);
    text = func_80099290(text);
    func_800A5720(saved);
    goto common;
  }


  mode18:
  mode21:
  {
    s32 modeTest = blocked;
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
    return 0;
  }
  if (value == 5)
  {
    goto event5;
  }
  if (value == 9)
  {
    goto event9;
  }
  return 0;
  event3:
  {
  s32 eventZero = 0;
     /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
  delta = -(((s16) (*((u16 *) (((u8 *) entityp) + 0x64)))) >> 3);

  amount = delta;
  if (amount == 0)
  {
    return 0;
  }
  contextp->value64 += delta;
  func_800B4C7C(0x10, contextp, amount, 1);
  return 0;
  }
  event4:
  {
    s32 eventTest = blocked;
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
       /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    text = func_80099194(D_800E0BF3, saved);
    text = func_80099734(entityp, text);
    text = func_80099194(D_800892C4, text);
    text = func_80099290(text);
    func_800A5720(saved);
    return 0;
  }

  event5:
  {
    s32 low; /* MATCH: merge random-range bounds in the retail argument registers. */
    s32 high; /* MATCH: preserve the range-bound delay slots. */
    s32 eventTest = blocked;
       /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
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
      low = 0x10;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
      high = 0x18;
         /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
         /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
      saved[0] = 1;
      goto state_roll;
    }
    if ((D_80012090[0] != 2) && (D_8008146C[0] < 0x16))
    {
      low = 0x50;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
      high = 0x78;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
      saved[0] = 2;
         /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
      state_roll:
      saved[2] = func_800A6DA4(low, high);
      saved[3] = 0;
      goto done;
    }
    entityp->state48 = 3;
    saved[2] = func_800A6DA4(0x10, 0x18);
    saved[3] = 1;
    goto done;
  }

  event9:
  {
  s32 eventZero = 0;
  s32 eventTest;
     /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
  eventTest = blocked;
     /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */

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
  done:
   /* MATCH: keep the shared zero return after the state-store delay slots. */
  return 0;
  }
}
