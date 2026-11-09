#include "common.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "shared/sprite_frame_state.h"
#include "town/scene/list_setup.h"
#include "town/player/object_setup.h"
#include "town/menu.h"
#include "town/player/object.h"
#include "town/scene.h"

extern M2C_UNK D_800D0DA8;

/* Initializes the object and sets its transform scale to 0xC00 on all axes. */
void initialize_scaled_effect_object(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *transform) {
    NODE_HEADER(object)->update_callback = &retire_object_on_check_or_callback;
    object->unk_50.as_s32 = 0;
    initialize_object_transform_and_state((s32)(object), transform, 0x48);
    configure_the_set_mode_n_3(object, position, &D_800D0DA8);
    transform->offset_x = 0xC00;
    transform->scale_y = 0xC00;
    transform->scale_x = 0xC00;
}
