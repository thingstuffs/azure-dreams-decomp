#include "town/scene.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"
extern void set_current_entry_script_flag(void);
extern s32 process_checked_entry(void *, s32);

s32 apply_gate_5211_flag_entry(SquareSceneEntry *entry, s32 entry_index) {
    if (get_script_flag_mask(5211) != 0) {
        set_script_flag_bit(entry->unk_18);
    }
    return apply_selected_entry_values(entry, entry_index);
}
