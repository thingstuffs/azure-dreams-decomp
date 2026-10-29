#include "common.h"
#include "town/menu/object_setup.h"
#include "town/event/object_setup.h"
#include "town/scene/list_setup.h"
#include "m2c_compat.h"

void select_record_entry_and_value(void *state, void *entries, short index);
extern M2C_UNK D_800D0690;
#include "shared/sprite_source.h"
#include "town/event/state.h"
extern SpriteSourceEntry emote_sprite_entries[];
extern M2C_UNK D_800D6A58;

/* Initialize the object's sprite, scene data, and behavior. */
void initialize_emote_sprite_and_scene(void *object, void *scene, struct SpriteFrameState *sprite) {
    select_record_entry_and_value(sprite, &emote_sprite_entries, 0);
    handle_insert_initialize_two_values_status_flags(object, scene, &D_800D6A58);
    initialize_optional_object_state(object, scene, sprite, &D_800D0690);
}
