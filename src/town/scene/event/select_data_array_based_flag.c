#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

extern void func_80017BA0(s32, s32);
extern void func_80018854(s32); /* placed copy of set_script_flag_bit */

extern u8 D_80019950[];
extern u8 D_80019A10[];

/* Select a data array based on flag 0x507, setting the flag on first use. */
void *select_data_array_based_flag(s32 first_input, s32 second_input) {
    void *result;

    func_80017BA0(first_input, second_input);
    if (func_8001894C(F_sbs07_pad16) == 0) {
        func_80018854(F_sbs07_pad16);
        result = D_80019950;
    } else {
        result = D_80019A10;
    }
    return result;
}
