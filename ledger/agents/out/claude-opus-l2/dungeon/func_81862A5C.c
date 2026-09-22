#include "common.h"
#include "m2c_compat.h"
extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern s32 rand();
extern M2C_UNK D_8002418C;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEDB0[3];
/* Spawn a 0x212 effect object at the source position, jittered upward by a random amount. */
void func_81862A5C(s32 owner, void *source)
{
  s32 roll;
  void *render;
  int white;
  void *part;
  void *obj;
  obj = func_8003FC64(0x212);
  if (obj != 0)
  {
    *((M2C_UNK **) (((s8 *) obj) + 0x10)) = &D_8002418C;
    render = *((void **) (((s8 *) obj) + 0xC));
    *((s32 *) (((s8 *) obj) + 0x20)) = owner;
    *((s8 *) (((s8 *) obj) + 0x24)) = 0;
    white = 0x80;
    *((s8 *) (((s8 *) render) + 0xE)) = white;
    *((s8 *) (((s8 *) render) + 0xD)) = white;
    *((s8 *) (((s8 *) render) + 0xC)) = white;
    func_8003DB94(render, D_800DEDB0, 0);
    *((s16 *) (((s8 *) render) + 0x1E)) = 0x1000;
    *((s16 *) (((s8 *) render) + 0x1C)) = 0x1000;
    *((s16 *) (((s8 *) render) + 0x12)) = 0x7E0B;
    *((u16 *) (((s8 *) render) + 0x10)) = (u16) ((*((u16 *) (((s8 *) render) + 0x10))) | 0x60);
    *((u16 *) (((s8 *) render) + 0x14)) = (u16) ((*((u16 *) (((s8 *) render) + 0x14))) | 0x10C);
    func_8004491C(obj, &D_80045340);
    part = *((void **) (((s8 *) obj) + 8));
    rand();
    *((u16 *) (((s8 *) part) + 2)) = (u16) (*((u16 *) (((s8 *) source) + 2)));
    *((u16 *) (((s8 *) part) + 6)) = (u16) (*((u16 *) (((s8 *) source) + 6)));
    roll = rand();
    *((s16 *) (((s8 *) part) + 0xA)) = (s16) (((*((u16 *) (((s8 *) source) + 0xA))) - 0x40) - (roll % 16));
  }
}
