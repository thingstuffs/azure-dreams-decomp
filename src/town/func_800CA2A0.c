#include "common.h"

extern s32 func_800C30E0(s32, s32, s32, s32);
extern void func_800C7BF0(s32, s32, s32);
extern s32 D_80113220[];

/* Reset the object callback when the shared countdown expires after a zero check result. */
void func_800C7A00(s32 object, s32 motion, s32 init_data, s32 check_arg) {
    if (func_800C30E0(object, motion, init_data, check_arg) == 0) {
        if (--D_80113220[0] <= 0) {
            func_800C7BF0(object, motion, init_data);
        }
    }
}
