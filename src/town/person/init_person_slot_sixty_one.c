#include "town/person.h"
#include "shared/sprite_frame_state.h"

/* Register person slot 61 with its four data tables and set output halfword +0x12. */
void init_person_slot_sixty_one(void *object, void *unused, struct SpriteFrameState *output) {
    initialize_object_and_register_slot(object, 0x3D, D_800D6718, D_800D671C, D_800D66E8, D_800D66F0);
    output->clut = 2;
}
