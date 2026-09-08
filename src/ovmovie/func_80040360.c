#include "common.h"

extern void func_801776D8(s32);
extern void func_8017797C(s32);
extern void func_80060B04(void *, s32);
extern void func_800636AC(s32, s32, s32, s32, s32);
extern void func_80177154(s32);

extern s32 D_801781E0;
extern s8 *D_80189390;

/* Reset movie state and apply the requested playback settings. */
void func_80040360(s32 playback_mode, s32 playback_option) {
    func_801776D8(0);
    *(s32 *)(D_80189390 + 0x34) = 0;
    func_8017797C(playback_option);
    func_80060B04(D_80189390 + 0x40, 0x20);
    func_800636AC(D_801781E0 & 1, 1, -1, 0, 0);
    func_80177154(playback_mode);
}
