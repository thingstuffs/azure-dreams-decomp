#include "slus/slot_transition.h"

/* Updates controller and dispatch state, then allocates a slot and schedules func_80043DB8 if callbacks do not signal completion. */
void func_80043D04(void)
{
    unsigned int source_value;
    struct SlotTransitionState *state;

    source_value = D_8008148C.field0;
    D_80081480.field0 = source_value;
    func_8003E2D8();

    state = &D_80082E60;
    func_80040FDC(state->field_B);
    func_80041038(state->field_B);
    func_800411FC(state->field_B);
    if (func_80040F2C(state->field_B)) {
        func_80040B88();
    } else {
        D_80081500 = func_8003F794(5, 8);
        D_80082E60.field_0 &= ~1;
        func_80040A88((s32)func_80043DB8);
    }
}
