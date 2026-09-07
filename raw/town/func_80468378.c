#include "common.h"

typedef void (*TownCallback)(s32, s32, s32);

extern void *D_80016000[];

void func_80468378(void)
{
    (*(TownCallback *)((s8 *)*(void **)((u8 *)D_80016000[0] + 0x20) + 0x310))(
        0x2B, 0x200, 0x9000);
    (*(TownCallback *)((u8 *)*(void **)((u8 *)D_80016000[0] + 0x20) + 0x310))(
        0x2B, 0x200, 0);
}
