#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern void func_8004491C();
extern s32 func_800644B8();
extern s32 func_80064584();
extern u8 D_800345B8[];
extern u8 D_800A1FEC[];
extern s16 D_800D0A10[];
extern s32 D_800D0A1C[];
extern u16 D_800D0A34[];
extern u8 D_800F148C[];
/* Initializes object and render state from indexed parameter tables. */
void func_800A1F00(void *object, s32 unused, void *render_state)
{
  s16 *angle_entry;
  s32 *property_entry;
  s32 *property_table;
  u16 *state_entry;
  u16 *state_table;
  u8 *angle_table;
  u16 initial_state;
  s32 variant_offset;
  s32 halfword_offset;
  variant_offset = *((s16 *) (((s8 *) object) + 0x20));
  *((s32 *) (((s8 *) render_state) + 0)) = 0;
  *((s8 *) (((s8 *) render_state) + 4)) = 0;
  *((s8 *) (((s8 *) render_state) + 5)) = 0;
  *((u8 **) (((s8 *) render_state) + 8)) = D_800F148C;
  func_8004491C(object - 0x20, D_800345B8);
  angle_table = (u8 *) D_800D0A10;
  *((s16 *) (((s8 *) render_state) + 0x10)) = 0x20;
  *((u16 *) (((s8 *) render_state) + 0x14)) |= 0x1C;
  halfword_offset = variant_offset * 2;
  angle_entry = (s16 *) (angle_table + halfword_offset);
  *((s32 *) (((s8 *) object) + 0x24)) = func_800644B8(*angle_entry);
  variant_offset *= 4;
  *((s32 *) (((s8 *) object) + 0x28)) = 0;
  *((s32 *) (((s8 *) object) + 0x2C)) = func_80064584(*angle_entry);
  property_table = D_800D0A1C;
  property_entry = (s32 *) (((u8 *) property_table) + variant_offset);
  *((s32 *) (((s8 *) object) + 0x3C)) = *property_entry;
  state_table = D_800D0A34;
  state_entry = (u16 *) (((u8 *) state_table) + halfword_offset);
  initial_state = *state_entry;
  *((u8 **) (((s8 *) object) + 0)) = D_800A1FEC;
  *((u16 *) (((s8 *) object) + 0x22)) = initial_state;
}
