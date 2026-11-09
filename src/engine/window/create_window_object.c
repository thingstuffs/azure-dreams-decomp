#include "slus/owned_80035484.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"

/* Registers a window node, attaches it to its owner, and initializes its model, transform and appearance. */
void create_window_object(void *object_addr, S_func_80035484_4 *model, S_func_80035484_5 *config) {
    S_func_80035484_1 *state;
    ObjectPosition *transform;
    SpriteFrameState *appearance;
    ObjectNodeHeader *object;

    object = initialize_runtime_node_storage(0x11, object_addr, 0x49, &window_node_list_storage[0]);
    current_window_object = object;
    object->update_callback = invoke_window_object_callback;
    register_node(object, &draw_linked_sprite_nodes);
    transform = object->position;
    appearance = object->sprite;
    runtime_initialize_state_value(model, 0);
    state = NODE_BODY(object);
    state->model = model;
    model->unk_60 = 6;
    state->model->unk_10 = 0;
    state->model->unk_08 = 0x400;
    state->unk_04 = 0;
    state->unk_08 = 0;
    prepend_embedded_object_node(config, state);
    state->unk_68 = init_window_object;
    transform->x.w.i = -0x86;
    transform->y.w.i = 0x78;
    transform->z.w.i = 0x200;
    appearance->color.word = 0x808080;
    appearance->source = &window_default_render_data[0];
    appearance->unk_00 = 0;
    appearance->unk_04 = 0;
    appearance->frame_ticks = 0;
    state->unk_74 = config;
    state->model->unk_14 =
        *(s16 *)((u8 *)&window_variant_model_values[0] + config->unk_02 * 2);
    appearance->source =
        *(void **)((u8 *)&window_variant_render_data[0] + ((S_func_80035484_5 *)state->unk_74)->unk_02 * 4);
}
void * current_window_object = 0;
