#include "common.h"

void func_800B1960(s32, s32, s32, s32, s32); /* extern */
void func_800B19F8(s32); /* extern */
void func_800B1B04(void); /* extern */

void func_800B1B10(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_800B1B04();
    func_800B1960(arg0 + 0x38, arg0 + 0x10, arg0 + 0x20, arg2, arg3);
    func_800B19F8(arg0);
}
