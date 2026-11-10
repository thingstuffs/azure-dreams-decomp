#include "common.h"
#include "m2c_compat.h"
#include "town/scene/flags.h"

extern M2C_UNK D_800194E8;

/* Call func_80017BA0, then return the address of D_800194E8. */
s32 *dispatch_by_state_code_0x798(s32 first_input, s32 second_input) {
    set_indexed_entry_flag(first_input, second_input);
    return &D_800194E8;
}
