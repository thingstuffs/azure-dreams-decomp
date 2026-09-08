#include "common.h"

/* func_800345B8 -- BYTE-EXACT at gcc 2.7.2-cdk -O2 aspsx 2.56 (stock maspsx).
 *
 * Round-3 closers on top of b8r2_8.c (see b8_rubberduck.md + dig ledger "Round 3"):
 *
 * 1. THE DISPATCH ARMS (retail `lui t0,%hi / addiu a0,t0,%lo` x2): `page` below is a
 *    single-set constant pointer whose only uses sit in the copy-loop dispatch arms, so
 *    its live range wraps the whole outer loop and crosses every call. Priority ~0 ->
 *    allocated last -> no register left -> reload substitutes its REG_EQUIV constant and
 *    rematerializes it AT EACH ARM through the function's spill register $t0 (`lui t0`),
 *    with the arm's add emitted as `addiu a0,t0,imm`. 0x80070000 - 0x57B4 == &D_8006A84C,
 *    0x80070000 - 0x32F0 == &D_8006CD10 (lui-only page base => byte-identical encodings
 *    to retail's %hi/%lo pair). Raw-symbol arms color the la temp v0, tbl-pointer arms
 *    color a0 (genuine PSY-Q 4.1 CC1PSX reproduces both, and ICEs on the pointer-as-call-
 *    arg form) -- the starved-constant reload is the only route to retail's t0 shape.
 *
 * 2. ENTRY ORDER (`fixed_matrix` initialized LAST): sched2 is a backward list scheduler
 *    whose same-priority tie-break prefers the HIGHER-luid insn; the s6 materialization
 *    must carry later luids than the D_80083160 chain or `lui v0,%hi(D_80083160)` is
 *    emitted two words late.
 *
 * 3. `base_addr` (own statement before `amplitude`): gives the D_8006A83E la a lower luid
 *    than the `copy_index << 1` shift, so sched2 emits la-then-sll as retail does.
 */

