#include "common.h"

extern void func_80401BF4(void *buffer, s32 index);
extern s32 func_80401C70(void *buffer, void *data_ptr, s32 value0, s32 value1);
extern s32 func_80401D28(void *buffer, void *record_ptr, s32 value0, s32 value1, s32 record_value);
extern s32 func_80401FEC(void *data_ptr);
extern void func_8007BF18(void *data_ptr);
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
