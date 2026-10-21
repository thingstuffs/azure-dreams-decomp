#include "common.h"
#include "frontend/card.h"
#include "main/data.h"

extern s32 func_80047FD8(void *node);
extern void process_four_referenced_values(void *object);
extern s32 card_ui_dirty_flags[3];
extern s32 D_8008DAB4_2[3];

/* Processes the global state, optionally flags its linked object, and returns the state value. */
s32 update_global_dialog_state(s32 flag_linked_object) {
    void *linked_object;
    u8 *state_data = D_80409508 + 0x20;

    if (func_80047FD8(state_data - 0x20) != 0) {
        if (flag_linked_object != 0) {
            linked_object = *(void **)(state_data + 0x14);
            *(u16 *)((u8 *)linked_object + 0x1E) = (u16) (*(u16 *)((u8 *)linked_object + 0x1E) | 0x2000);
        }
        process_four_referenced_values(state_data);
        *(u16 *)(state_data - 2) = (u16) (*(u16 *)(state_data - 2) | 0x8000);
        D_8008DAB4_2[0] = card_ui_dirty_flags[0] | 0x8000;
    }
    return *(s32 *)state_data;
}
