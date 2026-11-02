#include "common.h"
#include "town/scene/script_hooks.h"
#include "town/scene.h"
#include "town/data.h"
s32 func_8001E670(s32);                         /* extern */

/* Pass the current value of D_8001792C to func_8001E670. */
s32 apply_stored_value_1792_c(void) {
    return func_8001E670(scene_event_test_id);
}
