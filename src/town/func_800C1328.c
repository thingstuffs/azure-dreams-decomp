#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern void func_8006733C(void *arg0, void *arg1);
extern void func_80067014(s32 arg0);
extern void func_800673A0(void *arg0, s32 arg1, s32 arg2);
extern u8 D_800D231C[];
extern u8 D_800D2324[];
extern u8 D_80113138[];
/* pool_clut_store: Store the pool CLUT and update its transfer region. */
void pool_clut_store(void)
{
    func_8006733C(D_800D231C, D_80113138);
    func_80067014(0);
    func_800673A0(D_800D2324, 0x60, 0x1FA);
}
