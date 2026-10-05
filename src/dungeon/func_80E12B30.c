#include "common.h"

extern s32 func_800990FC(void);
extern s32 func_80099194(u8 *src, u8 *dst);
extern s32 func_80099290(s8 *byte_ptr);
extern s32 func_80099734(void *record, u8 *out);
extern void func_800A5720(s8 *text);

extern u8 D_800E1F7B[];
extern u8 D_800E1F93[];
extern u8 D_8017088C[];

/* Processes the input, then dispatches or finalizes the result according to the mode. */
void func_80E12B30(s32 dispatch_mode, void *input) {
    s32 result;

    result = func_800990FC();
    if (dispatch_mode << 16) {
        func_80099290(func_80099194(D_800E1F7B, func_80099734(input, result)));
    } else {
        func_80099290(func_80099194(D_8017088C,
            func_80099734(input, func_80099194(D_800E1F93, result))));
    }
    func_800A5720(result);
}
