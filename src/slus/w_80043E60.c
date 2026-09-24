#include "slus/slot_transition.h"

/* Updates the frame, then sets bit 0 and calls func_80040B88 if the current slot is unflagged. */
void func_80043E60(void) {
    func_80043EB8();
    if (D_80083120[D_80081500].field0 == 0) {
        D_80082E60.field_0 |= 1;
        func_80040B88();
    }
}
