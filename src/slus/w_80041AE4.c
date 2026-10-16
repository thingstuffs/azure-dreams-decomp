#include "slus/slot_transition.h"

/* Refreshes controller input and runs the current entry's handlers, starting a state transition if none signals completion. */
void func_80041AE4(void)
{
    unsigned int copied_value;
    struct SlotTransitionState *state;

    copied_value = D_8008148C;
    D_80081480 = copied_value;
    updateControllerButtonsAndTriggers();

    state = &D_80082E60;
    uploadDispatchEntryImages(state->field_B);
    uploadDispatchEntryVramRows(state->field_B);
    loadDispatchEntryFiles(state->field_B);
    if (runDispatchEntryCallbacks(state->field_B)) {
        sceneSavePreviousModeAndResetCallbacks();
    } else {
        D_80082E60.field_0 &= ~1;
        D_800814E8 = reserveRuntimeSlot(5, 8);
        setScenePhaseCallback((s32)func_80041B98);
    }
}
