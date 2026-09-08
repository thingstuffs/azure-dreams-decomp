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

/* Renders linked textured sprites with dimmed offset copies near the screen center. */
s32 func_800345B8(u8 *node_data, u8 *position, u8 *render_state)
{
  u8 *scratch;
  register void *fixed_matrix ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it slus-diff; the source shape that makes it unnecessary has not been found */
  u8 *sprite_data;
  s32 base_x;
  s32 center_x;
  s32 center_y;
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
  s32 amplitude_addr;
  void *source_matrix;
  u8 *record;
  u8 *prim;
  s32 scale;
  s32 abs_offset;
  s32 vertex_coord;
  s32 screen_coord;
  s32 visible_0;
  s32 visible_1;
  s32 visible_01;
  s32 visible_2;
  s32 visible_012;
  s32 visible_3;
  s32 u_end;
  s32 v_end;
  s32 v_end_bits;
  s32 v_start_bits;
  u16 texture_page;
  u16 texture_bias;
  s32 packed_uv;
  u8 draw_code;
  u8 blend_code;
  void *next_node;
  u8 *copy_matrix_a;
  u8 *copy_matrix_b;
  RenderPool **render_pools;
  u8 *matrix_page;
  RenderPool *render_pool;
  u8 *next_prim;
  matrix_page = (u8 *) 0x80070000;
  copy_matrix_a = D_8006A84C;
  copy_matrix_b = D_8006CD10;
  scratch = (u8 *) 0x1F800000;
  render_pool = D_80083160[0];
  next_prim = render_pool->next_prim;
  *((volatile s32 *) (scratch + 0x24)) = (s32) (((u8 *) render_pool) + 0xB0);
  *((volatile s32 *) (scratch + 0xE4)) = 0;
  *((volatile s32 *) (scratch + 0x1C)) = (s32) next_prim;
  render_pools = D_80083160;
  fixed_matrix = (void *) 0x1F8000C8;
  do
  {
    *((u16 *) (scratch + 0x04)) = *((u16 *) (position + 2));
    *((u16 *) (scratch + 0x06)) = *((u16 *) (position + 6));
    *((u16 *) (scratch + 0x08)) = *((u16 *) (position + 10));
    *((s32 *) (scratch + 0xC4)) = RotTransPers(scratch + 0x04, scratch + 0xBC, scratch + 0x94, scratch + 0x98);
    *((u16 *) (render_state + 0x14)) |= 0x8000;
    D_8006CD4C[0] = (scaled_depth = (*((s32 *) (scratch + 0xC4))) << 2);
    *((s32 *) (copy_matrix_b + 0x1C)) = scaled_depth;
    *((s32 *) (copy_matrix_a + 0x1C)) = scaled_depth;
    depth_value = (*((s32 *) (scratch + 0xC4))) - (*((s16 *) (render_state + 0x06)));
    *((s32 *) (scratch + 0xC4)) = depth_value;
    if (((u32) depth_value) < 0x1E0)
    {
      copies = 1;
      do
      {
        PushMatrix();
        center_x = (*((u16 *) (scratch + 0xBC))) - 0xA0;
        center_y = (*((u16 *) (scratch + 0xBE))) - 0x78;
        *((volatile u16 *) (scratch + 0xBC)) = center_x;
      } while (0);
      base_x = center_x;
      abs_offset = (s16) base_x;
      if (abs_offset < 0)
      {
        abs_offset = -abs_offset;
      }
      *((u16 *) (scratch + 0xBE)) = center_y;
      base_y = center_y;
      if (abs_offset < 0x330)
      {
        abs_offset = (s16) center_y;
        if (abs_offset < 0)
        {
          abs_offset = -abs_offset;
        }
        if (abs_offset < 0x330)
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
          *((s32 *) (scratch + 0xC4)) = 10;
          sin_x = rsin(ratan2((s16) base_x, 0x200));
          amplitude_addr = (s32) D_8006A83E;
          amplitude = (s16 *) (amplitude_addr + (copy_index << 1));
          product_x = (*amplitude) * sin_x;
          if (product_x < 0)
          {
            product_x += 0xFFF;
          }
          *((u16 *) (scratch + 0xBC)) = base_x - (product_x >> 12);
          sin_y = rsin(ratan2((s16) base_y, 0x200));
          product_y = (*amplitude) * sin_y;
          if (product_y < 0)
          {
            product_y += 0xFFF;
          }
          *((u16 *) (scratch + 0xBE)) = base_y - (product_y >> 12);
        }

        *((u16 *) (scratch + 0xF8)) = *((u16 *) (render_state + 0x16));
        *((u16 *) (scratch + 0xFA)) = *((u16 *) (render_state + 0x18));
        *((u16 *) (scratch + 0xFC)) = *((u16 *) (render_state + 0x1A));
        scale = *((u16 *) (render_state + 0x20));
        *((s32 *) (scratch + 0xDC)) = scale;
        *((u16 *) (scratch + 0x100)) = scale;
        scale = *((u16 *) (render_state + 0x22));
        *((s32 *) (scratch + 0xE0)) = scale;
        *((u16 *) (scratch + 0x102)) = scale;
        RotMatrix(scratch + 0xF8, fixed_matrix);
        if (copy_index != 0)
        {
          if (D_8006A847[copy_index] != 0)
          {
            source_matrix = matrix_page - 0x57B4;
          }
          else
          {
            ASM_USE_NV(scratch);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            source_matrix = matrix_page - 0x32F0;
          }
          CompMatrix(source_matrix, fixed_matrix, scratch + 0x54);
        }
        else
        {
          CompMatrix(D_8006CD30, fixed_matrix, scratch + 0x54);
        }
        SetTransMatrix(scratch + 0x54);
        SetRotMatrix(scratch + 0x54);
        record = *((u8 **) (render_state + 0x08));
        sprite_data = record + 1;
        *((u16 *) (scratch + 0x28)) = *((u16 *) (render_state + 0x14));
        record_loop:
        if (!(record[0] & 0x20))
        {
          prim = (u8 *) (*((s32 *) (scratch + 0x1C)));
          *((s32 *) (scratch + 0x1C)) = (s32) (prim + 0x28);
          *((s32 *) (scratch + 0x0C)) = sprite_data[7];
          *((s32 *) (scratch + 0x10)) = sprite_data[8];
          *((s32 *) (scratch + 0x14)) = sprite_data[9];
          *((s32 *) (scratch + 0x18)) = sprite_data[10];
          if ((record[0] ^ (*((u16 *) (scratch + 0x28)))) & 1)
          {
            vertex_coord = (-((s8) (*((volatile u8 *) (sprite_data + 1))))) - (*((u16 *) (scratch + 0x100)));
            *((u16 *) (scratch + 0x84)) = vertex_coord;
            *((u16 *) (scratch + 0x74)) = vertex_coord;
            vertex_coord -= *((u16 *) (scratch + 0x14));
          }
          else
          {
            vertex_coord = ((s8) (*((volatile u8 *) (sprite_data + 1)))) - (*((u16 *) (scratch + 0x100)));
            *((u16 *) (scratch + 0x84)) = vertex_coord;
            *((u16 *) (scratch + 0x74)) = vertex_coord;
            vertex_coord += *((u16 *) (scratch + 0x14));
          }
          *((u16 *) (scratch + 0x8C)) = vertex_coord;
          *((u16 *) (scratch + 0x7C)) = vertex_coord;
          if ((record[0] ^ (*((u16 *) (scratch + 0x28)))) & 2)
          {
            vertex_coord = (-((s8) (*((volatile u8 *) (sprite_data + 2))))) - (*((u16 *) (scratch + 0x102)));
            *((u16 *) (scratch + 0x7E)) = vertex_coord;
            *((u16 *) (scratch + 0x76)) = vertex_coord;
            vertex_coord -= *((u16 *) (scratch + 0x18));
            *((u16 *) (scratch + 0x8E)) = vertex_coord;
            *((u16 *) (scratch + 0x86)) = vertex_coord;
          }
          else
          {
            vertex_coord = ((s8) (*((volatile u8 *) (sprite_data + 2)))) - (*((u16 *) (scratch + 0x102)));
            *((u16 *) (scratch + 0x7E)) = vertex_coord;
            *((u16 *) (scratch + 0x76)) = vertex_coord;
            vertex_coord += *((u16 *) (scratch + 0x18));
            *((u16 *) (scratch + 0x8E)) = vertex_coord;
            *((u16 *) (scratch + 0x86)) = vertex_coord;
          }
          *((u16 *) (scratch + 0x90)) = 0;
          *((u16 *) (scratch + 0x88)) = 0;
          *((u16 *) (scratch + 0x80)) = 0;
          *((u16 *) (scratch + 0x78)) = 0;
          RotTransPers4(scratch + 0x74, scratch + 0x7C, scratch + 0x84, scratch + 0x8C, scratch + 0xE8, scratch + 0xEC, scratch + 0xF0, scratch + 0xF4, scratch + 0x94, scratch + 0x98);
          screen_coord = *((u16 *) (scratch + 0xE8));
          screen_coord += *((u16 *) (scratch + 0xBC));
          *((s16 *) (prim + 0x08)) = screen_coord;
          screen_coord = *((u16 *) (scratch + 0xEA));
          screen_coord += *((u16 *) (scratch + 0xBE));
          *((s16 *) (prim + 0x0A)) = screen_coord;
          screen_coord = *((u16 *) (scratch + 0xEC));
          screen_coord += *((u16 *) (scratch + 0xBC));
          *((s16 *) (prim + 0x10)) = screen_coord;
          screen_coord = *((u16 *) (scratch + 0xEE));
          screen_coord += *((u16 *) (scratch + 0xBE));
          *((s16 *) (prim + 0x12)) = screen_coord;
          screen_coord = *((u16 *) (scratch + 0xF0));
          screen_coord += *((u16 *) (scratch + 0xBC));
          *((s16 *) (prim + 0x18)) = screen_coord;
          screen_coord = *((u16 *) (scratch + 0xF2));
          screen_coord += *((u16 *) (scratch + 0xBE));
          *((s16 *) (prim + 0x1A)) = screen_coord;
          *((s16 *) (prim + 0x20)) = (*((u16 *) (scratch + 0xF4))) + (*((u16 *) (scratch + 0xBC)));
          *((s16 *) (prim + 0x22)) = (*((u16 *) (scratch + 0xF6))) + (*((u16 *) (scratch + 0xBE)));
          visible_0 = 0;
          if (((u16) ((*((s16 *) (prim + 0x08))) + 0x20)) < 0x181)
          {
            visible_0 = ((u16) ((*((s16 *) (prim + 0x0A))) + 0x20)) < 0x121;
          }
          visible_1 = 0;
          if (((u16) ((*((s16 *) (prim + 0x10))) + 0x20)) < 0x181)
          {
            visible_1 = ((u16) ((*((s16 *) (prim + 0x12))) + 0x20)) < 0x121;
          }
          visible_01 = visible_0 | visible_1;
          visible_2 = 0;
          if (((u16) ((*((s16 *) (prim + 0x18))) + 0x20)) < 0x181)
          {
            visible_2 = ((u16) ((*((s16 *) (prim + 0x1A))) + 0x20)) < 0x121;
          }
          visible_012 = visible_01 | visible_2;
          visible_3 = 0;
          if (((u16) ((*((s16 *) (prim + 0x20))) + 0x20)) < 0x181)
          {
            visible_3 = ((u16) ((*((s16 *) (prim + 0x22))) + 0x20)) < 0x121;
          }
          if (visible_012 | visible_3)
          {
            prim[3] = 9;
            *((u16 *) (render_state + 0x14)) &= 0x7FFF;
            u_end = (*((s32 *) (scratch + 0x14))) + (*((s32 *) (scratch + 0x0C)));
            *((s32 *) (scratch + 0x14)) = u_end;
            if (u_end & 0x100)
            {
              *((s32 *) (scratch + 0x14)) = u_end - 1;
            }
            v_end = (*((s32 *) (scratch + 0x18))) + (*((s32 *) (scratch + 0x10)));
            *((s32 *) (scratch + 0x18)) = v_end;
            if (v_end & 0x100)
            {
              *((s32 *) (scratch + 0x18)) = v_end - 1;
            }
            v_end_bits = (*((s32 *) (scratch + 0x18))) << 8;
            v_start_bits = (*((s32 *) (scratch + 0x10))) << 8;
            *((s32 *) (scratch + 0x18)) = v_end_bits;
            *((s32 *) (scratch + 0x10)) = v_start_bits;
            *((u32 *) (prim + 0x0C)) = (v_start_bits + (*((s32 *) (scratch + 0x0C)))) + (((*((u16 *) (render_state + 0x12))) + (*((u16 *) (sprite_data + 5)))) << 16);
            if (copy_index != 0)
            {
              packed_uv = *((u16 *) (scratch + 0x10));
              packed_uv += *((u16 *) (scratch + 0x14));
              *((u16 *) (prim + 0x14)) = packed_uv;
              texture_bias = *((u16 *) (render_state + 0x10));
              if (texture_bias != 0)
              {
                texture_page = (texture_bias + ((*((u16 *) (sprite_data + 3))) & 0xFF9F)) | 0x20;
              }
              else
              {
                texture_page = (*((u16 *) (sprite_data + 3))) | 0x20;
              }
            }
            else
            {
              packed_uv = *((u16 *) (scratch + 0x10));
              packed_uv += *((u16 *) (scratch + 0x14));
              *((u16 *) (prim + 0x14)) = packed_uv;
              texture_bias = *((u16 *) (render_state + 0x10));
              if (texture_bias != 0)
              {
                texture_page = texture_bias + ((*((u16 *) (sprite_data + 3))) & 0xFF9F);
              }
              else
              {
                texture_page = *((u16 *) (sprite_data + 3));
              }
            }
            *((u16 *) (prim + 0x16)) = texture_page;
            packed_uv = *((u16 *) (scratch + 0x18));
            packed_uv += *((u16 *) (scratch + 0x0C));
            *((u16 *) (prim + 0x1C)) = packed_uv;
            *((u16 *) (prim + 0x24)) = (*((u16 *) (scratch + 0x18))) + (*((u16 *) (scratch + 0x14)));
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
            draw_code = sprite_data[0];
            render_state[0x0F] = draw_code;
            if (copy_index != 0)
            {
              ASM_USE_NV(scratch);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
              blend_code = draw_code | 2;
              render_state[0x0F] = blend_code;
            }
            else if ((*((u16 *) (scratch + 0x28))) & 8)
            {
              if (!((*((u16 *) (scratch + 0x28))) & 4))
              {
                blend_code = draw_code & 0xFD;
              }
              else
              {
                blend_code = draw_code | 2;
              }
              render_state[0x0F] = blend_code;
            }
            if ((*((u16 *) (scratch + 0x28))) & 0x10)
            {
              render_state[0x0F] &= 0xFE;
            }
            else
            {
              render_state[0x0F] |= 1;
            }
            *((u32 *) (prim + 4)) = *((u32 *) (render_state + 0x0C));
            if (copy_index != 0)
            {
              prim[4] >>= 2;
              prim[5] >>= 2;
              prim[6] >>= 2;
            }
            AddPrim((void *) ((*((s32 *) (scratch + 0x24))) + ((*((s32 *) (scratch + 0xC4))) << 2)), prim);
          }
        }

        sprite_data += 0x0C;
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
    next_node = *((void **) (node_data - 8));
    if (next_node != 0)
    {
      node_data = ((u8 *) next_node) + 0x20;
      position = *((u8 **) (((u8 *) next_node) + 8));
      render_state = *((u8 **) (((u8 *) next_node) + 0x0C));
    }
  }
  while (next_node != 0);
  render_pools[0]->next_prim = (u8 *) (*((s32 *) (scratch + 0x1C)));
  return 0;
}
