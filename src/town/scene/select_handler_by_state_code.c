#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"

/*
 * While F_sbs22_pad28 is set, runs func_80019880 and returns func_80019814 of the supplied values;
 * otherwise applies the signed indexed value and returns one.
 */
s32 select_handler_by_state_code_0x798(void *primaryInput, s32 secondaryInput) {
    s32 result;

    if (func_8001A510(F_sbs22_pad28) != 0) {
        func_80019880();
        result = func_80019814(primaryInput, secondaryInput);
    } else {
        apply_signed_value_to_indexed_entry(primaryInput, secondaryInput);
        result = 1;
    }

    return result;
}
