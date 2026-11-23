#include "script_symbols.h"
#include "town/player/state.h"
#include "town/scene.h"

s32 apply_entry_and_write_flag_range(TownObjectSet *entry, s32 entry_index) {
    s32 result = apply_selected_entry_values(entry, entry_index);

    if (result != 0) {
        write_script_flag_range(Ftt_pad61, 3, 2);
    }
    return result;
}
