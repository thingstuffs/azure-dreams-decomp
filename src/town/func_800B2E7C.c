#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"

void bzero(void *, s32);
s32 set_item_menu_flag_and_return_one();                     /* extern */
s32 create_item_menu_child_at_position(); /* extern */
void finish_item_menu_child_and_release_list();                      /* extern */
extern M2C_UNK D_800B0490;

typedef struct S_800B05DC_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
    s32 unk_18;
} S_800B05DC_0;

typedef struct S_800B05DC_1 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_800B05DC_1;

/* Create a display controller and its child display object. */
void *create_item_menu_display_controller(s32 owner, s32 display_config, s32 x, s32 y, s32 init_config) {
    s32 init_result;
    s32 display_object;
    S_800B05DC_0 *state;
    void *object;

    object = func_8003FC64(0);
    if (object != NULL) {
        state = object + 0x20;
        state->unk_08 = owner;
        state->unk_0C = init_config;
        state->unk_14 = display_config;
        bzero(state, 4);
        init_result = set_item_menu_flag_and_return_one(state, init_config);
        state->unk_18 = init_result;
        if (init_result != 0) {
            ((S_800B05DC_1 *)object)->unk_10 = &D_800B0490;
            display_object = create_item_menu_child_at_position(object, x, y, display_config, state->unk_18, state);
            state->unk_04 = display_object;
            if (display_object == 0) {
                finish_item_menu_child_and_release_list(state);
                object = NULL;
            }
        }
    }
    return object;
}
