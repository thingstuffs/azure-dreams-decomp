#include "common.h"

extern s32 dungeonFadeActorToRemoval(s32 value_a, s32 value_b, void *ptr, s32 value_c);
extern void func_800A56C0(void);

void dungeonHandleActorActionResult(s32 value_a, s32 value_b, void *ptr, s32 value_c) {
    if (dungeonFadeActorToRemoval(value_a, value_b, ptr, value_c) != 0) {
        func_800A56C0();
        return;
    }

    *(s16 *)((u8 *)ptr + 0x12) = 0;
}
