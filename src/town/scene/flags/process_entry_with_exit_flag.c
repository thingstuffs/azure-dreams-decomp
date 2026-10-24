#include "town/scene.h"
#include "records/Rec_func_800165F4_arg0.h"

extern s32 get_script_flag_mask(s32);
extern void set_script_flag_bit(s32);
extern void apply_selected_entry_values(Rec_func_800165F4_arg0 *, s32);

/* Apply the entry's flag while exit flag 0x138E is set, then process its values. */
void process_entry_with_exit_flag(Rec_func_800165F4_arg0 *entry, s32 context)
{
    if (get_script_flag_mask(0x138E) != 0) {
        set_script_flag_bit(entry->unk_18);
    }
    apply_selected_entry_values(entry, context);
}
