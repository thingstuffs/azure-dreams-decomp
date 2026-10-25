#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/object_payload.h"
#include "shared/position_views.h"

s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */           /* extern */
extern M2C_UNK D_80023E64;
extern s32 linked_sprite_renderer_address[3];
extern M2C_UNK D_80079438;

typedef struct S_80956DA0_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80956DA0_1;

/* Creates an object with user data and initializes its position and rendering state. */
void create_user_data_object(s32 user_data) {
    ObjectNodeHeader *object;
    SpriteFrameState *render_state;
    S_80956DA0_1 *instance_data;
    s32 color;

    object = allocate_flagged_object_node(0x15);
    if (object != NULL) {
        object->update_callback = &D_80023E64;
        color = 0x800000;
        instance_data = (u8 *)object + 0x20;
        register_node(object, &linked_sprite_renderer_address);
        render_state = object->sprite;
        instance_data->unk_04 = user_data;
        ((SignedPositionView *)(object->position))->x = 0xF0;
        ((SignedPositionView *)(object->position))->y = 0xAC;
        ((SignedPositionView *)(object->position))->z = 0;
        render_state->scale_y = 0x1000;
        render_state->scale_x = 0x1000;
        render_state->depth_bias = 0x10;
        render_state->source = &D_80079438;
        render_state->unk_04 = 0;
        render_state->frame_ticks = 0;
        color |= 0x8080;
        render_state->color.word = color;
        render_state->flags = (u16) (render_state->flags | 0xC);
    }
}
