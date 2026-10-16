#include "common.h"

extern void dungeonAdvanceStatusTimers(s32);
extern s32 dungeonUpdateActorMovementToTile(void *, s32, s32, s32);
extern s32 dungeonCheckActorFloorTrap(s32, s32);
extern s32 D_8016B778;

/* Initializes the state fields when the availability and value checks pass. */
void dungeonAdvanceActorMovementAndTrapCheck(void *state, s32 unused, s32 checkInput, s32 setupInput) {
    if (dungeonUpdateActorMovementToTile(state, unused, checkInput, setupInput) != 0) {
        dungeonAdvanceStatusTimers(setupInput);
        if ((dungeonCheckActorFloorTrap(checkInput, setupInput) << 16) > 0) {
            *(s32 **)((u8 *)state + 0x8c) = &D_8016B778;
            *(s32 *)((u8 *)state + 0x90) = 0;
        }
    }
}
