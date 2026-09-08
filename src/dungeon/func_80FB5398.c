#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Vertex;

typedef struct {
    s32 value;
} __attribute__((packed)) PackedS32;

typedef struct {
    s32 w0;
    s32 w1;
} __attribute__((packed)) PackedPair;

typedef struct {
    s16 screen[2];
    s32 outer;
} Scratch;

typedef struct {
    void *vertices;
    void *output;
    s16 pad08;
    s16 pad0A;
    s16 z;
    s16 pad0E;
    PackedPair v10;
    s16 count;
    s16 pad1A;
    s32 pad1C;
} Projection;

extern u8 D_8017089C[];
extern u8 D_80083160[];
extern u8 D_801C9E40[];

extern void func_800DBA90(void *);
extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_800644B8(s32);
extern void func_800666F4(void *);
extern void func_80066640(void *, s32);
extern s32 func_80066460(s32, s32, s32, s32);

/* Draw layered, wavy textured strips over the projected bounds of linked objects. */
s32 func_80174B98(void *object_data, void *unused, void *appearance)
{
  s16 bounds[4];
  PackedPair material;
  Vertex vertices[4];
  Projection projection;
  Scratch scratch;
  void *object;
  Projection *projection_ptr;
  s32 bottom_y;
  s32 first_y;
  s32 depth;
  Vertex *vertex_base;
  s32 row_count;
  s32 depth_offset;
  u8 *vertex_bytes;
  u8 *poly;
  s32 index_or_row;
  s32 min_xy;
  s32 max_xy;
  register s32 depth_out_or_phase ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  s32 last_y;
  register s32 row_span;
  register s32 tag_mask ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
  register s32 crop_y;
  u8 *render_state;
  (void) unused;
  render_state = D_80083160;
  material = *((PackedPair *) D_8017089C);
  depth = 0;
  vertex_base = vertices;
  for (;;)
  {
    s32 right_x;
    s32 left_x;
    s32 far_z;
    s32 near_z;
    register Vertex *vertex ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 camera_z;
    s16 min_y;
    s16 max_y;
    s16 base_y;
    s16 height;
    s16 top_page;
    s32 top_page_index;
    s32 left_bound;
    s32 height_pixels;
    s32 top_bound;
    s32 bottom_bound;
    s32 top_copy;
    s32 crop_product;
    s32 bottom_page;
    void *next_object;
    scratch.outer = 48;
    right_x = (u16) scratch.outer;
    index_or_row = 3;
    far_z = -160;
    object = object_data;
    ASM_USE_NV(object);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    near_z = 16;
    left_x = -right_x;
    vertex = vertex_base + 3;
    ASM_KEEP4(vertex, right_x, left_x, index_or_row);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(far_z);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(near_z);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    do
    {
      vertex->x = right_x;
      if (index_or_row < 2)
      {
        vertex->x = left_x;
      }
      vertex->y = 0;
      if (index_or_row & 1)
      {
        vertex->z = far_z;
      }
      else
      {
        vertex->z = near_z;
      }
      index_or_row--;
      vertex--;
    }
    while (index_or_row >= 0);
    projection_ptr = &projection;
    ASM_KEEP4_NV(projection_ptr, projection_ptr, projection_ptr, projection_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    min_xy &= 0xFFFF;
    max_xy &= 0xFFFF;
    index_or_row = 3;
    camera_z = *((u16 *) (((u8 *) render_state) + 0xC8));
    projection.pad0A = 0;
    projection.pad08 = 0;
    depth_out_or_phase = (s32) (&scratch.outer);
    vertex_bytes = ((u8 *) vertex_base) + 24;
    projection.vertices = vertex_base;
    projection.output = vertex_base;
    ASM_KEEP_MEM_NV(camera_z, projection);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    projection.z = -camera_z;
    projection.v10 = *((PackedPair *) (((u8 *) object) + 0xA2));
    projection.count = 4;
    projection.pad1A = 0;
    func_800DBA90(projection_ptr);
    min_xy |= 0x75300000;
    min_xy &= 0xFFFF0000;
    min_xy |= 0x7530;
    max_xy |= 0x8AD00000;
    max_xy &= 0xFFFF0000;
    max_xy |= 0x8AD0;
    do
    {
      s32 vertex_depth;
      s32 screen_x;
      u16 x_bits;
      s32 screen_y;
      u16 y_bits;
      vertex_depth = func_80065420(vertex_bytes, scratch.screen, (void *) depth_out_or_phase, (void *) depth_out_or_phase);
      depth += vertex_depth - 8;
      x_bits = (u16) scratch.screen[0];
      screen_x = scratch.screen[0];
      if (((s16) max_xy) < screen_x)
      {
        max_xy &= 0xFFFF0000;
        max_xy = x_bits | max_xy;
      }
      else if (screen_x < ((s16) min_xy))
      {
        min_xy &= 0xFFFF0000;
        min_xy = x_bits | min_xy;
      }
      screen_y = scratch.screen[1];
      y_bits = (u16) scratch.screen[1];
      if (((s16) (max_xy >> 16)) < screen_y)
      {
        max_xy &= 0xFFFF;
        max_xy |= y_bits << 16;
      }
      else if (screen_y < ((s16) (min_xy >> 16)))
      {
        min_xy &= 0xFFFF;
        min_xy |= y_bits << 16;
      }
      index_or_row--;
      vertex_bytes -= 8;
    }
    while (index_or_row >= 0);
    left_bound = (s16) min_xy;
    base_y = (s16) (min_xy >> 16);
    min_y = base_y;
    bounds[2] = (s16) (max_xy - min_xy);
    bounds[0] = left_bound;
    depth = depth >> 2;
    if ((*((u8 **) render_state)) != D_801C9E40)
    {
      ASM_KEEP_NV(base_y);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
      base_y += 0xE0;
    }
    max_y = (s16) (max_xy >> 16);
    height = max_y - min_y;
    bounds[1] = base_y;
    bounds[3] = height;
    if (((u32) depth) < 0x1E0U)
    {
      crop_y = (*((s16 *) (((u8 *) object) + 0x96))) - 0x34;
      if (crop_y < 0)
      {
        crop_y = 0;
      }
      height_pixels = (s16) height;
      crop_product = height_pixels * crop_y;
      crop_y = crop_product / 8;
      top_bound = (s16) base_y;
      bottom_bound = top_bound + height_pixels;
      top_copy = top_bound;
      last_y = bottom_bound;
      top_page = top_bound / 0xE0;
      top_page_index = top_page;
      if ((top_page_index != top_page) && (last_y != bottom_bound))
      {
        bottom_page = 0;
      }
      bottom_page = bottom_bound / 0xE0;
      bottom_y = last_y;
      if (top_page_index != bottom_page)
      {
        last_y = bottom_page * 0xE0;
      }
      scratch.outer = 4;
      tag_mask = 0x00FFFFFF;
      depth_offset = depth << 2;
      do
      {
        s32 layer;
        s32 phase_or_y;
        layer = scratch.outer;
        phase_or_y = (*((s16 *) (((u8 *) object) + 0x96))) + layer;
        depth_out_or_phase = phase_or_y << 7;
        if (!(layer & 1))
        {
          depth_out_or_phase += 0x800;
        }
        phase_or_y = bounds[1];
        index_or_row = phase_or_y + crop_y;
        first_y = index_or_row;
        if (last_y >= index_or_row)
        {
          row_span = bottom_y - index_or_row;
          row_count = row_span + 1;
          do
          {
            u8 *frame;
            u8 *depth_bucket;
            s32 next_phase;
            s32 layer_phase;
            s32 texture_width;
            s32 strip_y;
            s32 texture_step;
            s32 texture_top;
            s32 texture_bottom;
            s32 wave_x;
            s32 poly_link;
            s32 bucket_link;
            layer_phase = scratch.outer << 2;
            next_phase = depth_out_or_phase + 80;
            ASM_USE2_NV(depth_out_or_phase, next_phase);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            ASM_KEEP4_NV(layer_phase, layer_phase, layer_phase, layer_phase);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            depth_out_or_phase = next_phase + layer_phase;
            frame = *((u8 **) render_state);
            poly = *((u8 **) (frame + 0x8D0));
            *((u8 **) (frame + 0x8D0)) = poly + 40;
            *((s32 *) (((u8 *) poly) + 4)) = *((s32 *) (((u8 *) appearance) + 0xC));
            func_800666F4(poly);
            func_80066640(poly, 1);
            *((s16 *) (((u8 *) poly) + 0x16)) = (s16) func_80066460(2, ((u8 *) appearance)[0xC] != 0x80, 0x340, 0x100);
            *((u8 *) (((u8 *) poly) + 0x14)) = 0;
            *((u8 *) (((u8 *) poly) + 0x0C)) = 0;
            texture_width = ((u8 *) (&material))[4];
            *((s16 *) (((u8 *) poly) + 8)) = (s16) row_span;
            *((u8 *) (((u8 *) poly) + 0x24)) = texture_width;
            *((u8 *) (((u8 *) poly) + 0x1C)) = texture_width;
            if (((s16) row_span) == 0)
            {
              *((u16 *) (((u8 *) poly) + 8)) = (u16) row_count;
            }
            texture_step = ((s16 *) (&material))[3] * (index_or_row - first_y);
            texture_step = texture_step / (*((s16 *) (((u8 *) poly) + 8)));
            *((u8 *) (((u8 *) poly) + 0x1D)) = (u8) texture_step;
            *((u8 *) (((u8 *) poly) + 0x0D)) = (u8) texture_step;
            texture_step = ((s16 *) (&material))[3] / (*((s16 *) (((u8 *) poly) + 8)));
            texture_top = *((u8 *) (((u8 *) poly) + 0x0D));
            *((u8 *) (((u8 *) poly) + 0x25)) = (u8) texture_step;
            if (((u8) texture_step) >= 2)
            {
              texture_bottom = texture_top + (*((u8 *) (((u8 *) poly) + 0x25)));
            }
            else
            {
              texture_bottom = texture_top + 2;
            }
            *((u8 *) (((u8 *) poly) + 0x25)) = (u8) texture_bottom;
            *((u8 *) (((u8 *) poly) + 0x15)) = (u8) texture_bottom;
            wave_x = func_800644B8(depth_out_or_phase);
            wave_x = ((u16) bounds[0]) + (wave_x >> 9);
            *((s16 *) (((u8 *) poly) + 0x10)) = (s16) wave_x;
            *((s16 *) (((u8 *) poly) + 8)) = (s16) wave_x;
            wave_x = wave_x + ((u16) bounds[2]);
            *((s16 *) (((u8 *) poly) + 0x20)) = (s16) wave_x;
            *((s16 *) (((u8 *) poly) + 0x18)) = (s16) wave_x;
            strip_y = index_or_row - ((index_or_row / 0xE0) * 0xE0);
            index_or_row++;
            strip_y = strip_y - ((u16) scratch.outer);
            *((s16 *) (((u8 *) poly) + 0x1A)) = (s16) strip_y;
            *((s16 *) (((u8 *) poly) + 0x0A)) = (s16) strip_y;
            strip_y += 2;
            *((s16 *) (((u8 *) poly) + 0x22)) = (s16) strip_y;
            *((s16 *) (((u8 *) poly) + 0x12)) = (s16) strip_y;
            poly_link = *((s32 *) ((u8 *) (depth_offset + ((s32) (*((u8 **) render_state)))) + 0xB0));
            *((s32 *) (((u8 *) poly) + 0)) = ((*((s32 *) (((u8 *) poly) + 0))) & 0xFF000000) | (poly_link & tag_mask);
            depth_bucket = (u8 *) (depth_offset + ((s32) (*((u8 **) render_state))));
            bucket_link = *((s32 *) (((u8 *) depth_bucket) + 0xB0));
            *((s32 *) (((u8 *) depth_bucket) + 0xB0)) = (bucket_link & 0xFF000000) | (((s32) poly) & tag_mask);
          }
          while (last_y >= index_or_row);
        }
      }
      while ((--scratch.outer) > 0);
    }
    next_object = *((void **) (((u8 *) object_data) - 8));
    if (next_object == 0)
    {
      break;
    }
    object_data = ((u8 *) next_object) + 0x20;
    appearance = *((void **) (((u8 *) next_object) + 0xC));
  }

  return 0;
}
