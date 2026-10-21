#include "modules/town_map_props.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/vector.h"

typedef struct S_800BDB20_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
} S_800BDB20_0;

/* Creates an object at the given position and initializes its graphics. */
void *create_positioned_graphic_object_2(TownPropPosition *position, s32 object_param, s32 graphics_id) {
    SpriteFrameState *render_data;
    S_800BDB20_0 *object;
    IntVector3 *object_pos;

    object = allocate_flagged_object_node(0x132);
    if (object != 0) {
        register_node(object, project_sprite_chain);
        render_data = object->unk_0C;
        object_pos = object->unk_08;
        object->unk_10 = object_param;
        object_pos->x = (s32) position->unk_00;
        object_pos->y = (s32) position->unk_04;
        object_pos->z = (s32) position->unk_08;
        render_data->color.word = 0x808080;
        render_data->scale_y = 0x1000;
        render_data->scale_x = 0x1000;
        select_record_entry_and_value(render_data, graphics_id, 0);
    }
    return object;
}
