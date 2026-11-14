#include "town/scene/event.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"

extern M2C_UNK D_80018E80;

/* Apply the stored global pair, then process the requested entry with the supplied value. */
void call_set_script_flag_bit(s32 entry_id, s32 unused, s32 value) {
    forward_stored_pair();
    lookup_entry_value_and_set_flag(&D_80018E80, entry_id, value);
}
