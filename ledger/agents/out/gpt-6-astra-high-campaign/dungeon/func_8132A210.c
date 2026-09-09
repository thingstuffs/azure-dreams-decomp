#include "common.h"

typedef s32 M2C_UNK;
typedef struct 
{
  u8 b[32];
} DungeonTable;
extern u8 D_80171704[];
void *func_8003FD64();
M2C_UNK func_8004491C();
s32 func_80069EF8();
extern DungeonTable D_8016A894;
extern M2C_UNK D_801718E4;
/* Creates an effect with direction-based position offsets and randomized velocity. */
void func_80171A10(void *source, s32 angle, s32 initial_value, s32 unused, volatile s32 spread_mode)
{
  register void *source_obj ASM_REG("$17") = source;
  register u32 direction ASM_REG("$18") = angle;
  register s32 data_value ASM_REG("$22") = initial_value;
  s32 spread;
  void *effect_obj;
  DungeonTable direction_table = D_8016A894;
  register u8 *frame_ptr ASM_REG("$29");
  register u8 *table_base ASM_REG("$19");
  void *y_position;
  void *x_position;
  void *motion;
  void *direction_entry;
  void *y_motion;
  void *effect_data;
  void *effect;
  void *handler;
  register s32 motion_value ASM_REG("$2");
  u32 saved_angle;
  s32 y_velocity;
  void *velocity_base;
  ASM_KEEP(data_value);
  {
    u32 effect_type = 0x211;
    ASM_KEEP(effect_type);
    spread = spread_mode;
    ASM_KEEP(spread);
    saved_angle = direction;
    effect = func_8003FD64(effect_type, source_obj);
  }
  ASM_UNDEF(frame_ptr);
  if (effect != 0)
  {
    register u32 entry_addr ASM_REG("$4");
    table_base = frame_ptr + 0x10;
    ASM_KEEP(table_base);
    handler = &D_801718E4;
    ASM_KEEP_DEP_NV(direction, handler);
    entry_addr = direction >> 7;
    *((M2C_UNK **) (((s8 *) effect) + 0x10)) = handler;
    *((u16 *) (((s8 *) (*((void **) (((s8 *) effect) + 8)))) + 2)) = (u16) (*((u16 *) (((s8 *) (*((void **) (((s8 *) source_obj) + 8)))) + 2)));
    entry_addr &= 0x1C;
    *((u16 *) (((s8 *) (*((void **) (((s8 *) effect) + 8)))) + 6)) = (u16) (*((u16 *) (((s8 *) (*((void **) (((s8 *) source_obj) + 8)))) + 6)));
    entry_addr = (u32) table_base + entry_addr;
    ASM_KEEP(direction);
    *((s16 *) (((s8 *) (*((void **) (((s8 *) effect) + 8)))) + 0xA)) = (s16) ((*((u16 *) (((s8 *) (*((void **) (((s8 *) source_obj) + 8)))) + 0xA))) - 0x14);
    ASM_KEEP(source_obj);
    x_position = *((void **) (((s8 *) effect) + 8));
    *((u16 *) (((s8 *) x_position) + 2)) = (u16) ((*((u16 *) (((s8 *) x_position) + 2))) + ((*((s16 *) (((s8 *) ((void *) entry_addr)) + 0))) * 0x10));
    y_position = *((void **) (((s8 *) effect) + 8));
    *((u16 *) (((s8 *) y_position) + 6)) = (u16) ((*((u16 *) (((s8 *) y_position) + 6))) + (((s32) ((*((u16 *) (((s8 *) ((void *) entry_addr)) + 2))) << 0x10)) >> 0xC));
    *((s16 *) (((s8 *) (*((void **) (((s8 *) effect) + 0xC)))) + 6)) = 6;
    effect_data = effect + 0x20;
    if ((spread << 0x10) == 0)
    {
      *((s32 *) (((s8 *) (*((void **) (((s8 *) effect) + 8)))) + 0xC)) = (s32) (((func_80069EF8(y_position, x_position) & 0x7FFF) - 0x4000) << 7);
      y_velocity = (s32) (((func_80069EF8() & 0x7FFF) - 0x4000) << 7);
      velocity_base = *((void **) (((s8 *) effect) + 8));
      *((s32 *) (((s8 *) velocity_base) + 0x10)) = y_velocity;
    }
    else
    {
      *((s32 *) (((s8 *) (*((void **) (((s8 *) effect) + 8)))) + 0xC)) = (s32) (((func_80069EF8(y_position, x_position) & 0x7FFF) - 0x4000) << 6);
      y_velocity = (s32) (((func_80069EF8() & 0x7FFF) - 0x4000) << 6);
      velocity_base = *((void **) (((s8 *) effect) + 8));
      *((s32 *) (((s8 *) velocity_base) + 0x10)) = y_velocity;
    }
    motion_value = (s32) (((func_80069EF8() & 0x7FFF) - 0x4000) << 5);
    {
      register u8 *tail_frame ASM_REG("$29");
      ASM_UNDEF(tail_frame);
      direction_entry = tail_frame + 0x10;
    }
    motion = (effect_obj = *((void **) (((s8 *) effect) + 8)));
    *((s32 *) (((s8 *) motion) + 0x14)) = motion_value;
    effect_obj = effect;
    motion_value = saved_angle >> 7;
    motion_value &= 0x1C;
    direction_entry += motion_value;
    motion = *((void **) (((s8 *) effect_obj) + 8));
    *((s32 *) (((s8 *) motion) + 0xC)) = (s32) ((*((s32 *) (((s8 *) motion) + 0xC))) + ((*((s16 *) (((s8 *) direction_entry) + 0))) * 0x160000));
    y_motion = *((void **) (((s8 *) effect_obj) + 8));
    *((s32 *) (((s8 *) y_motion) + 0x10)) = (s32) ((*((s32 *) (((s8 *) y_motion) + 0x10))) + (((s16) (*((volatile u16 *) (((s8 *) direction_entry) + 2)))) * 0x160000));
    *((u16 *) (((s8 *) effect_data) + 0x14)) = saved_angle;
    *((s16 *) (((s8 *) effect_data) + 0x32)) = 7;
    *((s16 *) (((s8 *) effect_data) + 0x34)) = 7;
    func_8004491C(effect_obj, D_80171704, y_motion);
    *((s32 *) effect_data) = data_value;
    *((s32 *) (((s8 *) effect_data) + 8)) = data_value;
  }
}
