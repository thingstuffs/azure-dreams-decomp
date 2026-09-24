#include "slus/slot_transition.h"

/* Refreshes controller input and runs the current entry's handlers, starting a state transition if none signals completion. */
void func_80041AE4(void)
{
    unsigned int copied_value;
    struct SlotTransitionState *state;

    copied_value = D_8008148C.field0;
    D_80081480.field0 = copied_value;
    func_8003E2D8();

    state = &D_80082E60;
    func_80040FDC(state->field_B);
    func_80041038(state->field_B);
    func_800411FC(state->field_B);
    if (func_80040F2C(state->field_B)) {
        func_80040B88();
    } else {
        D_80082E60.field_0 &= ~1;
        D_800814E8 = func_8003F794(5, 8);
        func_80040A88((s32)func_80041B98);
    }
}
