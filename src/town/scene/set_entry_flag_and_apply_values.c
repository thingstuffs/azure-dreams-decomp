#include "script_symbols.h"
#include "town/player/script_flags.h"

#include "town/scene/record_actions.h"
#include "town/scene.h"

s32 set_entry_flag_and_apply_values(TownObjectSet *row, s32 entry_index) {
    set_script_flag_bit(row->entry_flag);
    clear_script_flag_bit(F_sbs07_pad21);
    return apply_selected_entry_values(row, entry_index);
}
