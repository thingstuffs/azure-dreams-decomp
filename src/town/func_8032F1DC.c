#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s8 M2C_UNK8;
s32 func_8001ADE0();
extern s16 D_8001B8AA;
/* Check the record flag only when the global blocking flag is clear. */
s32 func_800199DC(void *record)
{
  s32 flag_set;
  void *record_copy;
  int initial_result;
  void *flag_record;
  if (initial_result)
  {
    initial_result = 0;
    flag_set = initial_result;
    record_copy = record;
    flag_record = record_copy;
  }
  else
  {
    initial_result = 0;
    flag_set = initial_result;
    record_copy = record;
    flag_record = record_copy;
  }
  if (func_8001ADE0(D_8001B8AA) == 0)
  {
    flag_set = func_8001ADE0(*(s16 *) (((s8 *) flag_record) + 0x18)) != 0;
  }
  return flag_set;
}
