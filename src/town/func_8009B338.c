#include "common.h"
#include "m2c_compat.h"

void townInitializeObjectTransformAndHandler(void *, void *, s32);                            /* extern */
extern s8 D_80082668;

/* Clear D_80082668 and pass the state, context, and mode to townInitializeObjectTransformAndHandler. */
void townClearSharedFlagAndInitializeObject(void *state, void *context, s32 mode) {
    D_80082668 = 0;
    townInitializeObjectTransformAndHandler(state, context, mode);
}
