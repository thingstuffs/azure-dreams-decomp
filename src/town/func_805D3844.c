#include "shared/record_ptrs.h"
#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s8 M2C_UNK8;
/* Writes 0x61 through the pointer at offset 0x1C of D_80016000's first entry. */
void func_80017844(void)
{
  **(s32 **)((s8 *)((unsigned int)D_80016000) + 0x1C) = 0x61;
}
