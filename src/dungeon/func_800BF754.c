#include "common.h"

extern void *func_8003FD64();
extern s32 D_80083498[4];
extern s32 D_800C4E00[4];

void *func_800C4EB4(s32 arg0, s32 arg1, s32 arg2, s16 arg3, s32 arg4) {
    void *temp_v0;
    void *temp_v0_2;
    s16 saved_arg3 = arg3;
    register s32 saved_arg4 ASM_REG("$17") = arg4;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

    temp_v0 = func_8003FD64(0, &D_80083498[0]);
    if (temp_v0 != 0) {
        *(s32 **)((s8 *)temp_v0 + 0x10) = &D_800C4E00[0];
        temp_v0_2 = (s8 *)temp_v0 + 0x20;
        *(s16 *)((s8 *)temp_v0_2 + 8) = 0x40;
        *(s16 *)((s8 *)temp_v0_2 + 0xA) = saved_arg3;
        *(s16 *)((s8 *)temp_v0_2 + 0xC) = (s16)saved_arg4;
    }
    return temp_v0;
}
