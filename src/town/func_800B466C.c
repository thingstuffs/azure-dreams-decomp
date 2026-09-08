#include "common.h"

extern void func_80044AAC();
extern u8 D_800D162C[];
extern u8 D_800D1630[];

/* Ease two objects toward preset coordinates and shades, then pass them in coordinate order. */
void func_800B1DCC(void **pair_state)
{
  s32 coords[2];
  s32 item_index;
  s32 coord_offset;
  s32 delta;
  u8 preset_index;
  u8 old_shade;
  s32 current_coord;
  s16 next_coord;
  s16 second_index;
  u8 *preset_table;
  u8 *shade_table;
  void **item_entry;
  void *visual_holder;
  void *visual_data;
  void *shade_data;

  item_index = 0;
  preset_table = D_800D162C;
  shade_table = D_800D1630;
  coord_offset = item_index;
  item_entry = pair_state;
  do {
    visual_holder = *((void **) (((u8 *) (*item_entry)) + 0xC));
    preset_index = (preset_table + ((*((s32 *) (((u8 *) pair_state) + 0xC))) * 2))[item_index];
    visual_data = *((void **) (((u8 *) visual_holder) + 4));
    {
      s32 loaded_coord;
      loaded_coord = *((s16 *) (((u8 *) visual_data) + 0xC));
      current_coord = loaded_coord;
      delta = (preset_index * 0x28) + 0x200;
      delta -= loaded_coord;
    }
    if (preset_index == 0) {
      goto no_round;
    }
    delta++;
  no_round:
    next_coord = (s16) (current_coord + (delta >> 1));
    *((s16 *) (((u8 *) visual_data) + 0xC)) = next_coord;
    second_index = 1;
    *((s32 *) (((u8 *) coords) + coord_offset)) = *((s16 *) (((u8 *) (*((void **) (((u8 *) visual_holder) + 4)))) + 0xC));
    visual_data = *((void **) (((u8 *) visual_holder) + 4));
    preset_index = (preset_table + ((*((s32 *) (((u8 *) pair_state) + 0xC))) * 2))[item_index];
    old_shade = *((u8 *) (((u8 *) visual_data) + 0));
    delta = shade_table[preset_index * 4] - old_shade;
    if (preset_index == 0) {
      delta++;
    }
    *((u8 *) (((u8 *) visual_data) + 0)) = old_shade + (delta >> 1);
    coord_offset += 4;
    *((u8 *) (((u8 *) (*((void **) (((u8 *) visual_holder) + 4)))) + second_index)) = *((u8 *) (((u8 *) (*((void **) (((u8 *) visual_holder) + 4)))) + 0));
    shade_data = *((void **) (((u8 *) visual_holder) + 4));
    *((u8 *) (((u8 *) shade_data) + 2)) = *((u8 *) (((u8 *) shade_data) + 0));
    item_entry = (void **) (((u8 *) item_entry) + 4);
    item_index++;
  } while (item_index < 2);
  if (coords[0] > coords[second_index]) {
    func_80044AAC(pair_state[second_index], pair_state[0]);
  } else {
    func_80044AAC(pair_state[0], pair_state[second_index]);
  }
}
