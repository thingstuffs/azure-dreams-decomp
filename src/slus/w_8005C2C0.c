#include "common.h"

typedef struct S_8005C2C0_slot
{
  s16 field_00;
  u8 pad02[0x06 - 0x02];
  s16 field_06;
  u8 pad08[0x0A - 0x08];
  s16 field_0A;
  u8 pad0C[0x10 - 0x0C];
  s16 field_10;
  u16 field_12;
  s8 field_14;
  s8 field_15;
  s8 field_16;
  s8 field_17;
  u8 pad18[0x1A - 0x18];
  s16 field_1A;
  u8 pad1C[0x22 - 0x1C];
  s8 field_22;
  s8 field_23;
  u8 pad24[0x5C - 0x24];
  s16 field_5C;
  u8 pad5E[0x78 - 0x5E];
} S_8005C2C0_slot;
typedef struct S_8005C2C0_kind
{
  u8 pad00[0x10];
  s32 field_10;
  u8 pad14[0x1C - 0x14];
} S_8005C2C0_kind;
typedef struct S_8005C2C0_req
{
  s32 field_00;
  s32 field_04;
  s16 field_08;
  u16 field_0A;
  s16 field_0C;
  s16 field_0E;
  u8 pad10[0x16 - 0x10];
  u16 field_16;
  s16 field_18;
  u8 pad1A[0x1C - 0x1A];
  s32 field_1C;
  u8 pad20[0x24 - 0x20];
  s32 field_24;
  s32 field_28;
  s32 field_2C;
  s16 field_30;
  s16 field_32;
  s16 field_34;
  s16 field_36;
  s16 field_38;
} S_8005C2C0_req;
extern s32 D_80073740[32];
extern S_8005C2C0_slot D_80085458;
extern s32 D_80085F98[4];
extern S_8005C2C0_kind D_80086A40;
extern void func_80056DB4(s32 arg0);
extern void func_8005E97C(s32 a0, s32 a1);
extern s32 func_8005EB78(s32 a0);
extern void func_8005EC0C(void *a0);
s16 func_8005C2C0(s16 arg0, s32 arg1, s16 arg2, unsigned short arg3, u16 arg4, u16 arg5, u16 arg6)
{
  S_8005C2C0_req req;
  S_8005C2C0_kind *new_var;
  S_8005C2C0_slot *slot_base;
  S_8005C2C0_slot *slot;
  s32 *ptr;
  s32 *tbl;
  s32 res;
  s32 k2;
  s8 k7f;
  D_80085F98[0] = 1;
  if (arg0 != (-1))
  {
    if (arg1 < 0x18)
    {
      func_80056DB4(arg1);
      tbl = D_80073740;
      ptr = &tbl[arg1];
      k2 = 2;
      do
      {
        func_8005E97C(0, *ptr);
        res = func_8005EB78(*ptr);
      }
      while ((res != k2) && (res != 0));
      req.field_04 = 0x1FFEF;
      req.field_24 = 1;
      req.field_28 = 1;
      req.field_2C = 3;
      req.field_30 = 0;
      req.field_32 = 0;
      req.field_34 = 0;
      req.field_36 = 0;
      req.field_38 = 0;
      req.field_0C = 0;
      req.field_0E = 0;
      new_var = &D_80086A40;
      slot_base = &D_80085458;
      req.field_00 = *ptr;
      req.field_1C = new_var[arg0].field_10;
      k7f = 0x7F;
      ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
      slot = &slot_base[arg1];
      slot->field_06 = 0x11;
      slot->field_16 = 0x40;
      slot->field_17 = 0x40;
      slot->field_14 = k7f;
      slot->field_15 = k7f;
      slot->field_10 = arg5 << 7;
      slot->field_00 = arg1;
      slot->field_1A = 1;
      slot->field_22 = arg2;
      slot->field_23 = arg3;
      slot->field_0A = arg4;
      slot->field_5C = arg0;
      slot->field_12 = arg6 << 7;
      req.field_08 = slot->field_10;
      req.field_0A = slot->field_12;
      req.field_16 = arg4;
      if (arg3 & 0xFFFF)
      {
        req.field_18 = ((arg2 - 1) << 8) | (0x7F - arg3);
      }
      else
      {
        req.field_18 = arg3 | (arg2 << 8);
      }
      func_8005EC0C(&req);
    }
  }
  D_80085F98[0] = 0;
  return arg1;
}
