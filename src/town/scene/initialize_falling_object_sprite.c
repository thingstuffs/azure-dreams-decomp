#include "town/scene/object.h"
#include "town/scene/list_setup.h"
#include "common.h"
#include "slus.h"
#include "town/event/state.h"
#include "town/scene.h"
extern u8 D_800EE344[];
extern s32 D_800D0678[];
extern s32 D_800D0690[];
void initialize_falling_object_sprite(FallingObjectState *object, void *context, void *sprite) {
    select_record_entry_and_value(sprite, D_800EE344, 0);
    handle_insert_initialize_two_values_status_flags(object, context, D_800D0678);
    initialize_optional_object_state(object, context, sprite, D_800D0690);
    object->phase = 13;
    object->mode = 5;
}
