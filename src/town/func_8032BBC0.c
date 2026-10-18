#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern s32 get_script_flag_mask(s32);
extern void clear_script_flag_bit(s32);

/* Consume condition 0x3EB and invoke the callback when it is active. */
s32 consume_condition_3_eb(void) {
    if (get_script_flag_mask(0x3EB) != 0) {
        clear_script_flag_bit(0x3EB);
        D_80016000->unk_20->callback_2F8(0xD, 0x200);
        return 1;
    }
    return 0;
}
