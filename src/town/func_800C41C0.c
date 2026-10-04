#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s32 M2C_UNK;
extern void func_8003AF58();
extern M2C_UNK D_800717D0;
extern s8 D_80080A88;
extern M2C_UNK D_800D429C;
/* Pass the town data pair to func_8003AF58 and set the shared flag. */
void func_800C1920(void)
{
    long enabled;
    func_8003AF58(&D_800717D0, &D_800D429C);
    enabled = 1;
    D_80080A88 = enabled;
    D_80080A88 = 1;
}
