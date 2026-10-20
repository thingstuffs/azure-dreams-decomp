#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 lookup_entry_and_apply_record_code();              /* extern */
extern M2C_UNK D_80018E60;

/* Passes the value to lookup_entry_and_apply_record_code with D_80018E60 as context. */
void dispatch_scene_value_a(s32 value) {
    lookup_entry_and_apply_record_code(&D_80018E60, value);
}
