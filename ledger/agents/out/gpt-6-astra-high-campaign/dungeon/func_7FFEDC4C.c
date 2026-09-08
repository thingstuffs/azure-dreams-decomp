#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

extern u8 D_80080EA8[];
extern u8 D_800CF828[];
extern s32 D_800CF838[];

/* Return the first slot whose table entry points to D_80080EA8, or -1. */
s32 func_8008B3AC(void) {
    s32 slot_index = 0;
    u8 *entry_indices = D_800CF828;
    s32 *entry_table = D_800CF838;
    u8 *target_entry = D_80080EA8;

    do {
        if (entry_table[*(u8 *)((s32)slot_index + (s32)entry_indices)] == (s32)target_entry)
            return slot_index;
        slot_index++;
    } while (slot_index < 15);
    return -1;
}
