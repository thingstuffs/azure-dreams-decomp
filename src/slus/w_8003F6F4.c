#include "common.h"

typedef struct S_80083120
{
  s16 field_0;
  s16 field_2;
  s16 field_4;
  s16 field_6;
} S_80083120;
extern S_80083120 D_80083120[8];
extern s16 func_80053428(S_80083120 *a0);
extern s16 func_80053604(S_80083120 *a0);
/* Processes type 5 and 6 entries in reverse order, clearing their type when handled. */
void func_8003F6F4(void)
{
  s32 entry_index;
  u32 last_index;
  S_80083120 *entries;
  S_80083120 *entry;
  s16 signed_type;
  s32 type;

  entry_index = 7;
  last_index = 7;
  entries = D_80083120;
  ASM_KEEP_NV(entries);
  entry = &entries[last_index];
do {
  signed_type = entry->field_0;
  type = (signed_type < 0) ? -signed_type : signed_type;
  if (type == 5)
  {
    goto case5;
  }
  if (type == 6)
  {
    goto case6;
  }
  entry--;
  goto next;
case5:
  if (func_80053428(entry) != 0)
  {
    entry->field_0 = 0;
  }
  goto handled;
case6:
  if (func_80053604(entry) != 0)
  {
    entry->field_0 = 0;
  }
handled:
  entry--;
next:
  ASM_USE(entry_index);
  entry_index--;
  } while (entry_index >= 0);
}
