#include "common.h"
#include "engine/graphics.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "frontend/settings.h"

typedef struct S_7FDD3A2C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    s32 unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_7FDD3A2C_0;

typedef struct S_7FDD3A2C_1 {
    s32 unk_00;
    s32 unk_04;
} S_7FDD3A2C_1;   /* arg0 in create_type */

/* Creates a type 0x136 object and initializes its position and rendering state. */
void *create_type(S_7FDD3A2C_1 *position, s32 object_value, s32 render_value, s32 extra_value) {
    S_7FDD3A2C_0 *object;
    SpriteFrameState *render_state;

    object = allocate_flagged_object_node(0x136);
    if (object != 0) {
        object->unk_10 = object_value;
        ((ObjectNodeHeader *)object)->position->x.v = (s32) position->unk_00;
        ((ObjectNodeHeader *)object)->position->y.v = (s32) position->unk_04;
        register_node(object, draw_linked_sprites);
        render_state = object->unk_0C;
        render_state->scale_y = 0x1000;
        render_state->scale_x = 0x1000;
        render_state->source = render_value;
        render_state->color.word = 0x808080;
        object->unk_20 = extra_value;
    }
    return object;
}
