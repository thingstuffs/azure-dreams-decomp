#include "common.h"

typedef struct 
{
  volatile u16 x;
  volatile u16 y;
} DungeonPosition;
typedef struct 
{
  u8 pad0[4];
  u16 flags;
  u16 texture;
  u8 x0;
  u8 y0;
  u8 x1;
  u8 y1;
  u8 x2;
  u8 y2;
  u16 count;
  s32 value0;
  s32 value1;
} DungeonParameters;
typedef struct 
{
  u8 pad[0x8D0];
  u8 * volatile cursor;
} DungeonState;
extern u8 D_80083160[];
extern s32 func_800644B8(s32 value);
extern s32 func_80064584(s32 value);
extern void func_8006658C(s32 arg0, u8 *arg1);
extern void func_8006671C(u8 *arg0);
/* Emit textured ellipse segments around the given position. */
void func_800B84E4(DungeonPosition *position, DungeonParameters *parameters, s32 draw_order, s32 blend_mode)
{
  volatile u8 *scratchpad;
  u8 *cursor;
  u8 *packet_code;
  s32 blend_setting;
  s32 segment;
  s32 outer_color2;
  s32 angle_step;
  s32 trig_value;
  s32 center_u;
  s32 center_v;
  s32 texture_page;
  s32 center_xy;
  s32 outer_color3;
  register u8 *state_base ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  u8 *quad_packet;
  register s32 packet_order ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  state_base = D_80083160 - 0x3160;
  cursor = (*((DungeonState **) (state_base + 0x3160)))->cursor;
  scratchpad = (volatile u8 *) 0x1F800000;
  *((volatile u16 *) (((volatile u8 *) scratchpad) + 0x74)) = 0;
  *((volatile u16 *) (((volatile u8 *) scratchpad) + 0x7C)) = 0;
  *((volatile u16 *) (((volatile u8 *) scratchpad) + 0x78)) = position->x + parameters->x2;
  *((volatile u16 *) (((volatile u8 *) scratchpad) + 0x7A)) = position->y;
  *((volatile s32 *) (((volatile u8 *) scratchpad) + 8)) = parameters->x0;
  *((volatile s32 *) (((volatile u8 *) scratchpad) + 0xC)) = parameters->y0;
  *((volatile s32 *) (((volatile u8 *) scratchpad) + 0x10)) = parameters->x1;
  *((volatile s32 *) (((volatile u8 *) scratchpad) + 0x14)) = parameters->y1;
  ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
  segment = 0;
  if (parameters->count != 0)
  {
    blend_setting = blend_mode & 0xFFFF;
    packet_code = cursor + 7;
    angle_step = segment;
    do
    {
      *((volatile s32 *) (((volatile u8 *) scratchpad) + 0x70)) = *((volatile s32 *) (((volatile u8 *) scratchpad) + 0x78));
      center_u = ((*((volatile s32 *) (((volatile u8 *) scratchpad) + 0x10))) >> 1) + (*((volatile u8 *) (((volatile u8 *) scratchpad) + 8)));
      *((volatile u8 *) (((volatile u8 *) packet_code) + 17)) = center_u;
      *((volatile u8 *) (((volatile u8 *) packet_code) + 5)) = center_u;
      center_v = ((*((volatile s32 *) (((volatile u8 *) scratchpad) + 0x14))) >> 1) + (*((volatile u8 *) (((volatile u8 *) scratchpad) + 0xC)));
      *((volatile u8 *) (((volatile u8 *) packet_code) + 18)) = center_v;
      *((volatile u8 *) (((volatile u8 *) packet_code) + 6)) = center_v;
      trig_value = func_80064584(angle_step / parameters->count);
      segment += 1;
      ASM_USE(segment);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
      {
        s32 u_offset;
        register s32 scaled_offset ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        u_offset = *((volatile s32 *) (((volatile u8 *) scratchpad) + 0x10));
        scaled_offset = u_offset * trig_value;
        ASM_USE2_NV(u_offset, scaled_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        u_offset = scaled_offset >> 13;
        *((volatile u8 *) (((volatile u8 *) packet_code) + 41)) = (*((volatile u8 *) (((volatile u8 *) packet_code) + 5))) + u_offset;
      }
      trig_value = func_800644B8(angle_step / parameters->count);
      do {
          angle_step += 0x1000;
      } while (0);
      {
        s32 v_offset;
        register s32 scaled_offset ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        v_offset = *((volatile s32 *) (((volatile u8 *) scratchpad) + 0x14));
        scaled_offset = v_offset * trig_value;
        ASM_USE2_NV(v_offset, scaled_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        v_offset = scaled_offset >> 13;
        *((volatile u8 *) (((volatile u8 *) packet_code) + 42)) = (*((volatile u8 *) (((volatile u8 *) packet_code) + 6))) + v_offset;
      }
      trig_value = func_80064584(angle_step / parameters->count);
      {
        s32 x_offset;
        register s32 scaled_offset ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        x_offset = parameters->x2;
        scaled_offset = x_offset * trig_value;
        ASM_USE2_NV(x_offset, scaled_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        x_offset = scaled_offset >> 12;
        *((volatile u16 *) (((volatile u8 *) scratchpad) + 0x78)) = position->x + x_offset;
      }
      ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
      trig_value = func_800644B8(angle_step / parameters->count);
      {
        s32 y_offset;
        register s32 scaled_offset ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        y_offset = parameters->y2;
        scaled_offset = y_offset * trig_value;
        ASM_USE2_NV(y_offset, scaled_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        y_offset = scaled_offset >> 12;
        *((volatile u16 *) (((volatile u8 *) scratchpad) + 0x7A)) = position->y + y_offset;
      }
      center_xy = *((volatile s32 *) (((volatile u8 *) position) + 0));
      *((volatile s32 *) (((volatile u8 *) packet_code) + 13)) = center_xy;
      *((volatile s32 *) (((volatile u8 *) packet_code) + 1)) = center_xy;
      *((volatile s32 *) (((volatile u8 *) packet_code) + 25)) = *((volatile s32 *) (((volatile u8 *) scratchpad) + 0x78));
      *((volatile s32 *) (((volatile u8 *) packet_code) + 37)) = *((volatile s32 *) (((volatile u8 *) scratchpad) + 0x70));
      trig_value = func_80064584(angle_step / parameters->count);
      {
        s32 u_offset;
        register s32 scaled_offset ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        u_offset = *((volatile s32 *) (((volatile u8 *) scratchpad) + 0x10));
        scaled_offset = u_offset * trig_value;
        ASM_USE2_NV(u_offset, scaled_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        u_offset = scaled_offset >> 13;
        *((volatile u8 *) (((volatile u8 *) packet_code) + 29)) = (*((volatile u8 *) (((volatile u8 *) packet_code) + 5))) + u_offset;
      }
      trig_value = func_800644B8(angle_step / parameters->count);
      {
        s32 v_offset;
        register s32 scaled_offset ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        v_offset = *((volatile s32 *) (((volatile u8 *) scratchpad) + 0x14));
        scaled_offset = v_offset * trig_value;
        ASM_USE2_NV(v_offset, scaled_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        v_offset = scaled_offset >> 13;
        *((volatile u8 *) (((volatile u8 *) packet_code) + 30)) = (*((volatile u8 *) (((volatile u8 *) packet_code) + 6))) + v_offset;
      }
      *((volatile u16 *) (((volatile u8 *) packet_code) + 7)) = parameters->texture;
      texture_page = parameters->flags;
      ASM_KEEP(packet_code);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
      *((u16 *) (((u8 *) packet_code) + 19)) = texture_page;
      if (blend_setting != 0)
      {
        *((u16 *) (((u8 *) packet_code) + 19)) = (texture_page & 0xFF9F) | ((blend_setting - 1) << 5);
      }
      *((volatile s32 *) (((volatile u8 *) (packet_code - 3)) + 0)) = parameters->value0;
      *((volatile s32 *) (((volatile u8 *) packet_code) + 9)) = parameters->value0;
      outer_color2 = parameters->value1;
      *((volatile s32 *) (((volatile u8 *) packet_code) + 21)) = outer_color2;
      quad_packet = cursor;
      outer_color3 = parameters->value1;
      *((s32 *) (((u8 *) packet_code) + 33)) = outer_color3;
      func_8006671C(quad_packet);
      packet_order = draw_order;
      if (blend_setting != 0)
      {
        *((volatile u8 *) (((volatile u8 *) packet_code) + 0)) |= 2;
      }
      func_8006658C(packet_order, cursor);
      packet_code += 52;
      cursor += 52;
    }
    while (segment < parameters->count);
  }
  {
    register u8 *state_slot ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    state_slot = D_80083160;
    ASM_KEEP(state_slot);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    (*((DungeonState **) state_slot))->cursor = cursor;
  }
}
