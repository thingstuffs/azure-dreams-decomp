#include "common.h"

extern s32 get_script_flag_mask(s16 flagIndex);
extern void set_current_entry_script_flag(void);
extern void set_script_flag_bit(s32 bit_index);
extern u8 D_8001E6F8[];
extern u8 D_8001F4CD[];
extern u8 D_8001F4E2[];

// Returns event-specific data, running the fallback action when the object check fails.
void *select_event_data_and_fallback(void *object, s32 unused, s32 eventCode) {
    if (eventCode == 0x25) {
        if (get_script_flag_mask(*(s16 *)((u8 *)object + 0x18)) != 0) {
            return D_8001F4E2;
        }
        set_current_entry_script_flag();
        set_script_flag_bit(0x145D);
        return D_8001E6F8;
    }
    if (eventCode == 0x44) {
        return D_8001F4CD;
    }
    return 0;
}
