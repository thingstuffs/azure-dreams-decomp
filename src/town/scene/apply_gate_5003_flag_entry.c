#include "town/scene.h"
extern s32 get_script_flag_mask(s32);
extern void set_current_entry_script_flag(void);
extern s32 apply_selected_entry_values(void *, s32);
extern void set_script_flag_bit(s32);
extern s32 process_checked_entry(void *, s32);

s32 apply_gate_5003_flag_entry(SquareSceneEntry *entry, s32 entry_index) {
    if (get_script_flag_mask(5003) != 0) {
        set_script_flag_bit(entry->unk_18);
    }
    return apply_selected_entry_values(entry, entry_index);
}
