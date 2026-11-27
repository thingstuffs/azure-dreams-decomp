#include "common.h"
#include "town/person/current_transform_object_data.h"
#include "town/scene/list_setup.h"
#include "m2c_compat.h"
#include "town/person/object.h"

extern M2C_UNK D_800C26C0[3];
#include "town/scene/active_object_overlap_g00529.h"


/* Initialize the object values to 0x40, apply its indexed setup, and assign its table. */
void initialize_transform_object_values(TownObjectRecord *object, ObjectPosition *setup_context, SpriteFrameState *unused) {
    object->roam_range_x = 0x40;
    object->roam_range_y = 0x40;
    init_scene_node_mode_1(object, setup_context, person_transform_defaults[(u8)object->state_index]);
    object->state_callback.as_pm = D_800C26C0;
}
