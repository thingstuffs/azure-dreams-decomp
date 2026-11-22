/* Transform state. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C520C. */
#include "slus/map_state.h"
#include "town/person/transform_state_g00657.h"
#include "town/person.h"
#include "town/scene.h"

/* Returns the address of the indexed 24-byte entry. */
Box *get_transform_entry_by_index(s32 entry_index) {
    return &D_800D4FB8[entry_index];
}

/* Sets the motion page and updates the object state and orientation. */
void update_transform_motion_page(TownObjectRecord *object_data, ObjectPosition *motion) {
    if (map_runtime_state.scene_selector == 12 && map_runtime_state.map_index == 23) {
        motion->z.v = 0xFF600000;
    } else {
        motion->z.v = 0xFFE00000;
    }
    init_scene_node_mode_1(object_data, motion, get_transform_entry_by_index(0));
    object_data->unk_50.as_pv = &D_800C2A10;
    object_data->unk_16 = (s16) ((((u16)object_data->heading) - 0x800) & 0xFFF);
}

/* Update the object's state value according to whether the pair check returns zero. */
void update_transform_state_value(TownObjectRecord *object) {
    Box *bounds;
    s32 result;

    result = is_angle_within_tolerance(D_800FE4A6, object->unk_16);
    if (result != 0) {
        bounds = get_transform_entry_by_index(0);
    } else {
        bounds = get_transform_entry_by_index(1);
    }
    ((TownSceneListNode *)object)->bounds = bounds;
}
