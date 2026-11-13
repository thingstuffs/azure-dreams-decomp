#include "common.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "shared/sprite_frame_state.h"
#include "town/scene/list_setup.h"
#include "town/player/object_setup.h"
#include "town/menu.h"
#include "town/player/object.h"
#include "town/scene.h"


extern void start_effect_when_bookshelf_fell();
extern M2C_UNK D_800D0DC0;

/* Initializes object callbacks and state, then sets unit scale. */
void initialize_unit_scale_object(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *transform) {
    NODE_HEADER(object)->update_callback = retire_object_on_check_or_callback;
    object->unk_50.as_pv = &start_effect_when_bookshelf_fell;
    initialize_object_transform_and_state((s32)(object), transform, 0xA);
    init_scene_node_mode_3(object, position, &D_800D0DC0);
    transform->offset_x = 0x1000;
    transform->scale_y = 0x1000;
    transform->scale_x = 0x1000;
    transform->angle_x = 0;
}
