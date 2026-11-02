#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"

extern u8 D_80019950[];
extern u8 D_80019A10[];

/* Select a data array based on flag 0x507, setting the flag on first use. */
void *select_data_array_based_flag(s32 first_input, s32 second_input) {
    void *result;

    set_indexed_entry_flag(first_input, second_input);
    if (get_script_flag_mask(F_sbs07_pad16) == 0) {
        set_script_flag_bit(F_sbs07_pad16);
        result = D_80019950;
    } else {
        result = D_80019A10;
    }
    return result;
}
