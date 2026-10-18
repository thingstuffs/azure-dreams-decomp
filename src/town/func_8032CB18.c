#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s32 M2C_UNK;
s32 apply_selected_entry_values();
s32 process_checked_entry();
void set_script_flag_bit();
s32 get_script_flag_mask();
/* Update the context flag and dispatch the selected entry according to active flags. */
void dispatch_entry_for_active_flags(void *context, s32 entry_index)
{
    if (get_script_flag_mask(0x1459) != 0) {
        set_script_flag_bit(*((s16 *) (((s8 *) context) + 0x18)));
        process_checked_entry(context, entry_index);
        return;
    }
    if (get_script_flag_mask(0x1458) != 0) {
        set_script_flag_bit(*((s16 *) (((s8 *) context) + 0x18)));
    }
    apply_selected_entry_values(context, entry_index);
}
