#include "shared/pad_state.h"
#include "common.h"

extern void func_80400948(void);
extern s32 card_devkit_poll_stable_slot_state(void);
extern void submit_stored_and_queried_boot_values(void);
extern s32 func_804010E0(void);
extern void forward_target_value_initcardmessageobject(void *left, void *right);
extern void func_8003FA78(void *descriptor, s32 value, s32 item);
extern u8 D_80400848[];
extern u8 D_804081AC[];
extern s32 D_804090C8[];
extern s32 D_804090E0[];

/* Updates the object's state and callback and performs a one-time transition. */
void card_boot_update_object_state_and_callback(void *object_data)
{
    s32 *object;
    s32 state_index;
    s32 table_offset;
    s32 next_callback;

    object = object_data;
    if ((boot_pad_state.held != 0) && ((boot_pad_state.pressed & 0x40) != 0)) {
        func_80400948();
        object[14] = 0;
        object[-4] = (s32)(unsigned long)D_804081AC;
        return;
    }

    state_index = card_devkit_poll_stable_slot_state();
    table_offset = state_index * 4;
    func_8003FA78(D_80400848, object[3], D_804090C8[state_index]);
    submit_stored_and_queried_boot_values();
    if (state_index != 0) {
        object[14] = 0;
        object[12] = state_index;
        next_callback = D_804090E0[state_index];
        object[13] = state_index;
        object[-4] = next_callback;
        return;
    }
    if ((func_804010E0() == 3) && (object[14] == 0)) {
        forward_target_value_initcardmessageobject((u8 *)object - 0x20, (u8 *)object + 0x38);
        object[14] = 1;
    }
    (void)table_offset;
}
