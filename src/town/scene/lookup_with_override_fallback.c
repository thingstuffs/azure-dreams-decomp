#include "common.h"
#include "shared/town_dispatch_object.h"
#include "m2c_compat.h"
#include "town/scene/position_entries.h"

s32 resolve_entry_flag();         /* extern */
extern ScenePositionEntry D_8001B234;
extern M2C_UNK D_8001DE4A;

/* Return the lookup result, or the fallback when the override check succeeds. */
s32 *lookup_with_override_fallback(void *key, s32 unused, s32 context) {
    s32 *result;

    result = apply_entry_position(&D_8001B234, active_scene_dispatch_context, key, context);
    if (resolve_entry_flag(&D_8001B234, key, context) != 0) {
        result = &D_8001DE4A;
    }
    return result;
}
