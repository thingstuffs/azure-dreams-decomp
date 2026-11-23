#include "script_symbols.h"
#include "town/player/script_flags.h"
#include "town/scene.h"

s32 process_flag_and_forward_request(TownObjectSet *entry, s32 entry_index) {
    clear_script_flag_bit(Ftt_pad33);
    if (check_progress_against_callback() != 0) {
        set_script_flag_bit(entry->entry_flag);
    }
    return process_checked_entry(entry, entry_index);
}
