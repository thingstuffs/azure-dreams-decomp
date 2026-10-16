#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

s32 lookupItemCategoryMappedValue();                /* extern */
void townConfigureTheSetModeN3();     /* extern */
void townInitializeOptionalObjectState(); /* extern */
extern s32 D_800D0678[];


/* Initializes the state value and sets up the context using D_800D0678. */
void townInitializeReactionContext(s32 contextId, s32 contextData, Rec_D_80082E80 *state) {
    state->unk_08 = lookupItemCategoryMappedValue(4, 1);
    townConfigureTheSetModeN3(contextId, contextData, &D_800D0678);
    townInitializeOptionalObjectState(contextId, contextData, state, 0);
}
