#include "common.h"

typedef s32 (*TownCallback)(s8 *);

extern void *D_80016000;
extern s32 D_80017788;

/* Pass the byte pair 0x12, 0x17 to the town callback and store its result. */
void func_806321E4(void) {
    s8 callback_args[2];

    callback_args[1] = 0x17;
    callback_args[0] = 0x12;
    D_80017788 = (*(TownCallback *)((u8 *)*(void **)((u8 *)D_80016000 + 0x20) + 0x50))(callback_args);
}
