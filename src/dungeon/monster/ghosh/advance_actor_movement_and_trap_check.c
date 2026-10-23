#include "common.h"
#include "dungeon/actor.h"

extern void advance_status_timers(s32);
extern s32 update_actor_movement_to_tile(void *, s32, s32, s32);

extern s32 D_8016B778;

/* Initializes the state fields when the availability and value checks pass. */
void advance_actor_movement_and_trap_check(void *state, s32 unused, s32 checkInput, s32 setupInput) {
    if (update_actor_movement_to_tile(state, unused, checkInput, setupInput) != 0) {
        advance_status_timers(setupInput);
        if ((check_actor_floor_trap(checkInput, setupInput) << 16) > 0) {
            *(s32 **)((u8 *)state + 0x8c) = &D_8016B778;
            *(s32 *)((u8 *)state + 0x90) = 0;
        }
    }
}
