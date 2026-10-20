#include "common.h"

extern void store_supplied_values(s32, s32);
extern s32 func_8001894C(s32);
extern s32 func_80017D9C(s32, s32);

/* Initializes the request and processes it when flag 0x50F is set. */
s32 initialize_request(s32 request_id, s32 request_arg) {
    s32 result;

    store_supplied_values(request_id, request_arg);
    if (func_8001894C(0x50F) != 0) {
        result = func_80017D9C(request_id, request_arg);
    } else {
        result = 0;
    }
    return result;
}
