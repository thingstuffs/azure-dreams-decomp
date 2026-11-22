#include "script_symbols.h"
#include "town/player/script_flags.h"
#include "town/scene.h"
#include "town/scene/flags.h"

s32 process_entry_with_sbs17_pad03(void *entry, s32 index)
{
    if (get_script_flag_mask(F_sbs17_pad03)) {
        set_current_entry_script_flag();
    }
    return process_checked_entry(entry, index);
}
