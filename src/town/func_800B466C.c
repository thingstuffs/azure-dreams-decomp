#include "common.h"

extern void func_80044AAC();
extern u8 D_800D162C[];
extern u8 D_800D1630[];

void func_800B1DCC(void **arg0)
{
  s32 values[2];
  s32 i;
  s32 stack_offset;
  s32 delta;
  u8 table_value;
  u8 old_value;
  s32 signed_coord;
  s16 result_coord;
  s16 old_coord;
  u8 *table_a;
  u8 *table_b;
  void **entry;
  void *container;
  void *object;
  void *copy;

  i = 0;
  table_a = D_800D162C;
  table_b = D_800D1630;
  stack_offset = i;
  entry = arg0;
  do {
    container = *((void **) (((u8 *) (*entry)) + 0xC));
    table_value = (table_a + ((*((s32 *) (((u8 *) arg0) + 0xC))) * 2))[i];
    object = *((void **) (((u8 *) container) + 4));
    {
      s32 loaded_coord;
      loaded_coord = *((s16 *) (((u8 *) object) + 0xC));
      signed_coord = loaded_coord;
      delta = (table_value * 0x28) + 0x200;
      delta -= loaded_coord;
    }
    if (table_value == 0) {
      goto no_round;
    }
    delta++;
  no_round:
    result_coord = (s16) (signed_coord + (delta >> 1));
    *((s16 *) (((u8 *) object) + 0xC)) = result_coord;
    old_coord = 1;
    *((s32 *) (((u8 *) values) + stack_offset)) = *((s16 *) (((u8 *) (*((void **) (((u8 *) container) + 4)))) + 0xC));
    object = *((void **) (((u8 *) container) + 4));
    table_value = (table_a + ((*((s32 *) (((u8 *) arg0) + 0xC))) * 2))[i];
    old_value = *((u8 *) (((u8 *) object) + 0));
    delta = table_b[table_value * 4] - old_value;
    if (table_value == 0) {
      delta++;
    }
    *((u8 *) (((u8 *) object) + 0)) = old_value + (delta >> 1);
    stack_offset += 4;
    *((u8 *) (((u8 *) (*((void **) (((u8 *) container) + 4)))) + old_coord)) = *((u8 *) (((u8 *) (*((void **) (((u8 *) container) + 4)))) + 0));
    copy = *((void **) (((u8 *) container) + 4));
    *((u8 *) (((u8 *) copy) + 2)) = *((u8 *) (((u8 *) copy) + 0));
    entry = (void **) (((u8 *) entry) + 4);
    i++;
  } while (i < 2);
  if (values[0] > values[old_coord]) {
    func_80044AAC(arg0[old_coord], arg0[0]);
  } else {
    func_80044AAC(arg0[0], arg0[old_coord]);
  }
}
