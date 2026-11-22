#include "common.h"
#include "shared/town_object.h"
#include "dungeon/actor.h"

#include "town/person/object.h"

/* The timeout forwards the dispatch position and sprite in the incoming registers. */
void apply_setup_on_timeout_variant_3(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    u16 remaining_count;

    remaining_count = object->timer - 1;
    object->timer = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        apply_object_setup_and_update(object, position, sprite);
    }
}
