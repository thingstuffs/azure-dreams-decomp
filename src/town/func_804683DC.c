#include "common.h"

extern void func_800196A4(void);
extern u8 *D_8001E950;

s32 func_804683DC(void) {
    func_800196A4();
    *D_8001E950 += 1;
    return 0;
}
