#include "town/scene/object.h"
#include "town/scene/list_setup.h"
#include "common.h"
#include "slus.h"
#include "town/event/state.h"
#include "town/scene.h"
#include "shared/sprite_source.h"
extern SpriteSourceEntry falling_object_sprite_sources[];
extern s32 common_object_state_handlers[];
void initialize_falling_object_sprite(FallingObjectState *object, ObjectPosition *context, SpriteFrameState *sprite) {
    select_record_entry_and_value(sprite, falling_object_sprite_sources, 0);
    init_scene_list_node(object, context, &common_object_bounds);
    initialize_optional_object_state(object, context, sprite, common_object_state_handlers);
    object->phase = 13;
    object->mode = 5;
}