#include "common.h"
typedef struct RenderState
{
  u8 pad0[6];
  s16 depth_bias;
  u8 *records;
  u32 color;
  u16 texture_bias;
  u16 depth_base;
  u16 flags;
  u16 rot_x;
  u16 rot_y;
  u16 rot_z;
  u8 pad1[4];
  u16 scale_x;
  u16 scale_y;
} RenderState;
typedef struct RenderPool
{
  u8 pad0[0x8D0];
  u8 *next_prim;
} RenderPool;
typedef struct PrimFT4
{
  u32 tag;
  u8 r0;
  u8 g0;
  u8 b0;
  u8 code;
  s16 x0;
  s16 y0;
  u8 u0;
  u8 v0;
  u16 clut;
  s16 x1;
  s16 y1;
  u8 u1;
  u8 v1;
  u16 tpage;
  s16 x2;
  s16 y2;
  u8 u2;
  u8 v2;
  u16 pad1;
  s16 x3;
  s16 y3;
  u8 u3;
  u8 v3;
  u16 pad2;
} PrimFT4;
extern s32 RotTransPers(void *, void *, void *, void *);
extern void RotTransPers4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void PushMatrix(void);
extern void PopMatrix(void);
extern s32 ratan2(s16, s16);
extern s32 rsin(s32);
extern void RotMatrix(void *, void *);
extern void CompMatrix(void *, void *, void *);
extern void SetTransMatrix(void *);
extern void SetRotMatrix(void *);
extern void AddPrim(void *, void *);
extern s16 D_8006A83E[];
extern u8 D_8006A847[];
extern u8 D_8006A84C[32];
extern u8 D_8006CD10[32];
extern u8 D_8006CD30[32];
extern s32 D_8006CD4C[];
extern RenderPool *D_80083160[];
s32 func_800345B8(u8 *arg0, u8 *arg1, u8 *arg2)
{
  u8 *spad;
  register void *fixed_matrix ASM_REG("$22");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
  u8 *point;
  s32 base_x;
  s32 t;
  s32 u;
  u16 base_y;
  s32 copies;
  s32 copy_index;
  s32 sin_x;
  s32 sin_y;
  s32 scaled_depth;
  s32 depth_value;
  s32 product_x;
  s32 product_y;
  s16 *amplitude;
  s32 base_addr;
  void *source_matrix;
  u8 *record;
  u8 *prim;
  s32 projected;
  s32 test_coord;
  s32 coord;
  s32 acc;
  s32 visible0;
  s32 visible1;
  s32 visible01;
  s32 visible2;
  s32 visible012;
  s32 visible3;
  s32 color_accum0;
  s32 color_accum1;
  s32 shifted18;
  s32 shifted10;
  u16 texture;
  u16 tex_mode;
  s32 tvv;
  u8 flag;
  u8 tv;
  void *next;
  u8 *tbl_a;
  u8 *tbl_b;
  RenderPool **pool;
  u8 *page;
  RenderPool *gfx;
  u8 *np;
  page = (u8 *) 0x80070000;
  tbl_a = D_8006A84C;
  tbl_b = D_8006CD10;
  spad = (u8 *) 0x1F800000;
  gfx = D_80083160[0];
  np = gfx->next_prim;
  *((volatile s32 *) (spad + 0x24)) = (s32) (((u8 *) gfx) + 0xB0);
  *((volatile s32 *) (spad + 0xE4)) = 0;
  *((volatile s32 *) (spad + 0x1C)) = (s32) np;
  pool = D_80083160;
  fixed_matrix = (void *) 0x1F8000C8;
  do
  {
    *((u16 *) (spad + 0x04)) = *((u16 *) (arg1 + 2));
    *((u16 *) (spad + 0x06)) = *((u16 *) (arg1 + 6));
    *((u16 *) (spad + 0x08)) = *((u16 *) (arg1 + 10));
    *((s32 *) (spad + 0xC4)) = RotTransPers(spad + 0x04, spad + 0xBC, spad + 0x94, spad + 0x98);
    *((u16 *) (arg2 + 0x14)) |= 0x8000;
    D_8006CD4C[0] = (scaled_depth = (*((s32 *) (spad + 0xC4))) << 2);
    *((s32 *) (tbl_b + 0x1C)) = scaled_depth;
    *((s32 *) (tbl_a + 0x1C)) = scaled_depth;
    depth_value = (*((s32 *) (spad + 0xC4))) - (*((s16 *) (arg2 + 0x06)));
    *((s32 *) (spad + 0xC4)) = depth_value;
    if (((u32) depth_value) < 0x1E0)
    {
      copies = 1;
 do { PushMatrix(); t = (*((u16 *) (spad + 0xBC))) - 0xA0; u = (*((u16 *) (spad + 0xBE))) - 0x78; *((volatile u16 *) (spad + 0xBC)) = t; } while (0);
      base_x = t;
      test_coord = (s16) base_x;
      if (test_coord < 0)
      {
        test_coord = -test_coord;
      }
      *((u16 *) (spad + 0xBE)) = u;
      base_y = u;
      if (test_coord < 0x330)
      {
        test_coord = (s16) u;
        if (test_coord < 0)
        {
          test_coord = -test_coord;
        }
        if (test_coord < 0x330)
        {
          copies = 5;
        }
      }
      copy_index = 0;
      if (copies != 0)
      {
        copy_loop:
        if (copy_index != 0)
        {
          *((s32 *) (spad + 0xC4)) = 10;
          sin_x = rsin(ratan2((s16) base_x, 0x200));
          base_addr = (s32) D_8006A83E;
          amplitude = (s16 *) (base_addr + (copy_index << 1));
          product_x = (*amplitude) * sin_x;
          if (product_x < 0)
          {
            product_x += 0xFFF;
          }
          *((u16 *) (spad + 0xBC)) = base_x - (product_x >> 12);
          sin_y = rsin(ratan2((s16) base_y, 0x200));
          product_y = (*amplitude) * sin_y;
          if (product_y < 0)
          {
            product_y += 0xFFF;
          }
          *((u16 *) (spad + 0xBE)) = base_y - (product_y >> 12);
        }

        *((u16 *) (spad + 0xF8)) = *((u16 *) (arg2 + 0x16));
        *((u16 *) (spad + 0xFA)) = *((u16 *) (arg2 + 0x18));
        *((u16 *) (spad + 0xFC)) = *((u16 *) (arg2 + 0x1A));
        projected = *((u16 *) (arg2 + 0x20));
        *((s32 *) (spad + 0xDC)) = projected;
        *((u16 *) (spad + 0x100)) = projected;
        projected = *((u16 *) (arg2 + 0x22));
        *((s32 *) (spad + 0xE0)) = projected;
        *((u16 *) (spad + 0x102)) = projected;
        RotMatrix(spad + 0xF8, fixed_matrix);
        if (copy_index != 0)
        {
          if (D_8006A847[copy_index] != 0)
          {
            source_matrix = page - 0x57B4;
          }
          else
          {
            ASM_USE_NV(spad);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            source_matrix = page - 0x32F0;
          }
          CompMatrix(source_matrix, fixed_matrix, spad + 0x54);
        }
        else
        {
          CompMatrix(D_8006CD30, fixed_matrix, spad + 0x54);
        }
        SetTransMatrix(spad + 0x54);
        SetRotMatrix(spad + 0x54);
        record = *((u8 **) (arg2 + 0x08));
        point = record + 1;
        *((u16 *) (spad + 0x28)) = *((u16 *) (arg2 + 0x14));
        record_loop:
        if (!(record[0] & 0x20))
        {
          prim = (u8 *) (*((s32 *) (spad + 0x1C)));
          *((s32 *) (spad + 0x1C)) = (s32) (prim + 0x28);
          *((s32 *) (spad + 0x0C)) = point[7];
          *((s32 *) (spad + 0x10)) = point[8];
          *((s32 *) (spad + 0x14)) = point[9];
          *((s32 *) (spad + 0x18)) = point[10];
          if ((record[0] ^ (*((u16 *) (spad + 0x28)))) & 1)
          {
            coord = (-((s8) (*((volatile u8 *) (point + 1))))) - (*((u16 *) (spad + 0x100)));
            *((u16 *) (spad + 0x84)) = coord;
            *((u16 *) (spad + 0x74)) = coord;
            coord -= *((u16 *) (spad + 0x14));
          }
          else
          {
            coord = ((s8) (*((volatile u8 *) (point + 1)))) - (*((u16 *) (spad + 0x100)));
            *((u16 *) (spad + 0x84)) = coord;
            *((u16 *) (spad + 0x74)) = coord;
            coord += *((u16 *) (spad + 0x14));
          }
          *((u16 *) (spad + 0x8C)) = coord;
          *((u16 *) (spad + 0x7C)) = coord;
          if ((record[0] ^ (*((u16 *) (spad + 0x28)))) & 2)
          {
            coord = (-((s8) (*((volatile u8 *) (point + 2))))) - (*((u16 *) (spad + 0x102)));
            *((u16 *) (spad + 0x7E)) = coord;
            *((u16 *) (spad + 0x76)) = coord;
            coord -= *((u16 *) (spad + 0x18));
            *((u16 *) (spad + 0x8E)) = coord;
            *((u16 *) (spad + 0x86)) = coord;
          }
          else
          {
            coord = ((s8) (*((volatile u8 *) (point + 2)))) - (*((u16 *) (spad + 0x102)));
            *((u16 *) (spad + 0x7E)) = coord;
            *((u16 *) (spad + 0x76)) = coord;
            coord += *((u16 *) (spad + 0x18));
            *((u16 *) (spad + 0x8E)) = coord;
            *((u16 *) (spad + 0x86)) = coord;
          }
          *((u16 *) (spad + 0x90)) = 0;
          *((u16 *) (spad + 0x88)) = 0;
          *((u16 *) (spad + 0x80)) = 0;
          *((u16 *) (spad + 0x78)) = 0;
          RotTransPers4(spad + 0x74, spad + 0x7C, spad + 0x84, spad + 0x8C, spad + 0xE8, spad + 0xEC, spad + 0xF0, spad + 0xF4, spad + 0x94, spad + 0x98);
          acc = *((u16 *) (spad + 0xE8));
          acc += *((u16 *) (spad + 0xBC));
          *((s16 *) (prim + 0x08)) = acc;
          acc = *((u16 *) (spad + 0xEA));
          acc += *((u16 *) (spad + 0xBE));
          *((s16 *) (prim + 0x0A)) = acc;
          acc = *((u16 *) (spad + 0xEC));
          acc += *((u16 *) (spad + 0xBC));
          *((s16 *) (prim + 0x10)) = acc;
          acc = *((u16 *) (spad + 0xEE));
          acc += *((u16 *) (spad + 0xBE));
          *((s16 *) (prim + 0x12)) = acc;
          acc = *((u16 *) (spad + 0xF0));
          acc += *((u16 *) (spad + 0xBC));
          *((s16 *) (prim + 0x18)) = acc;
          acc = *((u16 *) (spad + 0xF2));
          acc += *((u16 *) (spad + 0xBE));
          *((s16 *) (prim + 0x1A)) = acc;
          *((s16 *) (prim + 0x20)) = (*((u16 *) (spad + 0xF4))) + (*((u16 *) (spad + 0xBC)));
          *((s16 *) (prim + 0x22)) = (*((u16 *) (spad + 0xF6))) + (*((u16 *) (spad + 0xBE)));
          visible0 = 0;
          if (((u16) ((*((s16 *) (prim + 0x08))) + 0x20)) < 0x181)
          {
            visible0 = ((u16) ((*((s16 *) (prim + 0x0A))) + 0x20)) < 0x121;
          }
          visible1 = 0;
          if (((u16) ((*((s16 *) (prim + 0x10))) + 0x20)) < 0x181)
          {
            visible1 = ((u16) ((*((s16 *) (prim + 0x12))) + 0x20)) < 0x121;
          }
          visible01 = visible0 | visible1;
          visible2 = 0;
          if (((u16) ((*((s16 *) (prim + 0x18))) + 0x20)) < 0x181)
          {
            visible2 = ((u16) ((*((s16 *) (prim + 0x1A))) + 0x20)) < 0x121;
          }
          visible012 = visible01 | visible2;
          visible3 = 0;
          if (((u16) ((*((s16 *) (prim + 0x20))) + 0x20)) < 0x181)
          {
            visible3 = ((u16) ((*((s16 *) (prim + 0x22))) + 0x20)) < 0x121;
          }
          if (visible012 | visible3)
          {
            prim[3] = 9;
            *((u16 *) (arg2 + 0x14)) &= 0x7FFF;
            color_accum0 = (*((s32 *) (spad + 0x14))) + (*((s32 *) (spad + 0x0C)));
            *((s32 *) (spad + 0x14)) = color_accum0;
            if (color_accum0 & 0x100)
            {
              *((s32 *) (spad + 0x14)) = color_accum0 - 1;
            }
            color_accum1 = (*((s32 *) (spad + 0x18))) + (*((s32 *) (spad + 0x10)));
            *((s32 *) (spad + 0x18)) = color_accum1;
            if (color_accum1 & 0x100)
            {
              *((s32 *) (spad + 0x18)) = color_accum1 - 1;
            }
            shifted18 = (*((s32 *) (spad + 0x18))) << 8;
            shifted10 = (*((s32 *) (spad + 0x10))) << 8;
            *((s32 *) (spad + 0x18)) = shifted18;
            *((s32 *) (spad + 0x10)) = shifted10;
            *((u32 *) (prim + 0x0C)) = (shifted10 + (*((s32 *) (spad + 0x0C)))) + (((*((u16 *) (arg2 + 0x12))) + (*((u16 *) (point + 5)))) << 16);
            if (copy_index != 0)
            {
              tvv = *((u16 *) (spad + 0x10));
              tvv += *((u16 *) (spad + 0x14));
              *((u16 *) (prim + 0x14)) = tvv;
              tex_mode = *((u16 *) (arg2 + 0x10));
              if (tex_mode != 0)
              {
                texture = (tex_mode + ((*((u16 *) (point + 3))) & 0xFF9F)) | 0x20;
              }
              else
              {
                texture = (*((u16 *) (point + 3))) | 0x20;
              }
            }
            else
            {
              tvv = *((u16 *) (spad + 0x10));
              tvv += *((u16 *) (spad + 0x14));
              *((u16 *) (prim + 0x14)) = tvv;
              tex_mode = *((u16 *) (arg2 + 0x10));
              if (tex_mode != 0)
              {
                texture = tex_mode + ((*((u16 *) (point + 3))) & 0xFF9F);
              }
              else
              {
                texture = *((u16 *) (point + 3));
              }
            }
            *((u16 *) (prim + 0x16)) = texture;
            tvv = *((u16 *) (spad + 0x18));
            tvv += *((u16 *) (spad + 0x0C));
            *((u16 *) (prim + 0x1C)) = tvv;
            *((u16 *) (prim + 0x24)) = (*((u16 *) (spad + 0x18))) + (*((u16 *) (spad + 0x14)));
            if ((*((s16 *) (prim + 0x08))) > (*((s16 *) (prim + 0x20))))
            {
              prim[0x14]--;
              prim[0x24]--;
            }
            if ((*((s16 *) (prim + 0x0A))) > (*((s16 *) (prim + 0x22))))
            {
              prim[0x1D]--;
              prim[0x25]--;
            }
            flag = point[0];
            arg2[0x0F] = flag;
            if (copy_index != 0)
            {
              ASM_USE_NV(spad);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
              tv = flag | 2;
              arg2[0x0F] = tv;
            }
            else
              if ((*((u16 *) (spad + 0x28))) & 8)
            {
              if (!((*((u16 *) (spad + 0x28))) & 4))
              {
                tv = flag & 0xFD;
              }
              else
              {
                tv = flag | 2;
              }
              arg2[0x0F] = tv;
            }
            if ((*((u16 *) (spad + 0x28))) & 0x10)
            {
              arg2[0x0F] &= 0xFE;
            }
            else
            {
              arg2[0x0F] |= 1;
            }
            *((u32 *) (prim + 4)) = *((u32 *) (arg2 + 0x0C));
            if (copy_index != 0)
            {
              prim[4] >>= 2;
              prim[5] >>= 2;
              prim[6] >>= 2;
            }
            AddPrim((void *) ((*((s32 *) (spad + 0x24))) + ((*((s32 *) (spad + 0xC4))) << 2)), prim);
          }
        }

        point += 0x0C;
        if (((s8) record[0]) >= 0)
        {
          record += 0x0C;
          goto record_loop;
        }
        copy_index++;
        if (copy_index < copies)
        {
          goto copy_loop;
        }
      }
      PopMatrix();
    }
    next = *((void **) (arg0 - 8));
    if (next != 0)
    {
      arg0 = ((u8 *) next) + 0x20;
      arg1 = *((u8 **) (((u8 *) next) + 8));
      arg2 = *((u8 **) (((u8 *) next) + 0x0C));
    }
  }
  while (next != 0);
  pool[0]->next_prim = (u8 *) (*((s32 *) (spad + 0x1C)));
  return 0;
}
