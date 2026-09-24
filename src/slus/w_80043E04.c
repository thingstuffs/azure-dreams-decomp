#include "slus/slot_transition.h"

/* Updates the frame, then allocates a slot and installs func_80043E60 if signaled, otherwise calls func_8003D92C. */
void func_80043E04(void) {
    func_80043EB8();
    if (D_80082E6E[0] != 0) {
        D_80081500 = func_8003F794(6, 8);
        func_80040A88((int) func_80043E60);
    } else {
        func_8003D92C();
    }
}
