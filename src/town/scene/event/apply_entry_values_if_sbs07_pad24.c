#include "script_symbols.h"
#include "town/player/script_flags.h"
#include "town/scene/hooks.h"
#include "town/scene/record_actions.h"
#include "town/scene.h"

s32 apply_entry_values_if_sbs07_pad24(TownObjectSet *row, s32 entry_index) {
    s32 result;

    set_global_entry_pair(row, entry_index);
    if (get_script_flag_mask(F_sbs07_pad24) != 0) {
        result = apply_selected_entry_values(row, entry_index);
    } else {
        result = 0;
    }
    return result;
}
