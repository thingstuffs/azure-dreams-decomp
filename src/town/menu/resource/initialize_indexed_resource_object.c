#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/slus_callbacks.h"
#include "shared/town_object.h"
#include "engine/node.h"
#include "town/menu/indexed_effect_vectors_g00583.h"


typedef struct S_800A7E7C_0_pre {
    s32 * unk_00;
    u8 pad_04[0xC];
} S_800A7E7C_0_pre;   /* the 0x10 bytes before arg0 in initialize_indexed_resource_object, addressed as arg0[-1] */

extern void update_linked_position_or_flag_object();

/* Initialize the object state from its byte value and set the context resource and callback. */
void initialize_indexed_resource_object(TownObjectRecord *object_arg, ObjectPosition *unused, struct SpriteFrameState *context) {
    TownObjectRecord *object = object_arg;

    ((S_800A7E7C_0_pre *)object)[-1].unk_00 = &update_linked_position_or_flag_object;
    object->slot = (s32) object->variant;
    context->source = &item_effect_descriptor;
    register_node_if_unregistered(object, project_sprite_chain);
}
