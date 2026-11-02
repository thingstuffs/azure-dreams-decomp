#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"

s32 forward_stored_pair(s32);
extern M2C_UNK D_80018E80;

/* Initializes the requested entry, then processes it with the shared data and supplied value. */
void call_set_script_flag_bit(s32 entry_id, s32 unused, s32 value) {
    forward_stored_pair(entry_id);
    lookup_entry_apply_record_code(&D_80018E80, entry_id, value);
}
