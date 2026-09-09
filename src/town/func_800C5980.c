#include "common.h"

extern s32 func_800352FC(void *, s32, s32, s32);
extern s32 func_800C2A60(void *arg0);
extern void func_800C40D0(void *arg0, s32 arg1, s32 arg2);
extern void func_800C4134(void *arg0, s32 arg1, s32 arg2);
extern u8 D_80082A39[16];

/* Select the object setup path after a successful request. */
s32 func_800C30E0(void *object, s32 request_data, s32 request_param, s32 check_param) {
    if (func_800352FC(object, request_data, request_param, check_param) == 0) {
        return 0;
    }

    if (func_800C2A60(object) != 0 ||
        D_80082A39[0] == *(s32 *)((u8 *)object + 0x60)) {
        func_800C40D0(object, request_data, request_param);
        return 1;
    }

    func_800C4134(object, request_data, request_param);
    return 1;
}
