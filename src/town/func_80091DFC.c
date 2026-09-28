#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
/* Apply the entry adjustment, increment its slot count, and store its slot value. */
void func_8008F55C(s32 state_base, void *value_record, void *entry)
{
  int adjusted_value;
  void *slot_base;
  if ((*((u8 *) (((s8 *) entry) + 0x28))) == 0)
  {
    adjusted_value = (*((s32 *) (((s8 *) value_record) + 0))) - (*((s32 *) (((s8 *) entry) + 0x10)));
    *((s32 *) (((s8 *) value_record) + 0xC)) = 0;
    *((s32 *) (((s8 *) value_record) + 0)) = (s32) adjusted_value;
  }
  slot_base = state_base + (*((s32 *) (((s8 *) entry) + 0x2C)));
  *((u8 *) (((s8 *) slot_base) + 0x3A)) = (u8) ((*((u8 *) (((s8 *) slot_base) + 0x3A))) + 1);
  *((s32 *) (((s8 *) (((*((s32 *) (((s8 *) entry) + 0x2C))) * 4) + state_base)) + 0x1C)) = (s32) (*((s32 *) (((s8 *) entry) + 4)));
}
