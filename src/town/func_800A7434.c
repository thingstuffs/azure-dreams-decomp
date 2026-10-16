#include "common.h"


typedef struct {
    s32 *unk00;
    s32 *unk04;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    void (*unk28)(void);
} UnkStruct_800A7434;


extern void townRestartOrAdvanceTargetInterpolation(UnkStruct_800A7434 *);
/* Reset state when the value source changes; otherwise copy its three values. */
void townResetOrCopyStateValues(UnkStruct_800A7434 *state) {
    s32 *values;

    values = state->unk00;
    if (values != state->unk04) {
        state->unk20 = 9;
        state->unk28 = townRestartOrAdvanceTargetInterpolation;
        state->unk14 = 0;
        state->unk18 = 0;
        state->unk1C = 0;
        state->unk04 = values;
        townRestartOrAdvanceTargetInterpolation(state);
        return;
    }
    state->unk08 = values[0];
    state->unk0C = state->unk00[1];
    state->unk10 = state->unk00[2];
}
