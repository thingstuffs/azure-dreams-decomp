#include "script_symbols.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"
#include "town/scene/flags.h"

s32 apply_record_value_for_either_flag(Rec_func_800165F4_arg0 *entry, s32 entry_index) {
    if (get_script_flag_mask(F_selfy_dungeon_tasuketa) != 0 ||
        get_script_flag_mask(F_selfy_dungeon_tasukenai) != 0) {
        set_script_flag_bit(entry->unk_18);
    }
    return apply_selected_entry_values(entry, entry_index);
}
