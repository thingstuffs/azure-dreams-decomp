#include "common.h"

extern int D_800814C8;
extern int D_80081550;
extern int D_80081558;
extern int D_80081554;
extern unsigned char D_80071298[];
extern volatile int D_80071250[];
extern int D_800712B4[];
extern int D_80084130[3];
extern short D_80084808[8];
extern struct S_80083178 D_80083178;
extern struct S_80083178State D_80083CE8;
typedef struct
{
  s16 x;
  s16 y;
  s16 z;
  s16 pad;
} Vec16;
typedef struct 
{
  u8 u0;
  u8 pad01;
  u8 v0;
  u8 pad03;
  u8 du;
  u8 pad05;
  u8 dv;
  u8 pad07;
  s16 x0;
  s16 y0;
  s16 z0;
  s16 pad0e;
  s16 x1;
  s16 y1;
  s16 z1;
  s16 pad16;
  u32 color;
  s16 pad18;
  s16 pad1a;
  s16 angle;
  s16 depth;
  s16 depth_step;
  s16 scale;
  s16 base_angle;
  s16 angle_step;
  u16 tpage;
  s16 width;
  s16 height;
  u16 clut;
  u16 tex;
  s16 count;
} Item;
typedef struct 
{
  s16 x;
  s16 y;
  s16 z;
  s16 pad;
  Vec16 *p0;
  Vec16 *p1;
  s32 pad10;
  s16 sx;
  s16 pad16;
  s16 sy;
  s16 sz;
  s16 value;
  s16 pad1e;
  s16 one;
  s16 zero;
  s32 pad24;
} Transform;
typedef struct 
{
  u32 tag;
  u32 color;
  u8 data[0x2c];
} Primitive;
typedef struct 
{
  u8 pad00[0xB0];
  u32 ordering[0x1E0];
  u8 pad830[0xA0];
  Primitive *next_primitive;
} Dungeon;
extern u8 D_80083160[];
extern s32 func_800644B8(s32);
extern s32 func_800654B0(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80066640(Primitive *, s32);
extern void func_800666F4(Primitive *);
extern void func_800DBA90(Transform *);
/* Draw linked items as fading textured quads along interpolated, oscillating paths. */
s32 func_800DB660(Item *item)
{
  Vec16 local_vertices[4];
  Vec16 quad_vertices[4];
  Transform transform;
  s32 projection_scratch;
  Dungeon *dungeon_copy;
  s32 quad_index;
  s32 accum_x;
  s32 accum_y;
  s32 accum_z;
  s32 delta_x;
  s32 delta_y;
  s32 delta_z;
  s32 z_phase;
  s32 address_mask;
  Dungeon **dungeon_ptr;
  dungeon_ptr = (Dungeon **) D_80083160;
  address_mask = 0x00FFFFFF;
  for (;;)
  {
    s32 left_x = (-item->width) >> 1;
    s32 near_z;
    s32 right_x;
    s32 far_z;
    s32 color;
    s32 offset_phase;
    Item *current_item;
    Item *next_node;
    local_vertices[1].x = left_x;
    local_vertices[0].x = left_x;
    near_z = (-item->height) >> 1;
    local_vertices[2].z = near_z;
    local_vertices[0].z = near_z;
    right_x = left_x + ((u16) item->width);
    local_vertices[3].x = right_x;
    local_vertices[2].x = right_x;
    far_z = near_z + ((u16) item->height);
    local_vertices[3].z = far_z;
    local_vertices[1].z = far_z;
    local_vertices[3].y = 0;
    local_vertices[2].y = 0;
    local_vertices[1].y = 0;
    local_vertices[0].y = 0;
    quad_index = 0;
    current_item = item;
    z_phase = item->depth;
    offset_phase = item->base_angle;
    color = item->color;
    delta_x = item->x1 - item->x0;
    delta_y = item->y1 - item->y0;
    delta_z = item->z1 - item->z0;
    if (item->count >= 0)
    {
      accum_z = 0;
      accum_y = accum_z;
      accum_x = accum_y;
      do
      {
        Primitive *primitive;
        u8 *vertex_bytes;
        u32 *ordering_entry;
        void *vertex_0;
        void *vertex_2;
        void *vertex_3;
        void *vertex_1;
        s32 ordering_index;
        s32 wave_value;
        u8 u_start;
        u8 u_end;
        u8 v_start;
        u8 v_end;
        wave_value = func_800644B8(offset_phase);
        transform.x = (wave_value * current_item->scale) >> 12;
        transform.z = 0;
        transform.y = 0;
        transform.p0 = &transform.x;
        transform.p1 = &transform.x;
        transform.sx = current_item->tpage;
        transform.sy = current_item->x0 + (accum_x / current_item->count);
        transform.sz = current_item->y0 + (accum_y / current_item->count);
        wave_value = func_800644B8(z_phase);
        transform.value = (current_item->z0 + (accum_z / current_item->count)) + ((wave_value * current_item->angle) >> 12);
        transform.one = 1;
        transform.zero = 0;
        func_800DBA90((Transform *) (&transform.p0));
        vertex_bytes = (u8 *) quad_vertices;
        vertex_0 = vertex_bytes;
        vertex_2 = vertex_bytes + 16;
        vertex_3 = vertex_bytes + 24;
        quad_vertices[1].x = transform.x - (((s16) current_item->width) >> 1);
        quad_vertices[0].x = quad_vertices[1].x;
        quad_vertices[3].x = quad_vertices[0].x + current_item->width;
        quad_vertices[2].x = quad_vertices[3].x;
        quad_vertices[2].z = transform.z - (((s16) current_item->height) >> 1);
        quad_vertices[0].z = quad_vertices[2].z;
        quad_vertices[3].z = quad_vertices[2].z + current_item->height;
        quad_vertices[1].z = quad_vertices[3].z;
        quad_vertices[3].y = transform.y;
        quad_vertices[2].y = quad_vertices[3].y;
        quad_vertices[1].y = quad_vertices[2].y;
        quad_vertices[0].y = quad_vertices[1].y;
        z_phase += current_item->depth_step;
        vertex_1 = vertex_bytes + 8;
        {
          Dungeon *dungeon = *dungeon_ptr;
          primitive = dungeon->next_primitive;
          offset_phase += current_item->angle_step;
          dungeon->next_primitive = (Primitive *) (((u8 *) primitive) + 0x34);
        }
        ordering_index = func_800654B0(vertex_0, vertex_1, vertex_2, vertex_3, ((u8 *) primitive) + 8, ((u8 *) primitive) + 0x10, ((u8 *) primitive) + 0x18, ((u8 *) primitive) + 0x20, &projection_scratch, &projection_scratch) - 8;
        if (((u32) ordering_index) < 0x1E0)
        {
          primitive->color = color;
          func_800666F4(primitive);
          func_80066640(primitive, 1);
          *((u16 *) (((u8 *) primitive) + 0x16)) = current_item->clut;
          *((u16 *) (((u8 *) primitive) + 0x0E)) = current_item->tex;
          u_start = current_item->u0;
          *(((u8 *) primitive) + 0x14) = u_start;
          *(((u8 *) primitive) + 0x0C) = u_start;
          u_end = current_item->u0 + current_item->du;
          *(((u8 *) primitive) + 0x24) = u_end;
          *(((u8 *) primitive) + 0x1C) = u_end;
          v_start = current_item->v0;
          *(((u8 *) primitive) + 0x1D) = v_start;
          *(((u8 *) primitive) + 0x0D) = v_start;
          v_end = current_item->v0 + current_item->dv;
          *(((u8 *) primitive) + 0x25) = v_end;
          *(((u8 *) primitive) + 0x15) = v_end;
          {
            Dungeon *dungeon = *dungeon_ptr;
            Dungeon *ordering_dungeon;
            u32 chain_tag;
            chain_tag = (primitive->tag & 0xFF000000) | (dungeon->ordering[ordering_index] & address_mask);
            primitive->tag = chain_tag;
            dungeon_copy = *dungeon_ptr;
            ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            ordering_dungeon = dungeon_copy;
            ordering_dungeon->ordering[ordering_index] = (ordering_dungeon->ordering[ordering_index] & 0xFF000000) | (((u32) primitive) & address_mask);
          }
        }
        if (color > 0x80807)
        {
          color -= 0x80808;
        }
        accum_z += delta_z;
        accum_y += delta_y;
        accum_x += delta_x;
        quad_index++;
      }
      while (quad_index <= current_item->count);
    }
    next_node = *((Item **) (((u8 *) item) - 8));
    if (next_node == 0)
    {
      break;
    }
    item = (Item *) (((u8 *) next_node) + 0x20);
  }

  return 0;
}
