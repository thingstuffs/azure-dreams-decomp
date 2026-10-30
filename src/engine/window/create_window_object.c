#include "slus/owned_80035484.h"

#include "slus/owned_80035484.h"

/* Registers a window node, attaches it to its owner, and initializes its model, transform and appearance. */
void create_window_object(void *object_addr, S_func_80035484_4 *model, S_func_80035484_5 *config) {
    S_func_80035484_1 *state;
    S_func_80035484_2 *transform;
    S_func_80035484_3 *appearance;
    S_func_80035484_0 *object;

    object = initialize_runtime_node_storage(0x11, object_addr, 0x49, &window_node_list_storage[0]);
    current_window_object = object;
    object->unk_10 = invoke_window_object_callback;
    register_node(object, &draw_linked_sprite_nodes);
    transform = object->unk_08;
    appearance = object->unk_0C;
    runtime_initialize_state_value(model, 0);
    object->unk_20 = model;
    model->unk_60 = 6;
    state = (S_func_80035484_1 *)((u8 *)object + 0x20);
    ((S_func_80035484_4 *)object->unk_20)->unk_10 = 0;
    ((S_func_80035484_4 *)object->unk_20)->unk_08 = 0x400;
    state->unk_04 = 0;
    state->unk_08 = 0;
    prepend_embedded_object_node(config, state);
    state->unk_68 = init_window_object;
    transform->unk_02 = -0x86;
    transform->unk_06 = 0x78;
    transform->unk_0A = 0x200;
    appearance->unk_0C = 0x808080;
    appearance->unk_08 = &window_default_render_data[0];
    appearance->unk_00 = 0;
    appearance->unk_04 = 0;
    appearance->unk_05 = 0;
    state->unk_74 = config;
    ((S_func_80035484_4 *)object->unk_20)->unk_14 =
        *(s16 *)((u8 *)&window_variant_model_values[0] + config->unk_02 * 2);
    appearance->unk_08 =
        *(void **)((u8 *)&window_variant_render_data[0] + ((S_func_80035484_5 *)state->unk_74)->unk_02 * 4);
}
void * current_window_object = 0;
