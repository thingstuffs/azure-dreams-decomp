#include "modules/dungeon_ovl_1831cd8.h"

void dispatch_menu_state_update(s32 *state, s32 mode, s32 value, s32 extra_value)
{
    if (mode == 0) {
        refresh_menu_record_resource(state, value);
        return;
    }
    if (*state != 0x13) {
        rebuild_menu_resource(state, value);
        return;
    }
    refresh_menu_derived_value(state, value, extra_value);
}
