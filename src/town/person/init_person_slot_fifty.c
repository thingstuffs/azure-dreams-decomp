#include "town/person.h"
#include "shared/sprite_frame_state.h"

/* Register person slot 50 with its four data tables. */
void init_person_slot_fifty(TownObjectRecord *body, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite) {
    TownObjectRecord *object = body;

    register_object_slot_with_tables(object, 50, D_800D71F4, D_800D71F8, D_800D71C4, D_800D71CC);
}
