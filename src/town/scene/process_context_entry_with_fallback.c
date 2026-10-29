#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene.h"
#include "town/scene/flags.h"

#include "town/scene/record_actions.h"

/* Processes the selected context entry and applies a fallback value on failure. */
s32 process_context_entry_with_fallback(Rec_func_800165F4_arg0 *entry_context, s32 entry_index)
{
    if (has_matching_entry_result(13, 1) != 0) {
        set_current_entry_script_flag();
    }

    if (apply_selected_entry_values(entry_context, entry_index) == 0) {
        clear_script_flag_bit(Ftt_pad78);
        return 0;
    }

    return 1;
}
