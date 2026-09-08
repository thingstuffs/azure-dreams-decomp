#include "common.h"

#include "common.h"

typedef struct 
{
  char pad0[0xA4];
  s16 f_A4;
  s16 f_A6;
  s16 f_A8;
  s16 f_AA;
  s16 f_AC;
  s16 f_AE;
  s16 f_B0;
  s16 f_B2;
  void *callback;
  void *field_B8;
  char pad_bc[0x140 - 0xBC];
  void *field_140;
  char pad_144[0x1C4 - 0x144];
} S_80083178_local;
extern void func_8004D1EC(void *a0, void *a1, u16 a2, void *a3);
void func_8004D294(void *a0, void *a1, s32 a2)
{
  S_80083178_local *p = (S_80083178_local *)&D_80083178;
  u16 uv;
  s16 t;
  s16 sv;
  s32 diff;
  s32 near;
  if (a0 != 0)
  {
    func_8004D1EC(&p->field_B8, a0, a2, &p->f_A4);
  }
  if (a1 != 0)
  {
    uv = *((u16 *) (((u8 *) a1) + 0));
    if (uv & 0x800)
    {
      t = uv | 0xF800;
    }
    else
    {
      t = uv & 0x7FF;
    }
    *((s16 *) (((u8 *) a1) + 0)) = t;
    uv = *((u16 *) (&p->f_AC));
    if (uv & 0x800)
    {
      sv = uv | 0xF800;
    }
    else
    {
      sv = uv & 0x7FF;
    }
    p->f_AC = sv;
    {
      register s32 svw ASM_REG("$3") = sv;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
      diff = (*((s16 *) (((u8 *) a1) + 0))) - svw;
    }
    if (diff < 0)
    {
      diff = -diff;
    }
    near = (diff < 0x801);
    uv = *((volatile u16 *) (((u8 *) a1) + 0));
    if (!near)
    {
      *((s16 *) (((u8 *) a1) + 0)) = (sv & 0xF000) | (uv & 0xFFF);
    }
    uv = *((u16 *) (((u8 *) a1) + 2));
    if (uv & 0x800)
    {
      t = uv | 0xF800;
    }
    else
    {
      t = uv & 0x7FF;
    }
    *((s16 *) (((u8 *) a1) + 2)) = t;
    uv = *((u16 *) (&p->f_AE));
    if (uv & 0x800)
    {
      sv = uv | 0xF800;
    }
    else
    {
      sv = uv & 0x7FF;
    }
    p->f_AE = sv;
    {
      register s32 svw ASM_REG("$3") = sv;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
      diff = (*((s16 *) (((u8 *) a1) + 2))) - svw;
    }
    if (diff < 0)
    {
      diff = -diff;
    }
    near = (diff < 0x801);
    uv = *((volatile u16 *) (((u8 *) a1) + 2));
    if (!near)
    {
      *((s16 *) (((u8 *) a1) + 2)) = (sv & 0xF000) | (uv & 0xFFF);
    }
    uv = *((u16 *) (((u8 *) a1) + 4));
    if (uv & 0x800)
    {
      t = uv | 0xF800;
    }
    else
    {
      t = uv & 0x7FF;
    }
    *((s16 *) (((u8 *) a1) + 4)) = t;
    uv = *((u16 *) (&p->f_B0));
    if (uv & 0x800)
    {
      sv = uv | 0xF800;
    }
    else
    {
      sv = uv & 0x7FF;
    }
    p->f_B0 = sv;
    {
      register s32 svw ASM_REG("$3") = sv;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
      diff = (*((s16 *) (((u8 *) a1) + 4))) - svw;
    }
    if (diff < 0)
    {
      diff = -diff;
    }
    near = (diff < 0x801);
    uv = *((volatile u16 *) (((u8 *) a1) + 4));
    if (!near)
    {
      *((s16 *) (((u8 *) a1) + 4)) = (sv & 0xF000) | (uv & 0xFFF);
    }
    func_8004D1EC(&p->field_140, a1, a2, &p->f_AC);
  }
}
