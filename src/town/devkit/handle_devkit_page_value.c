#include "town/scene.h"

typedef struct {
    u8 pad[0x34];
    u32 flags;
} State;

extern State *devkit_state_slots[3];

extern s32 func_80700C9C(s32 carry_value);
extern void shift_index_and_add_offset(s32 carry_value);
extern void pass_indexed_table(s32 carry_value);


/* Devkit page 2: pass the value through when idle, else set the redraw flag and rescan. */
s32 handle_devkit_page_2_value(s32 carry_value) {
    s32 result;

    if (func_80700C9C(2) == 0) {
        pass_indexed_table(2);
        result = carry_value;
    } else {
        shift_index_and_add_offset(2);
        devkit_state_slots[0]->flags |= 0x10;
        result = call_indexed_callback_failed_test();
    }
    return result;
}
