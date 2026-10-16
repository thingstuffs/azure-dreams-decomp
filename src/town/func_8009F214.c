#include "common.h"

extern void townConfigureTheSetModeN3(void *record, s32 setup_value, void *setup_param);
extern void townInitializeOptionalObjectState(void *object, s32 context, void *state, void *init_value);

extern s32 D_800CFD00[];
extern s32 D_800F8CEC[];

// Assigns the state's data table and invokes the shared handlers.
void townInitializeObjectStateFromSelector(void *context, s32 selector, void *state) {
    *(void **)((u8 *)state + 8) = D_800F8CEC;
    townConfigureTheSetModeN3(context, selector, D_800CFD00);
    townInitializeOptionalObjectState(context, selector, state, 0);
}
