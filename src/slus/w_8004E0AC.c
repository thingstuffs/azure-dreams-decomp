#include "common.h"

extern int testResidentBitmapBit(int);
extern int clearResidentBitmapBit(int);

/* Processes the first passing slot check among 3, 4, and 5, returning 1, 2, or 3, or 0 if none pass. */
int func_8004E0AC(void) {
    int slot_result = 0;
    if (testResidentBitmapBit(3)) {
        clearResidentBitmapBit(3);
        slot_result = 1;
    } else {
        if (testResidentBitmapBit(4)) {
            clearResidentBitmapBit(4);
            slot_result = 2;
        } else {
            if (testResidentBitmapBit(5)) {
                clearResidentBitmapBit(5);
                slot_result = 3;
            }
        }
    }
    return slot_result;
}
