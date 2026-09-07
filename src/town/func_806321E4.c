#include "common.h"

typedef s32 (*TownCallback)(s8 *);

extern void *D_80016000;
extern s32 D_80017788;

void func_806321E4(void) {
    s8 arg[2];

    arg[1] = 0x17;
    arg[0] = 0x12;
    D_80017788 = (*(TownCallback *)((u8 *)*(void **)((u8 *)D_80016000 + 0x20) + 0x50))(arg);
}
