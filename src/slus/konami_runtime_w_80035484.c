#include "slus/owned_80035484.h"

void func_80035484(s32 object_addr, S_func_80035484_4 *model, S_func_80035484_5 *config) {
    S_func_80035484_1 *state;
    S_func_80035484_2 *transform;
    S_func_80035484_3 *appearance;
    S_func_80035484_0 *object;

    object = initialize_runtime_node_storage(0x11, object_addr, 0x49, &D_80082BC0[0]);
    D_80081440 = object;
    object->unk_10 = invoke_window_object_callback;
    func_8004491C(object, &runtime_handle_transform_submit_textured_sprite_quads_each_node_invoke_callback);
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
    func_800350B0(config, state);
    state->unk_68 = func_80035614;
    transform->unk_02 = -0x86;
    transform->unk_06 = 0x78;
    transform->unk_0A = 0x200;
    appearance->unk_0C = 0x808080;
    appearance->unk_08 = &D_80073B54[0];
    appearance->unk_00 = 0;
    appearance->unk_04 = 0;
    appearance->unk_05 = 0;
    state->unk_74 = config;
    ((S_func_80035484_4 *)object->unk_20)->unk_14 =
        *(s16 *)((u8 *)&D_8006A93C[0] + config->unk_02 * 2);
    appearance->unk_08 =
        *(void **)((u8 *)&D_8006A8F0[0] + ((S_func_80035484_5 *)state->unk_74)->unk_02 * 4);
}
