/* Relink of matched town/func_805D29B4; every changed retail word is a paired relocation. */
#define D_800196F4 D_80019700
#include "common.h"

extern s32 townCheckInputsAfterThresholdTwo(s32);
extern s32 D_8001967C;
extern s32 D_80019700[];

/* Dispatch the current state entry when the event code is 8. */
s32 townProcessEventIdsAndSucceed(s32 unused_arg_0, s32 unused_arg_1, s32 event_code) {
    s32 result = 0;

    if (event_code == 8) {
        result = townCheckInputsAfterThresholdTwo(D_80019700[D_8001967C]);
    }
    return result;
}
