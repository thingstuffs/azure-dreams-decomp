#include "common.h"

#include "common.h"
#include "records/Rec_D_80081FDC.h"
#include "records/Rec_func_80036210_arg0.h"
#include "engine/node.h"
#include "slus.h"
#include "slus/data.h"

typedef struct S_80036B10_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void (*unk_10)(void);
    u8 pad_14[0xC];
    void * unk_20;
} S_80036B10_0;   /* temp_v0 in create_cursor_object */

typedef struct S_80036B10_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x38];
    s32 * unk_44;
    s8 unk_48;
    u8 pad_49[0x1];
    s16 unk_4A;
} S_80036B10_1;   /* temp_s1 in create_cursor_object */


typedef struct S_80036B10_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80036B10_3;   /* temp_s6 in create_cursor_object */


typedef struct S_80036B10_4 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80036B10_4;   /* temp_v0 in create_cursor_object */


typedef struct S_80036B10_6 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} S_80036B10_6;   /* ((S_80036B10_4 *)temp_v0)->unk_20 in create_cursor_object */

typedef struct S_80036B10_7 {
    u8 pad_00[0x80];
    s32 * unk_80;
} S_80036B10_7;   /* ((Rec_func_80036210_arg0 *)arg2)->unk_74.as_pm in create_cursor_object */

typedef struct S_80036B10_8 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_80036B10_8;   /* ((S_80036B10_7 *)(((Rec_func_80036210_arg0 *)arg2)->unk_74.as_pm))->unk_80 in create_cursor_object */



void runtime_initialize_state_value(Rec_D_80081FDC *state, s32 initialValue);
void prepend_embedded_object_node();
extern u8 window_node_list_storage[];
extern void runtime_handle_transform_submit_textured_sprite_quads_each_node_invoke_callback(void);
extern void update_cursor_callback(void);

/* Initializes and links a task, then sets up its source record, state, and rendering data. */
void create_cursor_object(s32 task_buffer, Rec_D_80081FDC *record, s32 *source, s16 state_value, s32 setup_arg) {
    S_80036B10_1 *state;
    S_80036B10_3 *render_data;
    void *task;
    s16 *variant_table;

    task = initialize_runtime_node_storage(0x11, task_buffer, 0x49, &window_node_list_storage);
    ((S_80036B10_0 *)task)->unk_10 = update_cursor_callback;
    register_node(task, &runtime_handle_transform_submit_textured_sprite_quads_each_node_invoke_callback);
    state = task + 0x20;
    render_data = ((S_80036B10_0 *)task)->unk_0C;
    state->unk_44 = source;
    state->unk_48 = 1;
    state->unk_4A = state_value;
    runtime_initialize_state_value(record, *source);
    ((S_80036B10_0 *)task)->unk_20 = record;
    record->unk_60 = 6;
    ((S_80036B10_6 *)(((S_80036B10_4 *)task)->unk_20))->unk_10 = 0x10C;
    variant_table = (s16 *)&cursor_variant_values;
    ((S_80036B10_6 *)(((S_80036B10_4 *)task)->unk_20))->unk_14 =
        variant_table[((S_80036B10_8 *)(((S_80036B10_7 *)(((Rec_func_80036210_arg0 *)source)->unk_74.as_pm))->unk_80))->unk_02];
    state->unk_04 = 0;
    state->unk_08 = 0;
    prepend_embedded_object_node(setup_arg, state);
    render_data->unk_0C = 0x808080;
    select_record_entry_and_value(render_data, &cursor_sprite_source, 0);
}
