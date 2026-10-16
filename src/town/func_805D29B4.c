#include "common.h"

extern s32 townCheckInputsAfterThresholdTwo(s32);
extern s32 D_8001967C;
extern s32 D_800196F4[];

/* Dispatch the current state entry when the event code is 8. */
s32 func_800169B4(s32 unused_arg_0, s32 unused_arg_1, s32 event_code) {
    s32 result = 0;

    if (event_code == 8) {
        result = townCheckInputsAfterThresholdTwo(D_800196F4[D_8001967C]);
    }
    return result;
}
