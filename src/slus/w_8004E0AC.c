#include "common.h"

extern int test_resident_bitmap_bit(int);
extern int clear_resident_bitmap_bit(int);

/* Processes the first passing slot check among 3, 4, and 5, returning 1, 2, or 3, or 0 if none pass. */
int func_8004E0AC(void) {
    int slot_result = 0;
    if (test_resident_bitmap_bit(3)) {
        clear_resident_bitmap_bit(3);
        slot_result = 1;
    } else {
        if (test_resident_bitmap_bit(4)) {
            clear_resident_bitmap_bit(4);
            slot_result = 2;
        } else {
            if (test_resident_bitmap_bit(5)) {
                clear_resident_bitmap_bit(5);
                slot_result = 3;
            }
        }
    }
    return slot_result;
}
