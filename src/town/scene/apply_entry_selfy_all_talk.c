#include "town/scene.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"
#include "town/scene/flags.h"

s32 apply_entry_selfy_all_talk(SquareSceneEntry *entry, s32 entry_index) {
    if (get_script_flag_mask(5003) != 0) {
        set_script_flag_bit(entry->unk_18);
    }
    return apply_selected_entry_values(entry, entry_index);
}
