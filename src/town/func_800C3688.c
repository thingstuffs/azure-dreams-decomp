#include "shared/game_work.h"
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern u32 D_8006ADBC;
extern s32 D_800D3824[];
extern void func_800BC45C(s32 arg0, s16 arg1, void *state);
/* Calls func_800BC45C with the first table entry matching the state's ID. */
void func_800C0DE8(void)
{
  s32 *table_entry;
  s8 *state;
  if (*((volatile s32 *) D_800D3824) != (-1))
  {
    do
    {
      state = (s8 *) (&D_8006ADBC);
    } while (0);
    table_entry = D_800D3824;
    check_entry:
    if (*((s16 *) (state + 0x1A)) == (*table_entry))
    {
      func_800BC45C(*((s32 *) (((s8 *) table_entry) + 4)), *((s16 *) (((s8 *) table_entry) + 8)), state);
      return;
    }
    table_entry += 3;
    if (*table_entry != (-1))
    {
      goto check_entry;
    }
  }
}
