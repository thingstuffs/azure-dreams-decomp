#include "common.h"

#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"

/* Forward the object and parameters to apply_object_setup_and_update. */
void forward_reaction_update(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    apply_object_setup_and_update(object, position, sprite);
}
