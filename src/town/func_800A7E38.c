#include "common.h"

extern s32 D_800834B8;
extern void townInitializeEffectRecordHandlers(void *record_data, s32 unused_1, s32 unused_2);

/* Update the target using two values from the preceding state block. */
void townUpdateTargetFromPreviousState(void) {
    s32 *target = &D_800834B8;
    s32 *source_state = target - 8;


    townInitializeEffectRecordHandlers(target, source_state[2], source_state[3]);
}
