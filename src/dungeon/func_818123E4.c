#include "modules/dungeon_ovl_1831cd8.h"

void *refresh_menu_derived_value(ovl_1831cd8_818123E4_S_800273E4_0 *state, s32 replacementInput, s32 calculationInput) {
    s32 adjustedValue;

    func_8004B1A4(state->unk_08);
    adjustedValue = count_menu_entry_pair_matches(state->unk_00, calculationInput) + 5;
    state->unk_04 = adjustedValue;
    state->unk_08 = build_menu_text_page(state->unk_00, replacementInput, adjustedValue, calculationInput);
    return state;
}
