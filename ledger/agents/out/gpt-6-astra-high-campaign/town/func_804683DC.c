#include "common.h"

extern void func_800196A4(s32, s32);
extern u8 *D_8001E950;

/* Call func_800196A4, increment the byte at D_8001E950, and return zero. */
s32 func_804683DC(s32 first_value, s32 second_value) {
    func_800196A4(first_value, second_value);
    *D_8001E950 += 1;
    return 0;
}
