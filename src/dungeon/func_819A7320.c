#include "common.h"
#include "m2c_compat.h"
struct S_80083160;
typedef struct S_80083160 S_80083160;
extern S_80083160 D_80083160;
int abs(int);
s32 func_80065420();
M2C_UNK func_80066640();
M2C_UNK func_800666F4();
M2C_UNK func_800DBA90();
typedef struct
{
  u16 x;
  u16 y;
  u16 z;
  u16 pad;
} E_SVEC;
typedef struct
{
  u16 x;
  u16 y;
} E_DVEC;
typedef struct
{
  void *p0;
  void *p1;
  s16 f08;
  s16 f0A;
  u16 f0C;
  s16 f0E;
  s16 f10;
  s16 f12;
  s16 f14;
  s16 f16;
  s16 f18;
  s16 f1A;
  s32 f1C;
} E_PRIM;
/* Emit each chain node's four trail quads into the display list, depth-sorted into the OT. */
s32 func_819A7320(void *node)
{
  E_SVEC scratch;
  s32 otz[6];
  E_DVEC sxy[6];
  E_PRIM prim;
  s32 p;
  s32 i;
  s32 mid_otz;
  s32 slot_offset;
  S_80083160 *base;
  void *poly;
  void *parent;
  void *obj;
  int dy;
  u8 colour_a;
  u8 colour_b;
  u8 colour_c;
  u8 colour_d;
  base = &D_80083160;
  do
  {
    obj = node;
    i = 4;
    do
    {
      otz[i] = (s32) (func_80065420(((u8 *) obj) + ((i * 8) + 4), &sxy[i], &p, &p) - 8);
      i -= 1;
    }
    while (i >= 0);
    scratch.x = *((u16 *) (((s8 *) obj) + 4));
    scratch.y = *((u16 *) (((s8 *) obj) + 6));
    scratch.z = (u16) ((*((u16 *) (((s8 *) obj) + 8))) + 0x30);
    func_80065420(&scratch, &sxy[5], &p, &p);
    scratch.x = 0;
    scratch.z = 0;
    prim.p1 = &scratch;
    prim.p0 = &scratch;
    prim.f0A = 0;
    prim.f08 = 0;
    prim.f14 = 0;
    prim.f12 = 0;
    prim.f10 = 0;
    prim.f1A = 0;
    prim.f18 = 1;
    dy = (s16) sxy[0].y;
    dy = dy - ((s16) sxy[5].y);
    scratch.y = (u16) abs((s32) dy);
    prim.f0C = *((u16 *) (((s8 *) base) + 0xC8));
    func_800DBA90(&prim, (s16) sxy[5].y);
    for (i = 0; i < 4; i++)
    {
      poly = *((void **) (((s8 *) (*((void **) (((s8 *) base) + 0)))) + 0x8D0));
      *((void **) (((s8 *) (*((void **) (((s8 *) base) + 0)))) + 0x8D0)) = (void *) (((u8 *) poly) + 0x28);
      *((s32 *) (((s8 *) poly) + 4)) = *((s32 *) (((s8 *) obj) + 0x38));
      func_800666F4(poly);
      func_80066640(poly, 1);
      *((u16 *) (((s8 *) poly) + 0x16)) = (u16) (*((u16 *) (((s8 *) obj) + 0x40)));
      *((u16 *) (((s8 *) poly) + 0xE)) = (u16) (*((u16 *) (((s8 *) obj) + 0x42)));
      *((s16 *) (((s8 *) poly) + 8)) = (s16) (sxy[i].x - scratch.x);
      *((s16 *) (((s8 *) poly) + 0x10)) = (s16) (sxy[i + 1].x - scratch.x);
      *((s16 *) (((s8 *) poly) + 0x18)) = (s16) (sxy[i].x + scratch.x);
      *((s16 *) (((s8 *) poly) + 0x20)) = (s16) (sxy[i + 1].x + scratch.x);
      *((s16 *) (((s8 *) poly) + 0xA)) = (s16) (sxy[i].y - scratch.y);
      *((s16 *) (((s8 *) poly) + 0x1A)) = (s16) (sxy[i].y + scratch.y);
      *((s16 *) (((s8 *) poly) + 0x12)) = (s16) (sxy[i + 1].y - scratch.y);
      *((s16 *) (((s8 *) poly) + 0x22)) = (s16) (sxy[i + 1].y + scratch.y);
      colour_a = *((u8 *) (((s8 *) obj) + 0x2C));
      *((u8 *) (((s8 *) poly) + 0x1C)) = colour_a;
      *((u8 *) (((s8 *) poly) + 0xC)) = colour_a;
      colour_b = (u8) (colour_a + (*((u8 *) (((s8 *) obj) + 0x30))));
      *((u8 *) (((s8 *) poly) + 0x24)) = colour_b;
      *((u8 *) (((s8 *) poly) + 0x14)) = colour_b;
      colour_c = *((u8 *) (((s8 *) obj) + 0x2E));
      *((u8 *) (((s8 *) poly) + 0x25)) = colour_c;
      *((u8 *) (((s8 *) poly) + 0x1D)) = colour_c;
      colour_d = (u8) (colour_c + (*((u8 *) (((s8 *) obj) + 0x32))));
      *((u8 *) (((s8 *) poly) + 0x15)) = colour_d;
      *((u8 *) (((s8 *) poly) + 0xD)) = colour_d;
      mid_otz = (s32) ((otz[i] + otz[i + 1]) >> 1);
      p = mid_otz;
      if (((u32) mid_otz) < 0x1E0U)
      {
        u32 low_mask = 0xFFFFFF;
        u32 high_mask = 0xFF000000;
        slot_offset = mid_otz * 4;
        *((s32 *) (((s8 *) poly) + 0)) = (s32) (((*((s32 *) (((s8 *) poly) + 0))) & high_mask) | ((*((s32 *) (((s8 *) (((u8 *) slot_offset) + ((u32) (*((void **) (((s8 *) base) + 0)))))) + 0xB0))) & low_mask));
        *((s32 *) (((s8 *) (((u8 *) slot_offset) + ((u32) (*((void **) (((s8 *) base) + 0)))))) + 0xB0)) = (s32) (((*((s32 *) (((s8 *) (((u8 *) slot_offset) + ((u32) (*((void **) (((s8 *) base) + 0)))))) + 0xB0))) & high_mask) | (((s32) poly) & low_mask));
      }
    }

    parent = *((void **) (((s8 *) node) + (-8)));
    if (parent == 0)
    {
      break;
    }
    node = (void *) (((u8 *) parent) + 0x20);
  }
  while (1);
  return 0;
}
