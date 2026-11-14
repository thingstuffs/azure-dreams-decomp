#include "common.h"
#include "m2c_compat.h"

#include "town/person/object_setup.h"
#include "town/person/object.h"

/* Forward the object and two setup contexts to the selector. */
void forward_to_select_setup_path(void *object, void *value_1, SpriteFrameState *value_2, s32 value_3) {
    select_object_setup_path(object, value_1, value_2);
}
