#include "common.h"

typedef struct {
    u8 *ptr;
    u8 pad[8];
} D_800E3D7C_t;

extern D_800E3D7C_t D_800E3D7C;

/* Finds the first matching value in the four slots at offset 0xE4, or returns -1. */
s32 func_800A1C14(s32 target_value) {
    s32 slot;
    s32 *slot_ptr;
    s32 slot_value;
    s16 match_index;

    slot = 0;
    slot_ptr = (s32 *)D_800E3D7C.ptr;
    do {
        slot_value = slot_ptr[0x39];
        if (slot_value != target_value) {
            slot++;
            slot_ptr++;
            continue;
        }
        match_index = (s16)slot;
        return match_index;
    } while (slot < 4);
    return -1;
}
