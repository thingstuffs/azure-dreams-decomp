#include "engine/util/state_defaults.h"

#include "common.h"
s32 D_80080B58 = 0xFD80;
s32 D_80080B5C = 0x0;
s32 D_80080B60 = 0x0;
s32 D_80080B64 = 0x400;
#include "engine/util/state_defaults.h"

void func_8004D614(void)
{
    u8 *state = (u8 *)(&g_game_work.view);

    bzero(state + 0x9C, 8);
    *(s32 *)(state + 0x94) = D_80080B60;
    *(s32 *)(state + 0x98) = D_80080B64;
    *(s32 *)(state + 0xAC) = D_80080B58;
    *(s32 *)(state + 0xB0) = D_80080B5C;
    bzero(state + 0xA4, 8);
    *(s32 *)(state + 0x13C) = 0;
    *(s32 *)(state + 0x180) = 0;
    *(s32 *)(state + 0xB4) = 0;
    *(s32 *)(state + 0xF8) = 0;
    func_8004D0C8(((u8 *)(&D_80083780)));
}
