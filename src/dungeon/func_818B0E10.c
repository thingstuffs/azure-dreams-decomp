#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

extern unsigned char D_80080000[];
__asm__(".set D_80080000, 0x80080000");
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
  u8 pad00[0x18];
  u32 *ot;
  u8 pad1C[0x48];
  u16 unk_64;
  u16 unk_66;
  u16 unk_68;
  u8 pad6A[0x2];
  u16 unk_6C;
  u16 unk_6E;
  u16 unk_70;
  u8 pad72[0x12];
  s32 unk_84;
  s32 unk_88;
  u8 pad8C[0x28];
  s32 unk_B4;
  u8 padB8[0x20];
  u16 unk_D8;
  u16 unk_DA;
  u16 unk_DC;
  u16 unk_DE;
  u8 padE0[0x14];
  s32 unk_F4;
  s32 unk_F8;
} ScratchPad;
typedef struct {
    unsigned addr: 24;
    unsigned len: 8;
    u8 r0, g0, b0, code;
} P_TAG;
#define setaddr(p, _addr) (((P_TAG *)(p))->addr = (u32)(_addr))
#define getaddr(p) (u32)(((P_TAG *)(p))->addr)
#define addPrim(ot, p) setaddr(p, getaddr(ot)), setaddr(ot, p)
/* Draw 16 shaded line segments and link them into the ordering table by depth. */
s32 func_818B0E10(void *unused_0, void *origin, void *unused_2, s32 point_scale, s32 plane_z, s32 *points_addr, u8 intensity, s32 color_phase)
{
  u8 *globals_page = D_80080000;
  s32 segment = 15;
  s32 *point_base = points_addr;
  s32 initial_z = plane_z;
  s16 phase = (s16) color_phase;
  u8 *scratch;
  u8 *line_prim;
  RenderState *initial_ctx;
  GameWork *render_state = &gameWork;
  s32 depth;
  initial_ctx = *((RenderState **) (globals_page + 0x3160));
  scratch = (u8 *) 0x1F800000;
  ((ScratchPad *) scratch)->unk_70 = (u16) initial_z;
  ((ScratchPad *) scratch)->unk_68 = (u16) initial_z;
  ((ScratchPad *) scratch)->ot = (u32 *) (((u8 *) initial_ctx) + 0xB0);
  do
  {
    s32 phase_offset = phase;
    s32 color_index = segment + phase_offset;
    s32 biased_index = color_index;
    s32 biased_index_2;
    RenderState *ctx;
    s32 line_code;
    s32 div255_multiplier;
    union {
      s64 both;
      struct { s32 hi; u32 lo; } word;
    } wide_product;
    globals_page = (u8 *)(intensity << 16);
    div255_multiplier = (s32) 0x80808081U;
    wide_product.both = (s64) (s32)globals_page * div255_multiplier;
    ctx = ((RenderState *)render_state->unk_000);
    line_prim = ctx->nextPrim;
    ctx->nextPrim = line_prim + 0x14;
    line_prim[3] = 4;
    line_code = 0x52;
    color_phase = (s32)globals_page >> 31;
    line_prim[7] = (u8) line_code;
    phase_offset = (wide_product.word.hi - -(s32)globals_page) >> 7;
    globals_page = (u8 *)(phase_offset - color_phase);
    {
      s32 shade_scale = (s32)globals_page;
      s32 saved_shade_scale = shade_scale;
      globals_page = (u8 *)((s32)globals_page * (*((u8 *) (((u8 *) (&D_8002588C)) + (color_index % 16)))));
      phase_offset = (s32)globals_page >> 18;
      globals_page = (u8 *)saved_shade_scale;
      initial_z = color_index + 1;
      biased_index_2 = initial_z;
      line_prim[5] = intensity;
      line_prim[4] = (s8) phase_offset;
      line_prim[6] = (s8) phase_offset;
      if (initial_z < 0)
      {
        biased_index_2 = color_index + 16;
      }
      globals_page = (u8 *)((s32)globals_page * (*((u8 *) (((u8 *) (&D_8002588C)) + (initial_z - ((biased_index_2 >> 4) << 4))))));
      line_prim[0xD] = intensity;
      phase_offset = (s32)globals_page >> 18;
      line_prim[0xC] = (s8) phase_offset;
      line_prim[0xE] = (s8) phase_offset;
    }
    {
      u8 *origin_bytes = (u8 *) origin;
      s32 point_component;
      s32 coord_offset;
      point_component = point_base[segment];
      coord_offset = point_component * (s16) point_scale;
      coord_offset >>= 8;
      ((ScratchPad *) scratch)->unk_64 = (*((u16 *) (origin_bytes + 2))) + coord_offset;
      point_component = point_base[segment + 1];
      coord_offset = point_component * (s16) point_scale;
      coord_offset >>= 8;
      ((ScratchPad *) scratch)->unk_6C = (*((u16 *) (origin_bytes + 2))) + coord_offset;
      point_component = point_base[segment + 0x11];
      coord_offset = point_component * (s16) point_scale;
      coord_offset >>= 8;
      ((ScratchPad *) scratch)->unk_66 = (*((u16 *) (origin_bytes + 6))) + coord_offset;
      point_component = point_base[segment + 0x12];
      coord_offset = point_component * (s16) point_scale;
      coord_offset >>= 8;
      ((ScratchPad *) scratch)->unk_6E = (*((u16 *) (origin_bytes + 6))) + coord_offset;
    }
    {
      u8 *start_vertex = scratch + 0x64;
      u8 *end_vertex = scratch + 0x6C;
      u8 *start_screen = scratch + 0xD8;
      u8 *end_screen = scratch + 0xDC;
      u8 *projection_aux = scratch + 0x84;
      u8 *projection_flags = scratch + 0x88;
      ((ScratchPad *) scratch)->unk_F4 = func_80065420(start_vertex, start_screen, projection_aux, projection_flags);
      ((ScratchPad *) scratch)->unk_F8 = func_80065420(end_vertex, end_screen, projection_aux, projection_flags);
    }
    *((u16 *) (line_prim + 8)) = ((ScratchPad *) scratch)->unk_D8;
    *((u16 *) (line_prim + 0xA)) = ((ScratchPad *) scratch)->unk_DA;
    *((u16 *) (line_prim + 0x10)) = ((ScratchPad *) scratch)->unk_DC;
    *((u16 *) (line_prim + 0x12)) = ((ScratchPad *) scratch)->unk_DE;
    {
      s32 depth_sum;
      depth_sum = ((ScratchPad *) scratch)->unk_F4;
      depth_sum += ((ScratchPad *) scratch)->unk_F8;
      depth = depth_sum / 2;
    }
    ((ScratchPad *) scratch)->unk_B4 = depth;
    if (((u32) depth) < 0x1E0U)
    {
      u8 *draw_mode_prim;
      addPrim(((ScratchPad *) scratch)->ot + ((ScratchPad *) scratch)->unk_B4, line_prim);
      draw_mode_prim = ((RenderState *)render_state->unk_000)->nextPrim;
      ((RenderState *)render_state->unk_000)->nextPrim = draw_mode_prim + 0xC;
      func_80067F20(draw_mode_prim, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
      addPrim(((ScratchPad *) scratch)->ot + ((ScratchPad *) scratch)->unk_B4, draw_mode_prim);
    }
    segment -= 1;
  }
  while (segment >= 0);
  return 0;
}
