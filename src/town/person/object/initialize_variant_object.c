#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person.h"
#include "town/person/object.h"

extern M2C_UNK D_800D69DC;
extern M2C_UNK D_800D69E4;
extern M2C_UNK D_800D6A0C;
extern M2C_UNK D_800D6A10;


/* Initialize the object with resource 8 and apply its stored variant. */
void initialize_variant_object(TownObjectRecord *body, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite) {
    TownObjectRecord *object = body;

    initialize_object_and_register_slot(object, 8, &D_800D6A0C, &D_800D6A10, &D_800D69DC, &D_800D69E4);
    create_and_invoke_render_object(object, object->variant.as_u8);
}
