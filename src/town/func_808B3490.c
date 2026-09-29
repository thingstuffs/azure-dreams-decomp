#include "shared/game_work.h"

extern unsigned char D_000012F4[];
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s8 M2C_UNK8;
/* Stores 9 at offset 0x12F4 in the object referenced by 0xA0700F40. */
int func_808B3490(void)
{
    *(s32 *) ((s8 *) *(void **) 0xA0700F40 + (u32) D_000012F4) = 9;
}
