#include "shared/sprite_frame_state.h"
#include "shared/town_object.h"
#include "town/menu/state.h"

/* Store the negated value from the source's linked data in the destination. */
void copy_negated_menu_phase(DoorDisplayBody *source, ObjectPosition *unused, LitMeshSprite *mesh) {
    mesh->rotation[2] = (s16) (0 - source->owner->origin_heading);
}
