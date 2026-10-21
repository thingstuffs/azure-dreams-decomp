#include "script_symbols.h"
#include "common.h"
#include "engine/object.h"
#include "engine/runtime.h"

/* Processes the first passing slot check among 3, 4, and 5, returning 1, 2, or 3, or 0 if none pass. */
int poll_resident_slot(void) {
    int slot_result = 0;
    if (test_resident_bitmap_bit(sn_win_sw1)) {
        clear_resident_bitmap_bit(sn_win_sw1);
        slot_result = 1;
    } else {
        if (test_resident_bitmap_bit(sn_win_sw2)) {
            clear_resident_bitmap_bit(sn_win_sw2);
            slot_result = 2;
        } else {
            if (test_resident_bitmap_bit(sn_win_sw3)) {
                clear_resident_bitmap_bit(sn_win_sw3);
                slot_result = 3;
            }
        }
    }
    return slot_result;
}
