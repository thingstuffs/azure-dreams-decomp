#include "common.h"

extern void func_800CCF74(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

/* Forward three inputs with fixed parameters 16, -4, and -8. */
void func_800CD0FC(s32 input_first, s32 input_second, s32 input_third) {
    func_800CCF74(input_first, input_second, input_third, 0x10, -4, -8);
}
