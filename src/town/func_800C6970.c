#include "common.h"

extern s32 D_800C3960;
s16 townGetCachedOrCoordinateTransformValue(void *object, s32 lookup_mode);
void townApplyObjectSetupAndUpdate(void *object, s32 update_context, s32 setup_context);

// Initialize the object's state and delegate the remaining setup.
void townInitializeObjectAndUpdate(void *object, s32 update_context, s32 setup_context) {
    *(s8 *)((u8 *)object + 0x15) = 0;
    *(void **)((u8 *)object + 0x50) = &D_800C3960;
    *(s16 *)((u8 *)object + 0x72) = townGetCachedOrCoordinateTransformValue(object, update_context);
    townApplyObjectSetupAndUpdate(object, update_context, setup_context);
}
