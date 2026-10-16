#include "common.h"
#include "shared/dungeon_status.h"

extern void func_800A9A0C(void *);
extern void dungeonBeginActorDisplayAction(void *actor, void *unused, void *display, u8 *facing_variants);
extern s32 dungeonBeginReadyActorDirectionalAction(void *, s32, void *, s32);

/* Processes active status, counts completed transitions, and dispatches follow-up work. */
void func_800D3140(s32 dispatch_arg0, s32 dispatch_arg1, s32 dispatch_arg2, u8 *state) {
    s16 previous_status;

    if ((s8)state[0x6D] > 0) {
        previous_status = (s8)(state[0x6D] + 0);
        *(s32 *)(state + 0x60) = 0;
        func_800A9A0C(state);
        if (previous_status != 0 && *(s8 *)(state + 0x6D) == 0) {
            state[0x28]--;
        }
        if (state[0x28] == 0) {
            dungeonStatus.unk_10 = state - 0x20;
            dungeonBeginActorDisplayAction(dispatch_arg0, dispatch_arg1, dispatch_arg2, 0);
            return;
        }
    }
    if (*(s16 *)(state + 0x64) != 0) {
        dungeonBeginReadyActorDirectionalAction(dispatch_arg0, dispatch_arg1, dispatch_arg2, 0);
    }
}
