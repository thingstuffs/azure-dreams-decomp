#include "common.h"
#include "m2c_compat.h"

extern int D_800814C8;
extern int D_80081550;
extern int D_80081558;
extern int D_80081554;
extern unsigned char D_80071298[];
extern volatile int D_80071250[];
extern int D_800712B4[];
extern int D_80084130[3];
extern short D_80084808[8];
extern unsigned char D_80080000[];
__asm__(".set D_80080000, 0x80080000");
extern struct S_80083178 D_80083178;
extern struct S_80083178State D_80083CE8;
s32 func_80065420();
s32 func_80066460();
M2C_UNK func_80067F20();
extern M2C_UNK D_8002588C;
typedef struct 
{
  u8 pad0[0x8D0];
  u8 *nextPrim;
} RenderState;
typedef struct 
{
  RenderState *ctx;
  u8 pad0[0x20];
} GlobalState;
extern GlobalState D_80083160;
/* Draw 16 shaded line segments and link them into the ordering table by depth. */
s32 func_818B0E10(void *unused_0, void *origin, void *unused_2, s32 point_scale, s32 plane_z, s32 *points_addr, u8 intensity, s32 color_phase)
{
  u8 *globals_page = D_80080000;
  s32 segment = 15;
  u32 coord_scale = (s16) point_scale;
  s32 *point_base = points_addr;
  s32 initial_z = plane_z;
  s16 phase = (s16) color_phase;
  void *projection_aux = (void *) 0x1F800084;
  u32 addr_mask = 0x00FFFFFF;
  u32 tag_mask = 0xFF000000;
  s32 *point;
  register u8 *scratch ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
  u8 *line_prim;
  RenderState *initial_ctx;
  GlobalState *render_state = &D_80083160;
  s32 depth;
  point = (s32 *) (((u8 *) point_base) + 0x3C);
  initial_ctx = *((RenderState **) (globals_page + 0x3160));
  scratch = (u8 *) 0x1F800000;
  *((u16 *) (scratch + 0x70)) = (u16) initial_z;
  *((u16 *) (scratch + 0x68)) = (u16) initial_z;
  *((void **) (scratch + 0x18)) = ((u8 *) initial_ctx) + 0xB0;
  do
  {
    register s32 phase_offset ASM_REG("$2") = phase;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 color_index ASM_REG("$5") = segment + phase_offset;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 biased_index = color_index;
    s32 color_scale;
    RenderState *ctx;
    s32 line_code;
    s32 color_sign;
    s32 div255_multiplier;
    union {
      s64 both;
      struct { s32 hi; u32 lo; } word;
    } wide_product;
    globals_page = (u8 *)(intensity << 16);
    div255_multiplier = (s32) 0x80808081U;
    wide_product.both = (s64) (s32)globals_page * div255_multiplier;
    ctx = render_state->ctx;
    line_prim = ctx->nextPrim;
    ctx->nextPrim = line_prim + 0x14;
    line_prim[3] = 4;
    line_code = 0x52;
    color_sign = (s32)globals_page >> 31;
    line_prim[7] = (u8) line_code;
    phase_offset = (wide_product.word.hi - -(s32)globals_page) >> 7;
    globals_page = (u8 *)(phase_offset - color_sign);
    {
      s32 shade_scale = (s32)globals_page;
      s32 saved_shade_scale = shade_scale;
      if (color_index < 0)
      {
        biased_index = color_index + 15;
      }
      globals_page = (u8 *)((s32)globals_page * (*((u8 *) (((u8 *) (&D_8002588C)) + (color_index - ((biased_index >> 4) << 4))))));
      phase_offset = (s32)globals_page >> 18;
      globals_page = (u8 *)saved_shade_scale;
      initial_z = color_index + 1;
      biased_index = initial_z;
      line_prim[5] = intensity;
      line_prim[4] = (s8) phase_offset;
      line_prim[6] = (s8) phase_offset;
      if (initial_z < 0)
      {
        biased_index = color_index + 16;
      }
      globals_page = (u8 *)((s32)globals_page * (*((u8 *) (((u8 *) (&D_8002588C)) + (initial_z - ((biased_index >> 4) << 4))))));
      line_prim[0xD] = intensity;
      phase_offset = (s32)globals_page >> 18;
      line_prim[0xC] = (s8) phase_offset;
      line_prim[0xE] = (s8) phase_offset;
    }
    {
      u8 *origin_bytes = (u8 *) origin;
      s32 point_component;
      s32 coord_offset;
      point_component = *point;
      coord_offset = point_component * coord_scale;
      coord_offset >>= 8;
      *((u16 *) (scratch + 0x64)) = (*((u16 *) (origin_bytes + 2))) + coord_offset;
      point_component = point[1];
      coord_offset = point_component * coord_scale;
      coord_offset >>= 8;
      *((u16 *) (scratch + 0x6C)) = (*((u16 *) (origin_bytes + 2))) + coord_offset;
      point_component = point[0x11];
      coord_offset = point_component * coord_scale;
      coord_offset >>= 8;
      *((u16 *) (scratch + 0x66)) = (*((u16 *) (origin_bytes + 6))) + coord_offset;
      point_component = point[0x12];
      coord_offset = point_component * coord_scale;
      coord_offset >>= 8;
      *((u16 *) (scratch + 0x6E)) = (*((u16 *) (origin_bytes + 6))) + coord_offset;
    }
    {
      void *screen_start = scratch + 0xD8;
      u8 *projection_flags;
      projection_flags = scratch + 0x88;
      *((s32 *) (scratch + 0xF4)) = func_80065420(scratch + 0x64, screen_start, projection_aux, projection_flags);
      *((s32 *) (scratch + 0xF8)) = func_80065420(scratch + 0x6C, scratch + 0xDC, projection_aux, projection_flags);
    }
    *((u16 *) (line_prim + 8)) = *((u16 *) (scratch + 0xD8));
    *((u16 *) (line_prim + 0xA)) = *((u16 *) (scratch + 0xDA));
    *((u16 *) (line_prim + 0x10)) = *((u16 *) (scratch + 0xDC));
    *((u16 *) (line_prim + 0x12)) = *((u16 *) (scratch + 0xDE));
    {
      s32 depth_sum;
      depth_sum = *((s32 *) (scratch + 0xF4));
      depth_sum += *((s32 *) (scratch + 0xF8));
      depth = depth_sum / 2;
    }
    *((s32 *) (scratch + 0xB4)) = depth;
    if (((u32) depth) < 0x1E0U)
    {
      u8 *draw_mode_prim;
      *((s32 *) line_prim) = ((*((s32 *) line_prim)) & tag_mask) | (((s32 *) (*((void **) (scratch + 0x18))))[depth] & addr_mask);
      {
        u32 ot_slot;
        u32 *ordering_table;
        u32 old_tag;
        u32 prim_addr;
        ot_slot = *((u32 *) (scratch + 0xB4));
        ordering_table = *((u32 **) (scratch + 0x18));
        ot_slot = (ot_slot << 2) + ((u32) ordering_table);
        old_tag = *((u32 *) ot_slot);
        *((u32 *) ot_slot) = (old_tag & tag_mask) | ((u32)(((u32) line_prim) & addr_mask));
      }
      draw_mode_prim = render_state->ctx->nextPrim;
      render_state->ctx->nextPrim = draw_mode_prim + 0xC;
      func_80067F20(draw_mode_prim, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
      *((s32 *) draw_mode_prim) = ((*((s32 *) draw_mode_prim)) & tag_mask) | (((s32 *) (*((void **) (scratch + 0x18))))[*((s32 *) (scratch + 0xB4))] & addr_mask);
      *(((s32 *) (*((void **) (scratch + 0x18)))) + (*((s32 *) (scratch + 0xB4)))) = ((*(((s32 *) (*((void **) (scratch + 0x18)))) + (*((s32 *) (scratch + 0xB4))))) & tag_mask) | (((s32) draw_mode_prim) & addr_mask);
    }
    segment -= 1;
    point = (s32 *) (((u8 *) point) - 4);
  }
  while (segment >= 0);
  return 0;
}
