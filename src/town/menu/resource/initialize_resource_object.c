#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/slus_callbacks.h"
#include "shared/town_object.h"

typedef struct S_800A7C98_0_pre {
    s32 * unk_00;
    u8 pad_04[0xC];
} S_800A7C98_0_pre;   /* the 0x10 bytes before arg0 in initialize_resource_object, addressed as arg0[-1] */


#include "town/system/clear_object_status_and_dispatch_target_api.h"
#include "engine/node.h"
#include "town.h"

extern M2C_UNK D_800F8F68;

/* Clear the object state field and initialize its resource data and callback. */
void initialize_resource_object(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context) {
    ((S_800A7C98_0_pre *)object)[-1].unk_00 = &handle_object_bounds_and_cleanup;
    object->unk_50.as_s32 = 0;
    clear_object_status_and_dispatch_target(object, context, (int)(&D_800F8F68), 0);
    register_node_if_unregistered(object, (project_sprite_chain));
}
