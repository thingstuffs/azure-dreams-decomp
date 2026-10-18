#include "common.h"

extern s32 get_script_flag_mask(s32 flagIndex);
extern void set_indexed_entry_flag(s32 record, s32 entry_index);

s32 dispatch_if_condition_1463(s32 dispatch_value, s32 dispatch_option) {
    if (get_script_flag_mask(0x1463) != 0) {
        set_indexed_entry_flag(dispatch_value, dispatch_option);
        return 1;
    }
    return 0;
}
