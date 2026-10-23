#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"

typedef void (*Callback)(void);

typedef struct S_func_800A1C94_0 {
    u8 pad_00[0xC];
    void *unk_0C;
    Callback unk_10;
    u8 pad_14[0xC];
    Callback unk_20;
} S_func_800A1C94_0;

typedef struct S_func_800A1C94_2 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} S_func_800A1C94_2;

extern void *allocate_list_node(s32 kind, void *owner);
extern void render_shaded_object_primitive(void);
extern void initialize_indexed_render_state(void);

/* Creates a display object with callbacks and the supplied payload values. */
void *create_display_object_with_callbacks(s32 payload_word, s32 payload_halfword)
{
    S_func_800A1C94_0 *object;
    SpriteFrameState *display;
    S_func_800A1C94_2 *payload;

    object = allocate_list_node(0x136, ((u8 *)(&scene_object_list_anchor)));
    if (object == 0) {
        return 0;
    }

    object->unk_10 = render_shaded_object_primitive;
    display = object->unk_0C;
    object->unk_20 = initialize_indexed_render_state;

    payload = (S_func_800A1C94_2 *)((u8 *)object + 0x20);
    payload->unk_10 = payload_word;
    payload->unk_20 = payload_halfword;

    display->scale_y = 0xAAA;
    display->scale_x = 0xAAA;
    display->depth_bias = 9;
    return object;
}
