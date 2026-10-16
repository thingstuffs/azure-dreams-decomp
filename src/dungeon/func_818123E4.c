#include "modules/dungeon_ovl_1831cd8.h"

void *dungeonRefreshMenuDerivedValue(ovl_1831cd8_818123E4_S_800273E4_0 *state, M2C_UNK replacementInput, M2C_UNK calculationInput) {
    s32 adjustedValue;

    func_8004B1A4(state->unk_08);
    adjustedValue = dungeonCountMenuEntryPairMatches(state->unk_00, calculationInput) + 5;
    state->unk_04 = adjustedValue;
    state->unk_08 = dungeonBuildMenuTextPage(state->unk_00, replacementInput, adjustedValue, calculationInput);
    return state;
}
