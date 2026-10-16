#include "common.h"
#include "shared/dungeon_status.h"

extern void func_800A9A0C(void *);
extern void dungeonBeginPushedActorMove(void);
extern void dungeonBeginReadyActorDirectionalAction(s32, s32, s32, s32);
extern void dungeonBeginActorDisplayAction(void *actor, void *unused, void *display, u8 *facing_variants);

/* Updates the actor state, consumes completed counts, and dispatches its action. */
void dungeonDispatchActorAction(s32 actor, s32 action_arg, s32 action_data, u8 *state) {
    s16 old_count;

    if (!(dungeonStatus.flags & 0x2000)) {
        if (*(s32 *)(state + 0x1C) & 0x100) {
            dungeonBeginPushedActorMove();
            return;
        }
        if (*(u8 *)(actor + 0x9A) != 0xE) {
            *(u8 *)(actor + 0x9A) = 0xE;
        }
    }
    if (*(s8 *)(state + 0x6D) > 0) {
        old_count = (s8)(state[0x6D] + 0);
        *(s32 *)(state + 0x60) = 0;
        func_800A9A0C(state);
        if ((old_count != 0) && (*(s8 *)(state + 0x6D) == 0)) {
            *(u8 *)(state + 0x28) -= 1;
        }
        if (*(u8 *)(state + 0x28) == 0) {
            dungeonStatus.unk_10 = state - 0x20;
            dungeonBeginActorDisplayAction(actor, action_arg, action_data, 0);
            return;
        }
    }
    if (*(s16 *)(state + 0x64) != 0) {
        dungeonBeginReadyActorDirectionalAction(actor, action_arg, action_data, 0);
    }
}
