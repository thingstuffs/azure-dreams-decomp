/* Item menu object lifecycle (G00600). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B0CB4. */
#include "town/shop/item_menu_object_lifecycle_g00600.h"

/* Create an object and initialize its state, releasing the state if setup fails. */
s32 create_item_menu_object(s32 selector) {
    void *object;
    S_800AE324_0 *state;
    void *initializer;
    s32 count;
    s32 result;

    if (selector != 0) {
        object = allocate_list_node(0, selector);
    } else {
        object = allocate_flagged_object_node(0);
    }

    if (object != 0) {
        initializer = (void *)0x8001029C;
        state = (u8 *)object + 0x20;
        state->unk_20 = initializer;
        state->unk_1C = func_800B0718();
        state->unk_74 = selector;
        count = state->unk_1C;
        if (count != 0) {
            state->unk_14 = (count - 1) / 10;
        }
        set_message_mode(1);
        runtime_call_selected_mode_handler();
        result = create_item_menu_child_object(object);
        ((S_800AE324_1 *)object)->unk_20 = result;
        if (result != 0) {
            result = create_dual_buffer_object(object, 0x48, -0x5C);
            state->unk_08 = result;
        }
    }
    if (object == 0 || result != 0) {
        return (s32)object;
    }
    start_item_menu_object_processing((ItemMenuParameters *)state);
    return 0;
}

/* Marks the menu object for removal, schedules child cleanup, and resumes message and selection handling. */
void start_item_menu_object_processing(ItemMenuParameters *parameters) {
    s32 firstParameter = parameters->field0;
    ((u16 *)parameters)[-1] |= 0x8000;
    object_flag_block.flags |= 0x8000;
    reset_item_menu_object_state(firstParameter);
    schedule_item_menu_child_release(parameters->field4);
    set_object_data_pointer_2(parameters->field8);
    enqueue_script_message_command();
    handle_selection_and_create_object();
}
