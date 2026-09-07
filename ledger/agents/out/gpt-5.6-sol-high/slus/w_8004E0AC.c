#include "common.h"

/* Selects the first available slot among 3, 4, and 5, activates it, and returns its one-based choice index. */
extern int func_80033B2C(int);
extern int func_80033AE8(int);

int func_8004E0AC(void) {
    int selectedSlotIndex = 0;

    if (func_80033B2C(3)) {
        func_80033AE8(3);
        selectedSlotIndex = 1;
        goto out;
    }
    if (func_80033B2C(4)) {
        func_80033AE8(4);
        selectedSlotIndex = 2;
        goto out;
    }
    if (func_80033B2C(5)) {
        func_80033AE8(5);
        selectedSlotIndex = 3;
    }
out:
    return selectedSlotIndex;
}
