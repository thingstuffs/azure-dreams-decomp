#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene.h"
#include "town/scene/object.h"
#include "shared/town_root.h"

typedef s32 (*Callback)(s32);

/* Check whether the object callback returns 2 when the prerequisite value is at least 2. */
s32 check_object_callback_returns_two(void) {
    s32 callback_result;

    if (count_listed_enabled_records() >= 2) {
        callback_result = ((Callback)(town_scene_root->services->callback_2D4))(0);
        if (callback_result == 2)
            return 1;
    }
    return 0;
}
