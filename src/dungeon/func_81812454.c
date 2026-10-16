#include "modules/dungeon_ovl_1831cd8.h"

void dungeonDispatchMenuStateUpdate(s32 *state, s32 mode, s32 value, s32 extra_value)
{
    if (mode == 0) {
        dungeonRefreshMenuRecordResource(state, value);
        return;
    }
    if (*state != 0x13) {
        dungeonRebuildMenuResource(state, value);
        return;
    }
    dungeonRefreshMenuDerivedValue(state, value, extra_value);
}
