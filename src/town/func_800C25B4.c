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

void func_800BFD14(void *arg0)
{
  s32 state;
  void *temp_v0;
  void *obj;

  state = *((s16 *) (((u8 *) arg0) + 0x4C));
  *((u16 *) (((u8 *) arg0) + 0x48)) = (u16) ((*((u16 *) (((u8 *) arg0) + 0x48))) - 1);
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
  *((u16 *) (((u8 *) arg0) + 0x48)) = 3;
  *((s16 *) (((u8 *) arg0) + 0x2A)) = -4;
  *((s16 *) (((u8 *) arg0) + 0x32)) = 0x14;
  *((u16 *) (((u8 *) arg0) + 0x4C)) = (u16) ((*((u16 *) (((u8 *) arg0) + 0x4C))) + 1);

state_1:
  *((s32 *) (((u8 *) arg0) + 0x1C)) += *((s32 *) (((u8 *) arg0) + 0x28));
  *((s32 *) (((u8 *) arg0) + 0x24)) += *((s32 *) (((u8 *) arg0) + 0x30));
  if ((*((s16 *) (((u8 *) arg0) + 0x48))) > 0)
  {
    goto epilogue;
  }
  *((u16 *) (((u8 *) arg0) + 0x4C)) =
      (u16) ((*((u16 *) (((u8 *) arg0) + 0x4C))) + 1);
  goto epilogue;

state_2:
  *((u16 *) (((u8 *) arg0) + 0xC)) = (u16) ((*((u16 *) (((u8 *) arg0) + 0xC))) + (((*((s16 *) (((u8 *) arg0) + 0x2A))) * 3) >> 2));
  *((u16 *) (((u8 *) arg0) + 0x10)) = (u16) ((*((u16 *) (((u8 *) arg0) + 0x10))) + (((*((s16 *) (((u8 *) arg0) + 0x32))) * 3) >> 2));
  *((s32 *) (((u8 *) arg0) + 0x24)) += *((s32 *) (((u8 *) arg0) + 0x30));
  *((s32 *) (((u8 *) arg0) + 0x1C)) += *((s32 *) (((u8 *) arg0) + 0x28));
  if ((*((s16 *) (((u8 *) arg0) + 0x26))) <= 0)
  {
    goto epilogue;
  }
  *((s16 *) (((u8 *) arg0) + 0x26)) = 0;
  temp_v0 = func_8003FD64(0x312, D_80083498);
  if (temp_v0 != 0)
  {
    *((void **) (((u8 *) temp_v0) + 0x10)) = D_800BFF7C;
    func_8004491C(temp_v0, D_80045340);
    obj = *((void **) (((u8 *) temp_v0) + 0xC));
    *((s32 *) (((u8 *) (*((void **) (((u8 *) temp_v0) + 8)))) + 0)) = *((s32 *) (((u8 *) arg0) + 0x1C));
    *((s32 *) (((u8 *) (*((void **) (((u8 *) temp_v0) + 8)))) + 4)) = *((s32 *) (((u8 *) arg0) + 0x20));
    *((s32 *) (((u8 *) (*((void **) (((u8 *) temp_v0) + 8)))) + 8)) = *((s32 *) (((u8 *) arg0) + 0x24));
    *((s16 *) (((u8 *) obj) + 0x1E)) = 0xC00;
    *((s16 *) (((u8 *) obj) + 0x1C)) = 0xC00;
    *((s16 *) (((u8 *) obj) + 0x10)) = 0x60;
    *((s32 *) (((u8 *) obj) + 0xC)) = 0xA0A0A0;
    *((void **) (((u8 *) obj) + 0)) = D_800F15AC;
    *((u16 *) (((u8 *) obj) + 0x14)) |= 0xC;
    *((s32 *) (((u8 *) obj) + 8)) = *((s32 *) (D_800F15AC + 4));
    *((s8 *) (((u8 *) obj) + 4)) = 0;
    *((s8 *) (((u8 *) obj) + 5)) = 0;
  }
  *((u16 *) (((u8 *) arg0) + 0x48)) = 4;
  *((u16 *) (((u8 *) arg0) + 0x4C)) =
      (u16) ((*((u16 *) (((u8 *) arg0) + 0x4C))) + 1);
  goto epilogue;

state_3:
  *((u16 *) (((u8 *) arg0) + 0xC)) = (u16) ((*((u16 *) (((u8 *) arg0) + 0xC))) + (((*((s16 *) (((u8 *) arg0) + 0x2A))) * 3) >> 2));
  *((u16 *) (((u8 *) arg0) + 0x10)) = (u16) ((*((u16 *) (((u8 *) arg0) + 0x10))) + (((*((s16 *) (((u8 *) arg0) + 0x32))) * 3) >> 2));
  if ((*((s16 *) (((u8 *) arg0) + 0x48))) > 0)
  {
    goto epilogue;
  }
  {
    u16 *terminal_field = (u16 *) (((u8 *) arg0) + 0x4C);
    *terminal_field = 0xFF;
  }
  goto epilogue;

state_ff:
  *((u16 *) (((u8 *) arg0) + (-2))) |= 0x8000;
  D_800814A0.val |= 0x8000;

epilogue:
  return;
}
