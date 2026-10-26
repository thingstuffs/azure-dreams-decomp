#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

extern s32 has_matching_entry_result(s32, s32);
extern void set_current_entry_script_flag(void);
extern s32 apply_selected_entry_values(s32, s32);

/* Processes the selected context entry and applies a fallback value on failure. */
s32 process_context_entry_with_fallback(s32 entryContext, s32 entryIndex)
{
    if (has_matching_entry_result(13, 1) != 0) {
        set_current_entry_script_flag();
    }

    if (apply_selected_entry_values(entryContext, entryIndex) == 0) {
        clear_script_flag_bit(Ftt_pad78);
        return 0;
    }

    return 1;
}
