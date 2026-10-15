#include "modules/dungeon_ovl_1831370.h"

void func_80026508(s32 object_addr) {
    s32 updated_value;
    ovl_1831370_81811508_S_80026508_0 *state;

    state = object_addr + 0x20;
    updated_value = func_80026388(-1, state->unk_08, state->unk_10);
    state->unk_08 = updated_value;
    func_80026370(state->unk_70, updated_value);
}
