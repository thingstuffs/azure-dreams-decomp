#include "modules/dungeon_ovl_1831cd8.h"

void func_80027D08(ovl_1831cd8_81812D08_ProgressState *state) {
    dungeonStoreScaledMenuRatio(state->entries, state->current, state->maximum);
    dungeonDrawMenuProgressBar(state, state->current, state->maximum);
    dungeonSetMenuObjectScaleFields(state->entries, state->current, state->maximum);
    dungeonRefreshMenuEntryResources(state->entries, state->resource_names);
    advanceTimedTaggedStream(state->cursor);
}
