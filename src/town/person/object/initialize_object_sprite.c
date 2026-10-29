#include "common.h"
#include "town/person/object_setup.h"
#include "shared/sprite_frame_state.h"
#include "town/event/object_setup.h"
#include "town/scene/list_setup.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"
#include "slus.h"
#include "town/person/object.h"
struct Dst;
struct Elem;
extern s32 D_800D0678[];
extern M2C_UNK D_800D0690;
extern u8 D_800ED15C[];


/* Initialize the object's sprite and behavior, then set its state bytes. */
void initialize_object_sprite(Rec_D_800CFCB4 *object, void *context, SpriteFrameState *sprite) {
    select_record_entry_and_value(sprite, &D_800ED15C, 0);
    handle_insert_initialize_two_values_status_flags(object, context, &D_800D0678);
    initialize_optional_object_state(object, context, sprite, &D_800D0690);
    object->unk_4D.as_s8 = 0xD;
    object->unk_4C = 7;
}
