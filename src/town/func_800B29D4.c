#include "common.h"

extern s32 D_800AFD5C;

/* Initializes state values and links the shared data pointer. */
void initialize_item_menu_request_state(void *state, s32 base_value) {
    *(s32 *)((u8 *)state + 0x18) = base_value;
    base_value = base_value + 0x20;
    *(s32 *)((u8 *)state + 0x10) = 1;
    *(s32 *)((u8 *)state + 0x0) = base_value;
    *(s32 **)((u8 *)state - 0x10) = &D_800AFD5C;
}
