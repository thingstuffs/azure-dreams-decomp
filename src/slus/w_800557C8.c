#include "common.h"

/* FIFO pop from u16 queue at D_80084778: [0]=count (clamped to 0x20),
 * [1..]=entries. Shifts remaining entries left and decrements count. */
extern u16 D_80084778[0x21];

/* Pops the oldest queue entry and shifts the rest left, returning zero if empty. */
u16 func_800557C8(void)
{
    s32 byte_offset;
    s32 shift_index;
    s32 count_or_index;
    s32 first_slot;
    u16 entry;

    if ((u16)D_80084778[0] >= 0x21U) {
        D_80084778[0] = 0x20U;
    }

    count_or_index = D_80084778[0];
    entry = 0;
    if (count_or_index != 0) {
        entry = D_80084778[1];
        first_slot = 1;
        if ((u32)first_slot < (u32)count_or_index) {
            shift_index = first_slot;
            do {
                count_or_index = shift_index & 0xFFFF;
                shift_index += 1;
                byte_offset = count_or_index * 2;
                *(u16 *)((u8 *)D_80084778 + byte_offset) =
                    *(u16 *)((u8 *)D_80084778 + byte_offset + 2);
            } while ((u32)(shift_index & 0xFFFF) < (u16)D_80084778[0]);
        }
        D_80084778[0] = (u16)(D_80084778[0] - 1);
    }

    return entry;
}
