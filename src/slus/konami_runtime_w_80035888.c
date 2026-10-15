#include "slus/render_words.h"

void func_80035888(void *node_storage, void *attached_object, s32 *init_data, s16 object_id, void *owner)
{
    void *node;
    void *object;
    void *aux_state;
    void *render_state;

    node = func_8003FF2C(0x11, node_storage, 0x49, D_80082BC0);
    ((S_80035888_0 *)node)->unk_10 = func_800359FC;
    func_8004491C(node, func_80033D54);

    object = (u8 *)node + 0x20;
    aux_state = ((S_80035888_0 *)node)->unk_08;
    render_state = ((S_80035888_0 *)node)->unk_0C;
    ((S_80035888_1 *)object)->unk_44 = init_data;
    ((S_80035888_1 *)object)->unk_48 = 1;
    ((S_80035888_1 *)object)->unk_4A = object_id;

    func_80033C1C(attached_object, *init_data);

    ((S_80035888_0 *)node)->unk_20 = attached_object;
    ((S_80035888_1 *)object)->unk_04 = 0;
    ((S_80035888_1 *)object)->unk_08 = func_80037714;
    func_800375C0(object, D_8006A9E8);
    func_800350B0(owner, object);

    {
        s32 color;
        s32 initial_state_14;
        s32 initial_state_18;

        color = 0x800000;
        initial_state_14 = D_800809B8;
        (*(void * *)((u8 *)object + 0x68)) = func_80035AAC;
        (*(s32 *)((u8 *)object + 0x14)) = initial_state_14;
        initial_state_18 = D_800809BC;
        color |= 0x8080;
        ((S_80035888_1 *)object)->unk_18 = initial_state_18;
        ((S_80035888_2 *)aux_state)->unk_02 = 0;
        ((S_80035888_3 *)render_state)->unk_0C = color;
        ((S_80035888_3 *)render_state)->unk_08 = D_8007386C;
        ((S_80035888_3 *)render_state)->unk_00 = 0;
        ((S_80035888_3 *)render_state)->unk_04 = 0;
        ((S_80035888_3 *)render_state)->unk_05 = 0;
        ((S_80035888_1 *)object)->unk_74 = owner;
        ((S_80035888_1 *)object)->unk_78 = ((Rec_func_80034F58_arg0 *)owner)->unk_01;
        ((S_80035888_5 *)(((S_80035888_0 *)node)->unk_20))->unk_34 =
            D_8006A90C[((S_80035888_6 *)(((S_80035888_1 *)object)->unk_74))->unk_02];
    }
}
