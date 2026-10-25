#include "common.h"
#include "m2c_compat.h"
#include "town/scene/entry_requests.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80018E30;

/* Passes a value to lookup_entry_and_apply_record_code with D_80018E30 as context. */
void decrement_current_entry_counter_condition(void *context, s32 unused, s32 lookup_key)
{
    lookup_entry_and_apply_record_code(&D_80018E30, context, lookup_key);
}
