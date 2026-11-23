#include "common.h"
#include "m2c_compat.h"
#include "town/scene/entry_requests.h"
#include "town/scene.h"

extern ScenePositionEntry D_80018E30;

/* Passes a value to lookup_entry_and_apply_record_code with D_80018E30 as context. */
void apply_record_code_from_d_80018e30_table(TownObjectSet *context, s32 unused, s32 lookup_key)
{
    lookup_entry_value_and_set_flag(&D_80018E30, context, lookup_key);
}
