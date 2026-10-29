#include "common.h"
#include "town/menu/object_setup.h"
#include "town/event/object_setup.h"
#include "m2c_compat.h"
struct Dst;
struct Elem;
void select_record_entry_and_value(void *state, void *entries, short index); /* extern */
#include "shared/sprite_source.h"
#include "town/event/state.h"
extern SpriteSourceEntry emote_sprite_entries[];

/* Initialize the object's animation data and default behavior. */
void initialize_emote_animation(void *object, void *update_context, struct SpriteFrameState *animation_state) {
    select_record_entry_and_value(animation_state, &emote_sprite_entries, 0);
    initialize_optional_object_state(object, update_context, animation_state, 0);
}
