/* Relink of matched dungeon/func_8132530C; every changed retail word is a paired relocation. */
#define D_8016B778 D_8016A36C
#include "common.h"

extern void dungeonAdvanceStatusTimers(s32);
extern s32 dungeonUpdateActorMovementToTile(void *, s32, s32, s32);
extern s32 dungeonCheckActorFloorTrap(s32, s32);
extern s32 D_8016A36C;

/* Initializes the state fields when the availability and value checks pass. */
void func_8016BD48(void *state, s32 unused, s32 checkInput, s32 setupInput) {
    if (dungeonUpdateActorMovementToTile(state, unused, checkInput, setupInput) != 0) {
        dungeonAdvanceStatusTimers(setupInput);
        if ((dungeonCheckActorFloorTrap(checkInput, setupInput) << 16) > 0) {
            *(s32 **)((u8 *)state + 0x8c) = &D_8016A36C;
            *(s32 *)((u8 *)state + 0x90) = 0;
        }
    }
}
