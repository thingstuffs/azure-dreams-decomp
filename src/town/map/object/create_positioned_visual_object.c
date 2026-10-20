#include "modules/town_map_props.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/vector.h"

typedef struct S_800BDBD0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
} S_800BDBD0_0;

/* Creates an object at the supplied position and initializes its visual properties. */
void *create_positioned_visual_object(TownPropPosition *source_pos, s32 object_data, s32 angle, s32 visual_data) {
    S_800BDBD0_0 *object;
    SpriteFrameState *visual;
    IntVector3 *position;

    object = func_8003FC64(0x136);
    if (object != NULL) {
        register_node(object, draw_linked_lit_meshes);
        visual = object->unk_0C;
        object->unk_10 = object_data;
        visual->angle_z = (s16) angle;
        visual->scale_x = 0x1000;
        visual->scale_y = 0x1000;
        visual->unk_20 = 0x1000;
        visual->color.word = 0x808080;
        visual->source = visual_data;
        position = object->unk_08;
        position->x = source_pos->unk_00;
        position->y = source_pos->unk_04;
        position->z = source_pos->unk_08;
    }
    return object;
}
