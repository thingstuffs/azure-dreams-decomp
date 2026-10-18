#include "common.h"
#include "shared/object_index_slots.h"

typedef s32 M2C_UNK;

extern void call_the_handler_selects_nonzero_entry();
extern s16 clamp_transform_coordinate_deltas();
extern M2C_UNK D_80099874;

/* Clears the object slot flag, sets its handler, and updates its position-dependent value. */
void set_player_handler_and_position_value(void *object, M2C_UNK value_arg, s32 handler_param) {
    M2C_UNK saved_value_arg;

    call_the_handler_selects_nonzero_entry(*(s32 **)(*(void **)((u8 *)object + 0x44) + 0x14), object, handler_param);
    saved_value_arg = value_arg;
    *((s8 *)(D_80082660) + (*(s32 *)((u8 *)object + 0x40) * 8)) = 0;
    *(void **)((u8 *)object + 4) = &D_80099874;
    *(s16 *)((u8 *)object + 0x10) = clamp_transform_coordinate_deltas(
        *(s16 *)((u8 *)object + 0x36),
        *(s16 *)((u8 *)object + 0x38),
        saved_value_arg);
}
