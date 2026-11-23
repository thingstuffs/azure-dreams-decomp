#include "town/player.h"
#include "town/scene.h"
#include "town/scene/flags.h"

s32 apply_entry_values_flag_at_twenty(TownObjectSet *entry, s32 entry_index) {
    if (get_town_state_count() >= 20) {
        set_current_entry_script_flag();
    }
    return apply_selected_entry_values(entry, entry_index);
}
