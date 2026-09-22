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
/* Kill one actor: the player takes the game-over path, others drop their message, clear their slots and decrement the live count. */
s32 func_800BD86C(void *actor, s32 cause, s16 amount)
{
  s32 handle;
  s32 msg_value;
  register M2C_UNK *msg;
  register s32 msg_arg;
  u8 *counters;
  s32 slot;
  if (actor == (*D_800E3D7C))
  {
    *((s32 *) (((s8 *) actor) + 0x110)) = cause;
    func_8008D330(actor, D_80083780, D_80082E80, actor);
    return 0;
  }
  if (((u32) actor) <= 0x9FFFFFFFU)
  {
    func_800A63B8(actor, cause, amount);
    if (func_800AD6FC(actor, (D_800DDE84[*((u8 *) (((s8 *) actor) + 0x13))] >> 6) & 3, 0) == 0)
    {
      func_800A5F38(actor, cause);
      return 1;
    }
  }
  func_800C4AFC(*((s32 *) (((s8 *) actor) + (-0x18))), 0x20C0C0, actor);

  if ((*((s32 *) (((s8 *) actor) + 0x14))) & 0x4000)
  {
    handle = func_800990FC();
    msg = &D_800E0EB4;
    msg_arg = handle;
    handle = func_80099194(msg, msg_value = msg_arg);
    func_80099290(func_80099194(&D_800E0EC9, func_80099734(actor, handle)));
    func_800A5720(msg_value);
  }
  if ((*((s32 *) (((s8 *) actor) + 0x1C))) & 0x04000000)
  {
    *((s8 *) (((s8 *) actor) + 0x28)) = (s8) ((((u8) (*((u8 *) (((s8 *) actor) + 0x29)))) >> 1) + 1);
  }
  slot = 1;
  *((u8 *) (((s8 *) actor) + 0x26)) = (u8) (*((u8 *) (((s8 *) actor) + 0x68)));
  *((u8 *) (((s8 *) actor) + 0x27)) = (u8) (*((u8 *) (((s8 *) actor) + 0x69)));
  do
  {
    func_80042B68(actor, slot);
    slot += 1;
  }
  while (slot < 0x21);
  *((s32 *) (((s8 *) actor) + 0x1C)) = (s32) ((*((s32 *) (((s8 *) actor) + 0x1C))) & 0xFBFFE10F);
  func_80041E70(actor);
  func_80098B38(cause);
  counters = (u8 *) D_80083460;
  *((u16 *) (((s8 *) counters) + 0xA)) = (u16) ((*((u16 *) (((s8 *) counters) + 0xA))) - 1);
  return 1;
}
