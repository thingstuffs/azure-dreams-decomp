#include "slus/slot_transition.h"

/* Updates controller and dispatch state, then allocates a slot and schedules func_80043DB8 if callbacks do not signal completion. */
void func_80043D04(void)
{
    unsigned int source_value;
    struct SlotTransitionState *state;

    source_value = D_8008148C;
    D_80081480 = source_value;
    updateControllerButtonsAndTriggers();

    state = &D_80082E60;
    uploadDispatchEntryImages(state->field_B);
    uploadDispatchEntryVramRows(state->field_B);
    loadDispatchEntryFiles(state->field_B);
    if (runDispatchEntryCallbacks(state->field_B)) {
        sceneSavePreviousModeAndResetCallbacks();
    } else {
        D_80081500 = reserveRuntimeSlot(5, 8);
        D_80082E60.field_0 &= ~1;
        setScenePhaseCallback((s32)func_80043DB8);
    }
}
