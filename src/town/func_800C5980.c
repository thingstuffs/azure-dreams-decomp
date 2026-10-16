#include "common.h"

extern s32 func_800352FC(void *, s32, s32, s32);
extern s32 townCheckActiveTransformObject(void *other);
extern void townInitializeObjectAndUpdate(void *object, s32 setupParam1, s32 setupParam2);
extern void townInitializeObjectHandlers(void *object, s32 setupParam1, s32 setupParam2);
extern u8 D_80082A39[16];

/* Select the object setup path after a successful request. */
s32 townSelectObjectSetupPath(void *object, s32 request_data, s32 request_param, s32 check_param) {
    if (func_800352FC(object, request_data, request_param, check_param) == 0) {
        return 0;
    }

    if (townCheckActiveTransformObject(object) != 0 ||
        D_80082A39[0] == *(s32 *)((u8 *)object + 0x60)) {
        townInitializeObjectAndUpdate(object, request_data, request_param);
        return 1;
    }

    townInitializeObjectHandlers(object, request_data, request_param);
    return 1;
}
