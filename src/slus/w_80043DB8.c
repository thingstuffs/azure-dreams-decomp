#include "slus/slot_transition.h"

/* Runs the per-tick update and installs func_80043E04 when the current slot is free. */
void func_80043DB8(void) {
    func_80043EB8();
    if (D_80083120[D_80081500].field0 == 0) {
        func_80040A88((int) func_80043E04);
    }
}
