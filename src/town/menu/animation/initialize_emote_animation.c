#include "common.h"
#include "slus.h"
#include "town/menu/object_setup.h"
#include "town/event/object_setup.h"
#include "m2c_compat.h"
struct Dst;
struct Elem;
#include "shared/sprite_source.h"
#include "town/event/state.h"
#include "town/data.h"

/* Initialize the object's animation data and default behavior. */
void initialize_emote_animation(TownObjectRecord *object, ObjectPosition *update_context, struct SpriteFrameState *animation_state) {
    select_record_entry_and_value(animation_state, &emote_sprite_entries, 0);
    initialize_optional_object_state(object, update_context, animation_state, 0);
}
