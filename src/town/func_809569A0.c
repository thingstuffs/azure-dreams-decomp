#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s8 M2C_UNK8;
/* Fill negative slots when eligibility is at least four, then clear a duplicate second slot. */
void func_800239A0(void *record, s16 *eligibility, s16 new_value)
{
  s32 slot_index;
  void *slot_cursor;
  slot_index = 0;
  slot_cursor = record;
  do
  {
    if (((*((s16 *) (((s8 *) slot_cursor) + 0x44))) < 0) && ((*eligibility) >= 4))
    {
      *((s16 *) (((s8 *) slot_cursor) + 0x44)) = new_value;
    }
    if (record)
    {
      slot_index += 1;
      slot_cursor += 2;
    }
    else
    {
      slot_index += 1;
      slot_cursor += 2;
    }
  }
  while (slot_index < 2);
  if ((*((s16 *) (((s8 *) record) + 0x44))) == (*((s16 *) (((s8 *) record) + 0x46))))
  {
    *((s16 *) (((s8 *) record) + 0x46)) = -1;
  }
}
