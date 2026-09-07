#include "common.h"

extern u32 func_8001E670(s32 arg0);
extern s32 func_8001E82C(void);
extern void func_800196A4(void);

extern u8 *D_8001E950[];
extern u8 D_80018A30[];

u8 *func_80019418(void) {
    if (func_8001E670(20) == 0) {
        return D_80018A30;
    }
    if (func_8001E82C() != 0) {
        func_800196A4();
    }
    *D_8001E950[0] += 1;
    return (u8 *)0;
}
