#include "engine/window/cursor_body.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"

#include "records/Rec_D_80081FDC.h"
#include "records/Rec_func_80036210_arg0.h"
#include "engine/node.h"
#include "slus.h"
#include "slus/data.h"
#include "slus/window_node_list_data.h"
#include "engine/window.h"
#include "engine/object.h"




typedef struct S_80036B10_7 {
    u8 pad_00[0x80];
    s32 * unk_80;
} S_80036B10_7;   /* ((Rec_func_80036210_arg0 *)arg2)->unk_74.as_pm in create_cursor_object */

typedef struct S_80036B10_8 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_80036B10_8;   /* ((S_80036B10_7 *)(((Rec_func_80036210_arg0 *)arg2)->unk_74.as_pm))->unk_80 in create_cursor_object */


/* Initializes and links a task, then sets up its source record, state, and rendering data. */
void create_cursor_object(void *task_buffer, Rec_D_80081FDC *record, s32 *source, s16 state_value, void *setup_arg) {
    WindowCursorBody *state;
    SpriteFrameState *render_data;
    ObjectNodeHeader *task;
    s16 *variant_table;

    task = initialize_runtime_node_storage(0x11, task_buffer, 0x49, &window_node_list_storage);
    task->update_callback = update_cursor_callback;
    register_node(task, &draw_linked_sprite_nodes);
    state = NODE_BODY(task);
    render_data = task->sprite;
    state->script = source;
    state->enabled = 1;
    state->cursor_offset = state_value;
    runtime_initialize_state_value(record, *source);
    state->model = record;
    record->unk_60 = 6;
    state->model->unk_10 = 0x10C;
    variant_table = (s16 *)&cursor_variant_values;
    state->model->unk_14 =
        variant_table[((S_80036B10_8 *)(((S_80036B10_7 *)(((Rec_func_80036210_arg0 *)source)->unk_74.as_pm))->unk_80))->unk_02];
    state->unk_04 = 0;
    state->unk_08 = 0;
    prepend_embedded_object_node(setup_arg, state);
    render_data->color.word = 0x808080;
    select_record_entry_and_value(render_data, &cursor_sprite_source, 0);
}
