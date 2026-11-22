#include "common.h"
#include "town/player.h"
#include "town/player/action_initializers.h"
#include "town/player/item.h"


/* Select the deferred action dispatcher in the object’s first callback slot. */
void set_deferred_dispatch_handler(TownObjectRecord *object, ObjectPosition *unused_position, struct SpriteFrameState *unused_context) {
    object->unk_00 = dispatch_deferred_callback;
}
