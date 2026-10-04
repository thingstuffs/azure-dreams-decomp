#include "common.h"

extern void func_80401BF4(void *arg0, s32 arg1);
extern s32 func_80401C70(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern s32 func_80401D28(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 func_80401FEC(void *arg0);
extern void func_8007BF18(void *arg0);
extern u8 D_8009DDD8[];
extern u8 D_80400138[];

s32 func_80402154(s32 index, void *data_ptr) {
    u8 buffer[32];
    s32 result;

    func_80401BF4(buffer, index);
    result = func_80401C70(buffer, data_ptr, 0xC0, 0);
    if (result != 0) {
        result = func_80401FEC(data_ptr);
        if (result != 0) {
            result = func_80401D28(buffer, D_8009DDD8 + (index << 7), 1, 4,
                                   *(s32 *)(D_8009DDD8 + (index << 7)));
            goto done;
        }
        func_8007BF18(D_80400138);
    }
done:
    return result;
}
