#include "common.h"
#include "town/scene/entry_requests.h"
#include "m2c_compat.h"
#include "town/scene.h"
extern M2C_UNK D_80018E18;
/* Feed the value to the D_80018E18 record. */
void apply_scene_record_value(void *context, s32 unused, s32 lookup_key)
{
    lookup_entry_and_apply_record_code(&D_80018E18, context, lookup_key);
}
