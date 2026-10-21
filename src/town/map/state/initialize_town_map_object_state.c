#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"

struct Rec_D_80081FDC; void runtime_initialize_state_value(struct Rec_D_80081FDC *, s32);
void unlink_node_if_registered();
struct Container; struct Source; void copy_window_params(struct Container *, struct Source *);
void select_record_entry_and_value(void *, void *, s16);
s32 register_node();
extern u8 town_map_tag;
extern u8 D_80037714;
extern u8 D_800794AC;
extern s32 town_map_selection;
extern M2C_UNK D_8008B9D8;
extern M2C_UNK D_8008BA00;
extern s32 D_800CFB74[];
extern u8 D_800CFC38[];
extern s32 D_800CFC44[];
/* Initializes a town object and its state for the selected type. */
void initialize_town_map_object_state(s32 type_id, s32 *init_value_ptr, void *object, void *context)
{
    s32 type_data;
    s32 init_value;
    void *state;
    SpriteFrameState *render_data;
    void *transform;
    s32 *type_table;
    s32 *value_table_base;
    s32 *value_table;
    s32 *type_entry;
    *((s32 **) (((s8 *) object) + 0x10)) = &D_8008B9D8;
    register_node(object, &town_map_tag);
    init_value = 0;
    transform = *((void **) (((s8 *) object) + 8));
    render_data = *((void **) (((s8 *) object) + 0xC));
    state = object + 0x20;
    if (init_value_ptr != 0) {
        init_value = *init_value_ptr;
    }
    runtime_initialize_state_value(context, init_value);
    {
        s32 context_mode;
        context_mode = 2;
        type_table = D_800CFB74;
        *((void **) (((s8 *) object) + 0x20)) = context;
        *((s32 *) (((s8 *) context) + 0x60)) = context_mode;
    }
    *((s32 *) (((s8 *) state) + 4)) = 0;
    *((s16 *) (((s8 *) state) + 0x66)) = type_id;
    type_entry = type_table - (-type_id);
    type_data = *type_entry;
    if (type_data != 0) {
        *((s32 **) (((s8 *) state) + 8)) = &D_80037714;
        copy_window_params(state, (struct Source *)(type_data));
    }
    else {
        *((s32 **) (((s8 *) state) + 8)) = 0;
    }
    *((s16 *) (((s8 *) state) + 0x60)) = 0;
    render_data->color.word = 0x808080;
    if (((u32) (type_id - 9)) < 2U) {
        select_record_entry_and_value(render_data, &D_800794AC, 0);
    }
    else {
        render_data->source = 0;
    }
    if (type_id == 0) {
        *((s16 *) (((s8 *) transform) + 2)) = 0x20;
        *((s16 *) (((s8 *) transform) + 6)) = -0x20;
        *((s16 *) (((s8 *) transform) + 0xA)) = 0x200;
    }
    if (type_id == 0xA) {
        *((s32 *) (((s8 *) state) + 0x74)) = 0;
        town_map_selection = (s32) (*(*((u8 **) (((s8 *) state) + 0x7C))));
    }
    *((s32 **) (((s8 *) state) + 0x68)) = &D_8008BA00;
    value_table_base = D_800CFC44;
    value_table = value_table_base;
    *((s16 *) (((s8 *) state) + 0x64)) = (s16) ((s8) D_800CFC38[type_id]);
    *((s32 *) (((s8 *) state) + 0x6C)) = value_table[type_id];
    if (type_id == 9) {
        unlink_node_if_registered(state);
    }
}
