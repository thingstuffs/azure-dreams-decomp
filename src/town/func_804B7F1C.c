#include "common.h"

extern void func_8001611C(s32, s32);
extern s32 func_8001894C(s32);
extern s32 func_80017D9C(s32, s32);

/* Initializes the request and processes it when flag 0x50F is set. */
s32 func_8001671C(s32 request_id, s32 request_arg) {
    s32 result;

    func_8001611C(request_id, request_arg);
    if (func_8001894C(0x50F) != 0) {
        result = func_80017D9C(request_id, request_arg);
    } else {
        result = 0;
    }
    return result;
}
