#include "town/scene.h"
#include "town/scene/record_actions.h"
#include "town/scene/flags.h"
#include "town/scene/event.h"
#include "town/scene/hooks.h"

extern u8 D_8001C33C[];
extern u8 D_8001E4E8[];
extern s32 func_8001822C(SquareSceneEntry *, s32);
extern void *forward_values_to_fixed_data_handler(SquareSceneEntry *, s32, s32);
extern s32 contains_record_value_in_byte_0(s32);
s32 flag_entry_if_record_eleven(SquareSceneEntry *entry, s32 entry_index) {
    s32 result;
    if (contains_record_value_in_byte_0(11) == 0) {
        result = 0;
    } else {
        set_indexed_entry_flag(entry, entry_index);
        result = 1;
    }
    return result;
}

/* Complete choice array, including its terminal fallback record. */
TownSceneChoice square_record_choices[4] = {
    { func_8001822C, get_event_data_pointer, D_8001E4E8, 3473, 0 },
    { forward_data_and_value, select_context_data_with_flag_override, D_8001E4E8, 3474, 0 },
    { flag_entry_if_record_eleven, forward_values_to_fixed_data_handler, D_8001E4E8, 3475, 0 },
    { return_zero_fn, get_shared_entry_buffer, D_8001C33C, 0, 0 },
};
