#include "common.h"

extern void clear_resident_bitmap_bit(s32 flag_id);
extern s16 D_800D253C[66];
extern s16 D_800D25C0[66];

/* Processes paired array entries until the first array's zero terminator. */
void process_paired_arrays_until_terminator(void) {
    if (D_800D253C[0] != 0) {
        s32 entryIndex = 0;

        do {
            clear_resident_bitmap_bit(D_800D253C[entryIndex]);
            clear_resident_bitmap_bit(D_800D25C0[entryIndex]);
            entryIndex++;
        } while (D_800D253C[entryIndex] != 0);
    }
}
