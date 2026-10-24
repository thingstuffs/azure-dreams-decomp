#include "common.h"
#include "town/scene/entry_requests.h"

extern void set_script_flag_bit(s32 bit_index);
extern void clear_script_flag_bit(s32 bit_index);
extern s32 get_script_flag_mask(s32 flagIndex);

// Processes the selected entry if the object's handle passes its status check.
s32 process_checked_entry(void *object, s32 entryIndex)
{
    s32 processed;
    u8 *entries;

    if (get_script_flag_mask(*(s16 *)((s8 *)object + 0x18)) == 0) {
        processed = 0;
    } else {
        entries = *(u8 **)((s8 *)object + 0x10);
        set_script_flag_bit(*(s16 *)(entries + entryIndex * 0x10 + 0xC));
        clear_script_flag_bit(*(s16 *)((s8 *)object + 0x18));
        processed = 1;
    }
    return processed;
}
