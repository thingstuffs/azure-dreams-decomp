#include "shared/object_node.h"
#include "common.h"


extern void *allocate_list_node(s32 flags, s32 list_head);
extern void set_message_mode(s32 value);
extern void runtime_call_selected_mode_handler(void);
extern void start_item_menu_object_processing(void *parameters);
extern s32 create_item_menu_child_object(void *init_value);
extern s32 func_800B0718(void);
extern s32 create_dual_buffer_object(void *setup_value, s32 x, s32 y);


typedef struct S_800AE324_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    void * unk_20;
    u8 pad_24[0x50];
    s32 unk_74;
} S_800AE324_0;   /* state in create_item_menu_object */

typedef struct S_800AE324_1 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_800AE324_1;   /* object in create_item_menu_object */

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
        object = func_8003FC64(0);
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
    start_item_menu_object_processing(state);
    return 0;
}
