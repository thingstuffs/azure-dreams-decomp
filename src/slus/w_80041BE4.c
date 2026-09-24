#include "slus/slot_transition.h"

/* Runs the state update, then allocates a slot and advances the callback if enabled, or invokes the fallback. */
void func_80041BE4(void)
{
    func_80041CBC();
    if (D_80082E6E[0] != 0) {
        if (D_80083120[D_800814E8].field0 == 0) {
            D_800814E8 = func_8003F794(6, 8);
        }
        func_80040A88((int) func_80041C64);
    } else {
        func_8003D92C();
    }
}
