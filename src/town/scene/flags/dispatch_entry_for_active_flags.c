#include "script_symbols.h"
#include "shared/game_work.h"
#include "town/player/script_flags.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
s32 apply_selected_entry_values();
s32 process_checked_entry(void *object, s32 entryIndex);
/* Update the context flag and dispatch the selected entry according to active flags. */
void dispatch_entry_for_active_flags(void *context, s32 entry_index)
{
    if (get_script_flag_mask(F_s34_sero_quickstart) != 0) {
        set_script_flag_bit(*((s16 *) (((s8 *) context) + 0x18)));
        process_checked_entry(context, entry_index);
        return;
    }
    if (get_script_flag_mask(F_s34_sero_start) != 0) {
        set_script_flag_bit(*((s16 *) (((s8 *) context) + 0x18)));
    }
    apply_selected_entry_values(context, entry_index);
}
