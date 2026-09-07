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
s32 func_800DB660(Item *item)
{
  Vec16 source[4];
  Vec16 projected[4];
  Transform transform;
  s32 call_scratch;
  Dungeon *new_var;
  s32 iteration;
  s32 step_x;
  s32 step_y;
  s32 step_z;
  s32 delta_x;
  s32 delta_y;
  s32 delta_z;
  s32 base_angle;
  s32 mask;
  Dungeon **context_p;
  context_p = (Dungeon **) D_80083160;
  mask = 0x00FFFFFF;
  for (;;)
  {
    s32 half_width = (-item->width) >> 1;
    s32 half_height;
    s32 end_width;
    s32 end_height;
    s32 color;
    s32 depth;
    Item *held_item;
    Item *next_item;
    source[1].x = half_width;
    source[0].x = half_width;
    half_height = (-item->height) >> 1;
    source[2].z = half_height;
    source[0].z = half_height;
    end_width = half_width + ((u16) item->width);
    source[3].x = end_width;
    source[2].x = end_width;
    end_height = half_height + ((u16) item->height);
    source[3].z = end_height;
    source[1].z = end_height;
    source[3].y = 0;
    source[2].y = 0;
    source[1].y = 0;
    source[0].y = 0;
    iteration = 0;
    held_item = item;
    base_angle = item->depth;
    depth = item->base_angle;
    color = item->color;
    delta_x = item->x1 - item->x0;
    delta_y = item->y1 - item->y0;
    delta_z = item->z1 - item->z0;
    if (item->count >= 0)
    {
      step_z = 0;
      step_y = step_z;
      step_x = step_y;
      do
      {
        Primitive *primitive;
        u8 *projected_base;
        u32 *ordering_entry;
        void *p0;
        void *p2;
        void *p3;
        void *p1;
        s32 ordering_index;
        s32 trig;
        u8 u_value;
        u8 u_end;
        u8 v_value;
        u8 v_end;
        trig = func_800644B8(depth);
        transform.x = (trig * held_item->scale) >> 12;
        transform.z = 0;
        transform.y = 0;
        transform.p0 = &transform.x;
        transform.p1 = &transform.x;
        transform.sx = held_item->tpage;
        transform.sy = held_item->x0 + (step_x / held_item->count);
        transform.sz = held_item->y0 + (step_y / held_item->count);
        trig = func_800644B8(base_angle);
        transform.value = (held_item->z0 + (step_z / held_item->count)) + ((trig * held_item->angle) >> 12);
        transform.one = 1;
        transform.zero = 0;
        func_800DBA90((Transform *) (&transform.p0));
        projected_base = (u8 *) projected;
        p0 = projected_base;
        p2 = projected_base + 16;
        p3 = projected_base + 24;
        projected[1].x = transform.x - (((s16) held_item->width) >> 1);
        projected[0].x = projected[1].x;
        projected[3].x = projected[0].x + held_item->width;
        projected[2].x = projected[3].x;
        projected[2].z = transform.z - (((s16) held_item->height) >> 1);
        projected[0].z = projected[2].z;
        projected[3].z = projected[2].z + held_item->height;
        projected[1].z = projected[3].z;
        projected[3].y = transform.y;
        projected[2].y = projected[3].y;
        projected[1].y = projected[2].y;
        projected[0].y = projected[1].y;
        base_angle += held_item->depth_step;
        p1 = projected_base + 8;
        {
          Dungeon *dungeon = *context_p;
          primitive = dungeon->next_primitive;
          depth += held_item->angle_step;
          dungeon->next_primitive = (Primitive *) (((u8 *) primitive) + 0x34);
        }
        ordering_index = func_800654B0(p0, p1, p2, p3, ((u8 *) primitive) + 8, ((u8 *) primitive) + 0x10, ((u8 *) primitive) + 0x18, ((u8 *) primitive) + 0x20, &call_scratch, &call_scratch) - 8;
        if (((u32) ordering_index) < 0x1E0)
        {
          primitive->color = color;
          func_800666F4(primitive);
          func_80066640(primitive, 1);
          *((u16 *) (((u8 *) primitive) + 0x16)) = held_item->clut;
          *((u16 *) (((u8 *) primitive) + 0x0E)) = held_item->tex;
          u_value = held_item->u0;
          *(((u8 *) primitive) + 0x14) = u_value;
          *(((u8 *) primitive) + 0x0C) = u_value;
          u_end = held_item->u0 + held_item->du;
          *(((u8 *) primitive) + 0x24) = u_end;
          *(((u8 *) primitive) + 0x1C) = u_end;
          v_value = held_item->v0;
          *(((u8 *) primitive) + 0x1D) = v_value;
          *(((u8 *) primitive) + 0x0D) = v_value;
          v_end = held_item->v0 + held_item->dv;
          *(((u8 *) primitive) + 0x25) = v_end;
          *(((u8 *) primitive) + 0x15) = v_end;
          {
            Dungeon *dungeon = *context_p;
            Dungeon *next_dungeon;
            u32 tag;
            tag = (primitive->tag & 0xFF000000) | (dungeon->ordering[ordering_index] & mask);
            primitive->tag = tag;
            new_var = *context_p;
            ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            next_dungeon = new_var;
            next_dungeon->ordering[ordering_index] = (next_dungeon->ordering[ordering_index] & 0xFF000000) | (((u32) primitive) & mask);
          }
        }
        if (color > 0x80807)
        {
          color -= 0x80808;
        }
        step_z += delta_z;
        step_y += delta_y;
        step_x += delta_x;
        iteration++;
      }
      while (iteration <= held_item->count);
    }
    next_item = *((Item **) (((u8 *) item) - 8));
    if (next_item == 0)
    {
      break;
    }
    item = (Item *) (((u8 *) next_item) + 0x20);
  }

  return 0;
}
