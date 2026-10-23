#include "script_symbols.h"
#include "common.h"

extern void set_current_entry_script_flag(void);
extern void set_script_flag_bit(s32 bit_index);
extern u8 scene_event_buffer[];
extern u8 D_8001DD86[];
extern u8 D_8001DDA1[];

/* Dispatch the selected action and return its associated data pointer. */
void *select_action_data_and_process(s32 unused_1, s32 unused_2, s32 action) {
    void *result;

    if (action == 1) {
        set_script_flag_bit(Ftt_pad73);
        result = scene_event_buffer;
    } else if (action != 3) {
        result = D_8001DD86;
    } else {
        set_current_entry_script_flag();
        result = D_8001DDA1;
    }
    return result;
}
