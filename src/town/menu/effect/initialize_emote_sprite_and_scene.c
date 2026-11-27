#include "common.h"
#include "slus.h"
#include "town/menu/object_setup.h"
#include "town/event/object_setup.h"
#include "town/scene/list_setup.h"
#include "m2c_compat.h"

extern s32 common_object_state_handlers[];
#include "shared/sprite_source.h"
#include "town/event/state.h"
#include "town/data.h"
#include "town/menu/effect.h"

/* Initialize the object's sprite, scene data, and behavior. */
void initialize_emote_sprite_and_scene(struct EmoteCallbackObject *object, ObjectPosition *scene, struct SpriteFrameState *sprite) {
    select_record_entry_and_value(sprite, &emote_sprite_entries, 0);
    init_scene_list_node(object, scene, &flat_object_bounds);
    initialize_optional_object_state(object, scene, sprite, common_object_state_handlers);
}
