#include "common.h"
#include "shared/game_work.h"


typedef struct State {
    s32 unk0;
    s32 unk4;
    s32 flags;
} State;

void townUpdateActorGroundAndInput(s32 *, s32, s32);
void townInitializeSceneActionRecord();

/* Calls townInitializeSceneActionRecord if townUpdateActorGroundAndInput leaves the value unchanged and flag 0x20 is clear. */
void townUpdateInputAndFallbackAction(s32 *value, s32 input_a, s32 input_b) {
    GameWork *state;
    s32 old_value;

    state = &gameWork;
    old_value = *value;
    townUpdateActorGroundAndInput(value, input_a, input_b);
    if ((old_value == *value) && !(state->buttons & 0x20)) {
        townInitializeSceneActionRecord(value, input_a, input_b);
    }
}
