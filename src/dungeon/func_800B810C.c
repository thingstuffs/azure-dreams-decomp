#include "common.h"
#include "m2c_compat.h"
extern u8 *D_800E3D7C[];
extern u8 D_80083780[12];
extern u8 D_80082E80[];
extern u16 D_800DDE84[];
extern s32 D_80083460[3];
extern void func_80041E70(void *);
extern void func_80042B68(void *, s8);
extern void func_8008D330(void *, u8 *, u8 *, void *);
extern void func_80098B38(s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(M2C_UNK *, s32);
extern void func_80099290(volatile int);
extern s32 func_80099734(void *, s32);
extern void func_800A5720(s32);
extern void func_800A5F38(void *, s32);
extern void func_800A63B8(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);
extern void func_800C4AFC(s32, s32, void *);
extern M2C_UNK D_800E0EB4;
extern M2C_UNK D_800E0EC9;
s32 func_800BD86C(void *arg0, s32 arg1, s16 arg2)
{
  s32 temp_v0;
  s32 value;
  register M2C_UNK *message;
  register s32 call_value;
  u8 *counter;
  s32 var_s0;
  if (arg0 == (*D_800E3D7C))
  {
    *((s32 *) (((s8 *) arg0) + 0x110)) = arg1;
    func_8008D330(arg0, D_80083780, D_80082E80, arg0);
    return 0;
  }
  if (((u32) arg0) <= 0x9FFFFFFFU)
  {
    func_800A63B8(arg0, arg1, arg2);
    if (func_800AD6FC(arg0, (D_800DDE84[*((u8 *) (((s8 *) arg0) + 0x13))] >> 6) & 3, 0) == 0)
    {
      func_800A5F38(arg0, arg1);
      return 1;
    }
    goto block_8;
  }
  block_8:
  func_800C4AFC(*((s32 *) (((s8 *) arg0) + (-0x18))), 0x20C0C0, arg0);

  if ((*((s32 *) (((s8 *) arg0) + 0x14))) & 0x4000)
  {
    temp_v0 = func_800990FC();
    message = &D_800E0EB4;
    call_value = temp_v0;
    temp_v0 = func_80099194(message, value = call_value);
    func_80099290(func_80099194(&D_800E0EC9, func_80099734(arg0, temp_v0)));
    func_800A5720(value);
  }
  if ((*((s32 *) (((s8 *) arg0) + 0x1C))) & 0x04000000)
  {
    *((s8 *) (((s8 *) arg0) + 0x28)) = (s8) ((((u8) (*((u8 *) (((s8 *) arg0) + 0x29)))) >> 1) + 1);
  }
  var_s0 = 1;
  *((u8 *) (((s8 *) arg0) + 0x26)) = (u8) (*((u8 *) (((s8 *) arg0) + 0x68)));
  *((u8 *) (((s8 *) arg0) + 0x27)) = (u8) (*((u8 *) (((s8 *) arg0) + 0x69)));
  do
  {
    func_80042B68(arg0, var_s0);
    var_s0 += 1;
  }
  while (var_s0 < 0x21);
  *((s32 *) (((s8 *) arg0) + 0x1C)) = (s32) ((*((s32 *) (((s8 *) arg0) + 0x1C))) & 0xFBFFE10F);
  func_80041E70(arg0);
  func_80098B38(arg1);
  counter = (u8 *) D_80083460;
  *((u16 *) (((s8 *) counter) + 0xA)) = (u16) ((*((u16 *) (((s8 *) counter) + 0xA))) - 1);
  return 1;
}
