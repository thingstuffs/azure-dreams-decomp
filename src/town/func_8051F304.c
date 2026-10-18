#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 lookup_entry_and_apply_record_code();              /* extern */
extern M2C_UNK D_80018E90;

/* Passes a value to lookup_entry_and_apply_record_code using D_80018E90 as context. */
void dispatch_scene_value_c(s32 value) {
    lookup_entry_and_apply_record_code(&D_80018E90, value);
}
