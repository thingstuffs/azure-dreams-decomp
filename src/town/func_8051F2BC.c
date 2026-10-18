#include "common.h"
#include "m2c_compat.h"

s32 func_800160D4(s32);
s32 lookup_entry_and_apply_record_code();     /* extern */
extern M2C_UNK D_80018E80;

/* Initializes the requested entry, then processes it with the shared data and supplied value. */
void call_set_script_flag_bit(s32 entry_id, s32 unused, s32 value) {
    func_800160D4(entry_id);
    lookup_entry_and_apply_record_code(&D_80018E80, entry_id, value);
}
