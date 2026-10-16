#include "modules/ovmovie_game.h"

/* Reset movie state and apply the requested playback settings. */
void func_80176B60(void *playback_state, void (*playback_option)(void)) {
    func_801776D8(0);
    *(s32 *)((u8 *)D_80189390 + 0x34) = 0;
    func_8017797C(playback_option);
    func_80060B04((u8 *)D_80189390 + 0x40, 0x20);
    func_800636AC(D_801781E0 & 1, 1, -1, 0, 0);
    func_80177154(playback_state);
}
