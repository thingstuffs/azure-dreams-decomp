#include "script_symbols.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"
#include "town/scene.h"

s32 apply_conditional_record_value(TownObjectSet *entry, s32 entry_index) {
    if (get_script_flag_mask(F_sb34_00) != 0) {
        set_script_flag_bit(entry->entry_flag);
    }
    return apply_selected_entry_values(entry, entry_index);
}
