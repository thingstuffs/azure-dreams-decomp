#include "common.h"

typedef struct {
  s32 val;
  s32 pad[2];
} S_800814A0;
extern S_800814A0 D_800814A0;
extern void *func_8003FD64(s32, void *);
extern s32 func_8004491C(void *, void *);
extern u8 D_80045340[9];
extern u8 D_80083498[9];
extern u8 D_800BFF7C[9];
extern u8 D_800F15AC[9];

/* Moves the object through its animation states, spawns an effect, and marks completion. */
void func_800BFD14(void *object)
{
  s32 state;
  void *effect;
  void *effect_sprite;

  state = *((s16 *) (((u8 *) object) + 0x4C));
  *((u16 *) (((u8 *) object) + 0x48)) = (u16) ((*((u16 *) (((u8 *) object) + 0x48))) - 1);
  if (state == 2)
  {
    goto state_2;
  }
  if (state >= 3)
  {
    goto state_ge_3;
  }
  if (state == 0)
  {
    goto state_0;
  }
  if (state == 1)
  {
    goto state_1;
  }
  goto epilogue;

state_ge_3:
  if (state == 3)
  {
    goto state_3;
  }
  if (state == 0xFF)
  {
    goto state_ff;
  }
  goto epilogue;

state_0:
  *((u16 *) (((u8 *) object) + 0x48)) = 3;
  *((s16 *) (((u8 *) object) + 0x2A)) = -4;
  *((s16 *) (((u8 *) object) + 0x32)) = 0x14;
  *((u16 *) (((u8 *) object) + 0x4C)) = (u16) ((*((u16 *) (((u8 *) object) + 0x4C))) + 1);

state_1:
  *((s32 *) (((u8 *) object) + 0x1C)) += *((s32 *) (((u8 *) object) + 0x28));
  *((s32 *) (((u8 *) object) + 0x24)) += *((s32 *) (((u8 *) object) + 0x30));
  if ((*((s16 *) (((u8 *) object) + 0x48))) > 0)
  {
    goto epilogue;
  }
  *((u16 *) (((u8 *) object) + 0x4C)) =
      (u16) ((*((u16 *) (((u8 *) object) + 0x4C))) + 1);
  goto epilogue;

state_2:
  *((u16 *) (((u8 *) object) + 0xC)) = (u16) ((*((u16 *) (((u8 *) object) + 0xC))) + (((*((s16 *) (((u8 *) object) + 0x2A))) * 3) >> 2));
  *((u16 *) (((u8 *) object) + 0x10)) = (u16) ((*((u16 *) (((u8 *) object) + 0x10))) + (((*((s16 *) (((u8 *) object) + 0x32))) * 3) >> 2));
  *((s32 *) (((u8 *) object) + 0x24)) += *((s32 *) (((u8 *) object) + 0x30));
  *((s32 *) (((u8 *) object) + 0x1C)) += *((s32 *) (((u8 *) object) + 0x28));
  if ((*((s16 *) (((u8 *) object) + 0x26))) <= 0)
  {
    goto epilogue;
  }
  *((s16 *) (((u8 *) object) + 0x26)) = 0;
  effect = func_8003FD64(0x312, D_80083498);
  if (effect != 0)
  {
    *((void **) (((u8 *) effect) + 0x10)) = D_800BFF7C;
    func_8004491C(effect, D_80045340);
    effect_sprite = *((void **) (((u8 *) effect) + 0xC));
    *((s32 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 0)) = *((s32 *) (((u8 *) object) + 0x1C));
    *((s32 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 4)) = *((s32 *) (((u8 *) object) + 0x20));
    *((s32 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 8)) = *((s32 *) (((u8 *) object) + 0x24));
    *((s16 *) (((u8 *) effect_sprite) + 0x1E)) = 0xC00;
    *((s16 *) (((u8 *) effect_sprite) + 0x1C)) = 0xC00;
    *((s16 *) (((u8 *) effect_sprite) + 0x10)) = 0x60;
    *((s32 *) (((u8 *) effect_sprite) + 0xC)) = 0xA0A0A0;
    *((void **) (((u8 *) effect_sprite) + 0)) = D_800F15AC;
    *((u16 *) (((u8 *) effect_sprite) + 0x14)) |= 0xC;
    *((s32 *) (((u8 *) effect_sprite) + 8)) = *((s32 *) (D_800F15AC + 4));
    *((s8 *) (((u8 *) effect_sprite) + 4)) = 0;
    *((s8 *) (((u8 *) effect_sprite) + 5)) = 0;
  }
  *((u16 *) (((u8 *) object) + 0x48)) = 4;
  *((u16 *) (((u8 *) object) + 0x4C)) =
      (u16) ((*((u16 *) (((u8 *) object) + 0x4C))) + 1);
  goto epilogue;

state_3:
  *((u16 *) (((u8 *) object) + 0xC)) = (u16) ((*((u16 *) (((u8 *) object) + 0xC))) + (((*((s16 *) (((u8 *) object) + 0x2A))) * 3) >> 2));
  *((u16 *) (((u8 *) object) + 0x10)) = (u16) ((*((u16 *) (((u8 *) object) + 0x10))) + (((*((s16 *) (((u8 *) object) + 0x32))) * 3) >> 2));
  if ((*((s16 *) (((u8 *) object) + 0x48))) > 0)
  {
    goto epilogue;
  }
  {
    u16 *state_field = (u16 *) (((u8 *) object) + 0x4C);
    *state_field = 0xFF;
  }
  goto epilogue;

state_ff:
  *((u16 *) (((u8 *) object) + (-2))) |= 0x8000;
  D_800814A0.val |= 0x8000;

epilogue:
  return;
}
