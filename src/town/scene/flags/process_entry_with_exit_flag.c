#include "town/scene.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"
#include "town/scene/flags.h"


/* Apply the entry's flag while exit flag 0x138E is set, then process its values. */
s32 process_entry_with_exit_flag(TownObjectSet *entry, s32 context)
{
    if (get_script_flag_mask(0x138E) != 0) {
        set_script_flag_bit(entry->entry_flag);
    }
    return apply_selected_entry_values(entry, context);
}
