#include "common.h"
#include "town/person/object_setup.h"
#include "shared/sprite_frame_state.h"
#include "town/event/object_setup.h"
#include "town/scene/list_setup.h"
#include "records/Rec_D_800CFCB4.h"
#include "slus.h"
#include "town/person/object.h"
#include "town/event/state.h"
struct Dst;
struct Elem;
extern s32 common_object_state_handlers[];
extern u8 D_800ED15C[];


/* Initialize the object's sprite and behavior, then set its state bytes. */
void initialize_object_sprite(Rec_D_800CFCB4 *object, ObjectPosition *context, SpriteFrameState *sprite) {
    select_record_entry_and_value(sprite, &D_800ED15C, 0);
    init_scene_list_node(object, context, &common_object_bounds);
    initialize_optional_object_state(object, context, sprite, common_object_state_handlers);
    object->unk_4D.as_s8 = 0xD;
    object->unk_4C = 7;
}
