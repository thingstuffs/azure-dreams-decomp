#include "common.h"

extern void func_80099754(void *arg0);
extern s32 D_800D0608[];
extern u32 D_8009AB74;

/* Approach the target position and finish the motion when the countdown expires. */
void func_8009AAB8(void *state, void *motion)
{
    u16 ticks_left;

    *(u16 *)((u8 *)state + 0x10) += 0x200;
    *(s32 *)((u8 *)motion + 0xC) =
        (D_800D0608[0] - *(s32 *)((u8 *)motion + 0)) / 2;
    *(s32 *)((u8 *)motion + 0x10) =
        (D_800D0608[1] - *(s32 *)((u8 *)motion + 4)) / 2;
    ticks_left = *(u16 *)((u8 *)state + 0xA) - 1;
    *(u16 *)((u8 *)state + 0xA) = ticks_left;
    if ((s16)ticks_left < 0) {
        *(s32 *)((u8 *)motion + 0) = D_800D0608[0];
        *(s32 *)((u8 *)motion + 4) = D_800D0608[1];
        func_80099754(motion);
        *(s32 **)((u8 *)state + 4) = &D_8009AB74;
        *(u16 *)((u8 *)state + 0x10) = 0;
    }
}
