#include "common.h"

extern void func_800196A4(s32, s32);
extern u8 *D_8001E950;

s32 func_804683DC(s32 arg0, s32 arg1) {
    func_800196A4(arg0, arg1);
    *D_8001E950 += 1;
    return 0;
}
