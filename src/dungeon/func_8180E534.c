#include "common.h"

typedef s32 M2C_UNK;
void *func_8003FC64(s32);
void func_8004491C(void *, void *);
s32 func_800644B8(s32);
s32 func_80064584(s32);
void func_800B835C(void *, void *, s32, s32);
extern u8 D_8002744C[9];
extern u8 D_80028880[9];
extern u8 D_8002888C[9];
extern s16 D_80083228;
extern s32 D_800CEEFC[3];
/* Creates four groups of 32 effect objects with angularly distributed motion. */
void *func_80027534(s16 pos_x, s16 pos_y, s16 pos_z)
{
    register u16 facing_angle ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
  volatile struct
  {
    s32 sp10;
    s32 sp14;
    u16 sp18;
    u16 sp1A;
    u8 pad1C[4];
    u16 sp20;
    u8 pad22[6];
    s32 sp28;
  } sp;
  s32 angle_value;
  s32 sample_angle;
  s32 scale_shift;
  register s32 motion_angle ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
  s32 sample_index;
  s32 group_index;
  register s16 held_y ASM_REG("$5") = pos_y;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  register s16 held_z ASM_REG("$6") = pos_z;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  register s32 setup_origin ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  s32 setup_size;
  register void *setup_asset ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  register void *setup_data ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  s32 base_shift;
  s16 index_step;
  s32 trig_result;
  void *effect_state;
  void *effect;
  sp.sp1A = held_z;
  setup_origin = 0x01800380;
  setup_size = 0x400040;
  setup_asset = D_8002888C;
  sp.sp18 = held_y;
  setup_data = (void *) (&sp.sp10);
  ASM_USE_G_NV(D_80083228);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  sp.sp10 = setup_origin;
  sp.sp14 = setup_size;
  angle_value = (((s32) (D_80083228 + 0x500)) >> 9) & 7;
  group_index = 0;
  ASM_USE2_NV(setup_asset, setup_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  {
    facing_angle = (u8)angle_value << 9;
    *((u16 *) ((void *) (&sp.sp20))) = facing_angle;
  }
  func_800B835C(setup_asset, setup_data, 1, group_index);
  sp.sp28 = angle_value << 9;
  do
  {
      register s32 base_angle ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    sample_index = 0;
    {
      base_angle = sp.sp28;
      index_step = 1;
      base_shift = 5;
      scale_shift = base_shift - group_index;
      motion_angle = base_angle + 0x400;
    }
    spawn_sample:
    effect = func_8003FC64(0x202);

    if (effect != 0)
    {
      {
        setup_asset = (void *)((s32)(effect));
        setup_data = D_800CEEFC;
        ASM_USE2(setup_asset, setup_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        base_angle = (s32)(D_8002744C);
        *((M2C_UNK **) (((s8 *) effect) + 0x10)) = (void *)base_angle;
        func_8004491C((void *)(s32)setup_asset, setup_data);
      }
      {
        void *positions;
        positions = *((void **) (((s8 *) effect) + 8));
        *((s16 *) (((s8 *) positions) + 2)) = pos_x;
        *((s16 *) (((s8 *) positions) + 0xE)) = pos_x;
        facing_angle = sp.sp18;
        *((u16 *) (((s8 *) positions) + 6)) = facing_angle;
        *((u16 *) (((s8 *) positions) + 0x12)) = facing_angle;
        facing_angle = sp.sp1A;
        *((u16 *) (((s8 *) positions) + 0xA)) = facing_angle;
        *((u16 *) (((s8 *) positions) + 0x16)) = facing_angle;
      }
      sample_angle = sample_index << 7;
      effect_state = effect + 0x20;
      base_angle = func_80064584(motion_angle) * func_80064584(sample_angle);
      base_shift = base_angle >> scale_shift;
      *((s32 *) (((s8 *) effect_state) + 0xC)) = base_shift;
      base_angle = func_800644B8(motion_angle) * func_80064584(sample_angle);
      base_shift = base_angle >> scale_shift;
      *((s32 *) (((s8 *) effect_state) + 0x10)) = base_shift;
      trig_result = func_800644B8(sample_angle);
      {
        setup_data = (void *)(0x808080);
        *((s32 *) (((s8 *) effect_state) + 0x14)) = (s32) (trig_result << ((group_index >> index_step) + 7));
        setup_asset = (void *)((s32)(*((void **) (((s8 *) effect) + 0xC))));
        *((s16 *) (((s8 *) (void *)(s32)setup_asset) + 0x1E)) = 0x400;
        *((s16 *) (((s8 *) (void *)(s32)setup_asset) + 0x1C)) = 0x400;
        {
          void *render_asset = D_80028880;
          *((M2C_UNK **) (((s8 *) (void *)(s32)setup_asset) + 8)) = render_asset;
        }
        *((s16 *) (((s8 *) (void *)(s32)setup_asset) + 0x10)) = 0x20;
        *((s32 *) (((s8 *) (void *)(s32)setup_asset) + 0xC)) = (s32)setup_data;
        *((u16 *) (((s8 *) (void *)(s32)setup_asset) + 0x14)) = (u16) ((*((u16 *) (((s8 *) (void *)(s32)setup_asset) + 0x14))) | 0xC);
        *((s16 *) (((s8 *) effect_state) + 0x66)) = 0xC;
        {
          facing_angle = sp.sp20;
          *((u16 *) (((s8 *) effect_state) + 0x74)) = facing_angle;
        }
      }
    }
    sample_index += index_step;
    if (sample_index < 0x20)
    {
      goto spawn_sample;
    }
    group_index += index_step;
  }
  while (group_index < 4);
  return effect;
}
