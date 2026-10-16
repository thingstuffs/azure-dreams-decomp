#include "common.h"

extern s32 townSelectObjectSetupPath(s32, s32, s32, s32);
extern void townInitializeMotherEventWithTimer16(s32, s32, s32);
extern s32 D_80113220[];

/* Reset the object callback when the shared countdown expires after a zero check result. */
void townResetMotherEventCallbackOnExpiry(s32 object, s32 motion, s32 init_data, s32 check_arg) {
    if (townSelectObjectSetupPath(object, motion, init_data, check_arg) == 0) {
        if (--D_80113220[0] <= 0) {
            townInitializeMotherEventWithTimer16(object, motion, init_data);
        }
    }
}
