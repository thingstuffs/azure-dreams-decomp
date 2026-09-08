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
void func_800B84E4(DungeonPosition *position, DungeonParameters *parameters, s32 arg2, s32 arg3)
{
  volatile u8 *hw;
  u8 *cursor;
  u8 *vertex;
  s32 flag;
  s32 index;
  s32 new_var;
  s32 phase;
  s32 angle;
  s32 x_value;
  s32 y_value;
  s32 flags_value;
  s32 position_word;
  s32 final_value;
  register u8 *global_page ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  u8 *geometry_arg;
  register s32 setup_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  global_page = D_80083160 - 0x3160;
  cursor = (*((DungeonState **) (global_page + 0x3160)))->cursor;
  hw = (volatile u8 *) 0x1F800000;
  *((volatile u16 *) (((volatile u8 *) hw) + 0x74)) = 0;
  *((volatile u16 *) (((volatile u8 *) hw) + 0x7C)) = 0;
  *((volatile u16 *) (((volatile u8 *) hw) + 0x78)) = position->x + parameters->x2;
  *((volatile u16 *) (((volatile u8 *) hw) + 0x7A)) = position->y;
  *((volatile s32 *) (((volatile u8 *) hw) + 8)) = parameters->x0;
  *((volatile s32 *) (((volatile u8 *) hw) + 0xC)) = parameters->y0;
  *((volatile s32 *) (((volatile u8 *) hw) + 0x10)) = parameters->x1;
  *((volatile s32 *) (((volatile u8 *) hw) + 0x14)) = parameters->y1;
  ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
  index = 0;
  if (parameters->count != 0)
  {
    flag = arg3 & 0xFFFF;
    vertex = cursor + 7;
    phase = index;
    do
    {
      *((volatile s32 *) (((volatile u8 *) hw) + 0x70)) = *((volatile s32 *) (((volatile u8 *) hw) + 0x78));
      x_value = ((*((volatile s32 *) (((volatile u8 *) hw) + 0x10))) >> 1) + (*((volatile u8 *) (((volatile u8 *) hw) + 8)));
      *((volatile u8 *) (((volatile u8 *) vertex) + 17)) = x_value;
      *((volatile u8 *) (((volatile u8 *) vertex) + 5)) = x_value;
      y_value = ((*((volatile s32 *) (((volatile u8 *) hw) + 0x14))) >> 1) + (*((volatile u8 *) (((volatile u8 *) hw) + 0xC)));
      *((volatile u8 *) (((volatile u8 *) vertex) + 18)) = y_value;
      *((volatile u8 *) (((volatile u8 *) vertex) + 6)) = y_value;
      angle = func_80064584(phase / parameters->count);
      index += 1;
      ASM_USE(index);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
      {
        s32 value;
        register s32 product ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        value = *((volatile s32 *) (((volatile u8 *) hw) + 0x10));
        product = value * angle;
        ASM_USE2_NV(value, product);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        value = product >> 13;
        *((volatile u8 *) (((volatile u8 *) vertex) + 41)) = (*((volatile u8 *) (((volatile u8 *) vertex) + 5))) + value;
      }
      angle = func_800644B8(phase / parameters->count);
      phase += 0x1000;
      ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
      {
        s32 value;
        register s32 product ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        value = *((volatile s32 *) (((volatile u8 *) hw) + 0x14));
        product = value * angle;
        ASM_USE2_NV(value, product);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        value = product >> 13;
        *((volatile u8 *) (((volatile u8 *) vertex) + 42)) = (*((volatile u8 *) (((volatile u8 *) vertex) + 6))) + value;
      }
      angle = func_80064584(phase / parameters->count);
      {
        s32 value;
        register s32 product ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        value = parameters->x2;
        product = value * angle;
        ASM_USE2_NV(value, product);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        value = product >> 12;
        *((volatile u16 *) (((volatile u8 *) hw) + 0x78)) = position->x + value;
      }
      ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
      angle = func_800644B8(phase / parameters->count);
      {
        s32 value;
        register s32 product ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        value = parameters->y2;
        product = value * angle;
        ASM_USE2_NV(value, product);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        value = product >> 12;
        *((volatile u16 *) (((volatile u8 *) hw) + 0x7A)) = position->y + value;
      }
      position_word = *((volatile s32 *) (((volatile u8 *) position) + 0));
      *((volatile s32 *) (((volatile u8 *) vertex) + 13)) = position_word;
      *((volatile s32 *) (((volatile u8 *) vertex) + 1)) = position_word;
      *((volatile s32 *) (((volatile u8 *) vertex) + 25)) = *((volatile s32 *) (((volatile u8 *) hw) + 0x78));
      *((volatile s32 *) (((volatile u8 *) vertex) + 37)) = *((volatile s32 *) (((volatile u8 *) hw) + 0x70));
      angle = func_80064584(phase / parameters->count);
      {
        s32 value;
        register s32 product ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        value = *((volatile s32 *) (((volatile u8 *) hw) + 0x10));
        product = value * angle;
        ASM_USE2_NV(value, product);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        value = product >> 13;
        *((volatile u8 *) (((volatile u8 *) vertex) + 29)) = (*((volatile u8 *) (((volatile u8 *) vertex) + 5))) + value;
      }
      angle = func_800644B8(phase / parameters->count);
      {
        s32 value;
        register s32 product ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        value = *((volatile s32 *) (((volatile u8 *) hw) + 0x14));
        product = value * angle;
        ASM_USE2_NV(value, product);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        value = product >> 13;
        *((volatile u8 *) (((volatile u8 *) vertex) + 30)) = (*((volatile u8 *) (((volatile u8 *) vertex) + 6))) + value;
      }
      *((volatile u16 *) (((volatile u8 *) vertex) + 7)) = parameters->texture;
      flags_value = parameters->flags;
      ASM_KEEP(vertex);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
      *((u16 *) (((u8 *) vertex) + 19)) = flags_value;
      if (flag != 0)
      {
        *((u16 *) (((u8 *) vertex) + 19)) = (flags_value & 0xFF9F) | ((flag - 1) << 5);
      }
      *((volatile s32 *) (((volatile u8 *) (vertex - 3)) + 0)) = parameters->value0;
      *((volatile s32 *) (((volatile u8 *) vertex) + 9)) = parameters->value0;
      new_var = parameters->value1;
      *((volatile s32 *) (((volatile u8 *) vertex) + 21)) = new_var;
      geometry_arg = cursor;
      final_value = parameters->value1;
      *((s32 *) (((u8 *) vertex) + 33)) = final_value;
      func_8006671C(geometry_arg);
      setup_arg = arg2;
      if (flag != 0)
      {
        *((volatile u8 *) (((volatile u8 *) vertex) + 0)) |= 2;
      }
      func_8006658C(setup_arg, cursor);
      vertex += 52;
      cursor += 52;
    }
    while (index < parameters->count);
  }
  {
    register u8 *end_page ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    end_page = D_80083160;
    ASM_KEEP(end_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    (*((DungeonState **) end_page))->cursor = cursor;
  }
}
