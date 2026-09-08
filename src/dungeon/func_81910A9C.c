#include "common.h"
extern u8 D_80083160[];
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, s32);
/* Builds and depth-sorts five radial line segments for an effect. */
void func_8002429C(void *effect_data, void *origin, s16 step_index, s16 scale_factor)
{
  u8 *effect;
  register s32 scale ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
  register s32 step;
  u32 addr_mask;
  register s32 angle ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
  register u8 *scratch ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
  u8 *render_global;
  u8 *line_packet;
  void *projection_param;
  u8 *flags_or_mode;
  s32 ray_index = 0;
  s32 prev_step;
  effect = effect_data;
  render_global = (u8 *) D_80083160;
  scale = (s16) scale_factor;
  step = (s16) step_index;
  prev_step = step - 1;
  addr_mask = 0x00FFFFFF;
  angle = 0;
  scratch = (u8 *) 0x1F800000;
  *((void **) (((u8 *) scratch) + 0x18)) = (*((u8 **) D_80083160)) + 0xB0;
  do
  {
    void **render_ptr = (void **) render_global;
    void *render_ctx = *render_ptr;
    register s32 radial_offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 start_step_offset;
    s32 end_step_offset;
    s32 z_delta;
    s32 z_step;
    s32 avg_depth;
    void *origin_ptr;
    u16 origin_coord;
    line_packet = *((u8 **) (((u8 *) render_ctx) + 0x8D0));
    *((u8 **) (((u8 *) render_ctx) + 0x8D0)) = line_packet + 0x14;
    *((u8 *) (((u8 *) line_packet) + 3)) = 4;
    *((u8 *) (((u8 *) line_packet) + 7)) = 0x52;
    *((u8 *) (((u8 *) line_packet) + 4)) = *((u8 *) (((u8 *) effect) + 0x40));
    *((u8 *) (((u8 *) line_packet) + 5)) = *((u8 *) (((u8 *) effect) + 0x41));
    *((u8 *) (((u8 *) line_packet) + 6)) = *((u8 *) (((u8 *) effect) + 0x42));
    *((u8 *) (((u8 *) line_packet) + 0xC)) = *((u8 *) (((u8 *) effect) + 0x40));
    *((u8 *) (((u8 *) line_packet) + 0xD)) = *((u8 *) (((u8 *) effect) + 0x41));
    *((u8 *) (((u8 *) line_packet) + 0xE)) = *((u8 *) (((u8 *) effect) + 0x42));
    origin_ptr = *((void * volatile *) (&origin));
    origin_coord = *((u16 *) (((u8 *) origin_ptr) + 2));
    *((u16 *) (((u8 *) scratch) + 0x6C)) = origin_coord;
    *((u16 *) (((u8 *) scratch) + 0x64)) = origin_coord;
    radial_offset = ((func_800644B8(angle + (*((s16 *) (((u8 *) effect) + 0xA)))) >> 4) * (*((s16 *) (((u8 *) effect) + 0xE)))) << 8;
    start_step_offset = radial_offset / scale;
    *((s32 *) (((u8 *) scratch) + 0x108)) = radial_offset;
    ASM_KEEP_NV(radial_offset);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    end_step_offset = radial_offset / scale;
    *((u16 *) (((u8 *) scratch) + 0x64)) += (start_step_offset * prev_step) >> 16;
    *((u16 *) (((u8 *) scratch) + 0x6C)) += (end_step_offset * step) >> 16;
    origin_ptr = *((void * volatile *) (&origin));
    origin_coord = *((u16 *) (((u8 *) origin_ptr) + 6));
    *((u16 *) (((u8 *) scratch) + 0x6E)) = origin_coord;
    *((u16 *) (((u8 *) scratch) + 0x66)) = origin_coord;
    radial_offset = ((func_80064584(angle + (*((s16 *) (((u8 *) effect) + 0xA)))) >> 4) * (*((s16 *) (((u8 *) effect) + 0xE)))) << 8;
    start_step_offset = radial_offset / scale;
    *((s32 *) (((u8 *) scratch) + 0x10C)) = radial_offset;
    ASM_KEEP_NV(radial_offset);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    end_step_offset = radial_offset / scale;
    *((u16 *) (((u8 *) scratch) + 0x66)) += (start_step_offset * prev_step) >> 16;
    projection_param = scratch + 0x84;
    *((u16 *) (((u8 *) scratch) + 0x6E)) += (end_step_offset * step) >> 16;
    origin_ptr = *((void * volatile *) (&origin));
    origin_coord = *((u16 *) (((u8 *) origin_ptr) + 0xA));
    *((u16 *) (((u8 *) scratch) + 0x70)) = origin_coord;
    *((u16 *) (((u8 *) scratch) + 0x68)) = origin_coord;
    z_delta = (((s32) (*((s16 *) (((u8 *) effect) + 0x14)))) << 16) - (*((s32 *) (((u8 *) origin_ptr) + 8)));
    *((s32 *) (((u8 *) scratch) + 0x110)) = z_delta;
    z_step = z_delta >> scale;
    *((u16 *) (((u8 *) scratch) + 0x68)) += (z_step << prev_step) >> 16;
    *((u16 *) (((u8 *) scratch) + 0x70)) += (((*((volatile s32 *) (scratch + 0x110))) >> scale) << step) >> 16;
    *((s32 *) (((u8 *) scratch) + 0xF4)) = func_80065420(scratch + 0x64, scratch + 0xD8, projection_param, scratch + 0x88);
    flags_or_mode = scratch + 0x88;
    *((s32 *) (((u8 *) scratch) + 0xF8)) = func_80065420(scratch + 0x6C, scratch + 0xDC, projection_param, flags_or_mode);
    *((u16 *) (((u8 *) line_packet) + 8)) = *((u16 *) (((u8 *) scratch) + 0xD8));
    *((u16 *) (((u8 *) line_packet) + 0xA)) = *((u16 *) (((u8 *) scratch) + 0xDA));
    *((u16 *) (((u8 *) line_packet) + 0x10)) = *((u16 *) (((u8 *) scratch) + 0xDC));
    *((u16 *) (((u8 *) line_packet) + 0x12)) = *((u16 *) (((u8 *) scratch) + 0xDE));
    avg_depth = ((*((s32 *) (((u8 *) scratch) + 0xF4))) + (*((s32 *) (((u8 *) scratch) + 0xF8)))) / 2;
    *((s32 *) (((u8 *) scratch) + 0xB4)) = avg_depth;
    if (((u32) avg_depth) < 0x1E0U)
    {
      u8 *draw_mode;
      *((u32 *) (((u8 *) line_packet) + 0)) = ((*((u32 *) (((u8 *) line_packet) + 0))) & 0xFF000000) | ((*((u32 *) (((u8 *) ((*((u32 **) (((u8 *) scratch) + 0x18))) + avg_depth)) + 0))) & addr_mask);
      *((u32 *) (((u8 *) ((*((u32 **) (((u8 *) scratch) + 0x18))) + (*((s32 *) (((u8 *) scratch) + 0xB4))))) + 0)) = ((*((u32 *) (((u8 *) ((*((u32 **) (((u8 *) scratch) + 0x18))) + (*((s32 *) (((u8 *) scratch) + 0xB4))))) + 0))) & 0xFF000000) | (((u32) line_packet) & addr_mask);
      render_ptr = (void **) render_global;
      render_ctx = *render_ptr;
      flags_or_mode = *((u8 **) (((u8 *) render_ctx) + 0x8D0));
      *((u8 **) (((u8 *) render_ctx) + 0x8D0)) = flags_or_mode + 0xC;
      func_80067F20(flags_or_mode, 0, 0, func_80066460(0, *((s16 *) (((u8 *) effect) + 0x12)), 0, 0) & 0xFFFF, 0);
      *((u32 *) (((u8 *) flags_or_mode) + 0)) = ((*((u32 *) (((u8 *) flags_or_mode) + 0))) & 0xFF000000) | ((*((u32 *) (((u8 *) ((*((u32 **) (((u8 *) scratch) + 0x18))) + (*((s32 *) (((u8 *) scratch) + 0xB4))))) + 0))) & addr_mask);
      *((u32 *) (((u8 *) ((*((u32 **) (((u8 *) scratch) + 0x18))) + (*((s32 *) (((u8 *) scratch) + 0xB4))))) + 0)) = ((*((u32 *) (((u8 *) ((*((u32 **) (((u8 *) scratch) + 0x18))) + (*((s32 *) (((u8 *) scratch) + 0xB4))))) + 0))) & 0xFF000000) | (((u32) flags_or_mode) & addr_mask);
    }
    angle += 0x333;
    ray_index++;
  }
  while (ray_index < 5);
  ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
}
