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
s32 func_818B0E10(s32 unused_0, void *origin, s32 unused_2, s16 point_scale, s32 plane_z, s32 points_addr, u8 intensity, u16 color_phase)
{
  register u8 *globals_page ASM_REG("$4") = D_80080000;   /* MATCH pin: keeps a statement from moving across a call/branch */
  register s32 segment ASM_REG("$22") = 15;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
  register s32 coord_scale ASM_REG("$21") = (s16) point_scale;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
  register s32 point_base ASM_REG("$2") = points_addr;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
  register s32 initial_z ASM_REG("$3") = plane_z;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
  s16 phase = (s16) color_phase;
  void *projection_aux = (void *) 0x1F800084;
  register s32 green ASM_REG("$23") = intensity;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
  register s32 addr_mask ASM_REG("$20") = 0x00FFFFFF;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
  s32 tag_mask = 0xFF000000;
  register s32 *point ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
  register u8 *scratch ASM_REG("$18");   /* MATCH pin: retail keeps a computation the compiler would drop */
  u8 *line_prim;
  register RenderState *initial_ctx ASM_REG("$2");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
  GlobalState *render_state = &D_80083160;
  register s32 depth ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
  point = (s32 *) (((u8 *) point_base) + 0x3C);
  initial_ctx = *((RenderState **) (globals_page + 0x3160));
  scratch = (u8 *) 0x1F800000;
  ASM_KEEP(tag_mask);   /* MATCH pin: retail schedule: same instructions, different order without it */
  ASM_KEEP(scratch);   /* MATCH pin: load-bearing for the whole function shape */
  ASM_KEEP(green);   /* MATCH pin: retail schedule: same instructions, different order without it */
  ASM_KEEP(coord_scale);   /* MATCH pin: retail schedule: same instructions, different order without it */
  *((u16 *) (scratch + 0x70)) = (u16) initial_z;
  *((u16 *) (scratch + 0x68)) = (u16) initial_z;
  *((void **) (scratch + 0x18)) = ((u8 *) initial_ctx) + 0xB0;
  do
  {
    register s32 phase_offset ASM_REG("$2") = phase;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 color_index ASM_REG("$5") = segment + phase_offset;   /* MATCH pin: load-bearing for the whole function shape */
    s32 biased_index = color_index;
    s32 next_color_index;
    s32 color_scale;
    register s32 shade ASM_REG("$2");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 green_fixed ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    RenderState *ctx;
    s32 line_code;
    s32 color_sign;
    register s32 div255_multiplier ASM_REG("$3");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    union {
      s64 both;
      struct { s32 hi; u32 lo; } word;
    } wide_product;
    green_fixed = green << 16;
    div255_multiplier = (s32) 0x80808081U;
    wide_product.both = (s64) green_fixed * div255_multiplier;
    ctx = render_state->ctx;
    line_prim = ctx->nextPrim;
    ctx->nextPrim = line_prim + 0x14;
    line_prim[3] = 4;
    line_code = 0x52;
    color_sign = green_fixed >> 31;
    line_prim[7] = (u8) line_code;
    ASM_MEM_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    shade = (wide_product.word.hi - -green_fixed) >> 7;
    color_scale = shade - color_sign;
    {
      register s32 shade_scale ASM_REG("$4") = color_scale;   /* MATCH pin: keeps a statement from moving across a call/branch */
      register s32 saved_shade_scale ASM_REG("$7") = shade_scale;   /* MATCH pin: retail register colouring depends on it */
      register s32 shade_product ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
      if (color_index < 0)
      {
        biased_index = color_index + 15;
      }
      shade_product = shade_scale * (*((u8 *) (((u8 *) (&D_8002588C)) + (color_index - ((biased_index >> 4) << 4)))));
      shade = shade_product >> 18;
      shade_scale = saved_shade_scale;
      next_color_index = color_index + 1;
      biased_index = next_color_index;
      line_prim[5] = green;
      line_prim[4] = (s8) shade;
      line_prim[6] = (s8) shade;
      if (next_color_index < 0)
      {
        biased_index = color_index + 16;
      }
      shade_product = shade_scale * (*((u8 *) (((u8 *) (&D_8002588C)) + (next_color_index - ((biased_index >> 4) << 4)))));
      line_prim[0xD] = green;
      shade = shade_product >> 18;
      line_prim[0xC] = (s8) shade;
      line_prim[0xE] = (s8) shade;
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
      register s32 depth_sum ASM_REG("$2");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
      depth_sum = *((s32 *) (scratch + 0xF4));
      depth_sum += *((s32 *) (scratch + 0xF8));
      depth = depth_sum / 2;
    }
    ASM_KEEP_NV(depth);   /* MATCH pin: keeps a statement from moving across a call/branch */
    *((s32 *) (scratch + 0xB4)) = depth;
    if (((u32) depth) < 0x1E0U)
    {
      u8 *draw_mode_prim;
      *((s32 *) line_prim) = ((*((s32 *) line_prim)) & tag_mask) | (((s32 *) (*((void **) (scratch + 0x18))))[depth] & addr_mask);
      {
        register u32 ot_slot ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
        register u32 *ordering_table ASM_REG("$2");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        u32 old_tag;
        register u32 prim_addr ASM_REG("$2");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        ot_slot = *((u32 *) (scratch + 0xB4));
        ordering_table = *((u32 **) (scratch + 0x18));
        ot_slot = (ot_slot << 2) + ((u32) ordering_table);
        old_tag = *((u32 *) ot_slot);
        prim_addr = ((u32) line_prim) & addr_mask;
        *((u32 *) ot_slot) = (old_tag & tag_mask) | prim_addr;
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
