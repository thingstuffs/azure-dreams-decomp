#include "modules/dungeon_ovl_1831cd8.h"

void func_80027D08(ovl_1831cd8_81812D08_ProgressState *state) {
    func_80027B44(state->entries, state->current, state->maximum);
    func_80027AD0(state, state->current, state->maximum);
    func_80027B6C(state->entries, state->current, state->maximum);
    func_80027BBC(state->entries, state->resource_names);
    func_8004CB2C(state->cursor);
}
