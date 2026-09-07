#include "common.h"

s32 func_804019B4();                                /* extern */
s32 func_80401A50();                             /* extern */

extern s32 D_80136140[];
extern s32 D_8009EB58[];
extern s32 D_804094EC[];

void func_8001B214(void) {
    s32 temp_s0;
    s32 temp_v0;

    temp_s0 = D_804094EC[0] != 0;
    temp_v0 = func_804019B4();
    D_80136140[temp_s0] = temp_v0;
    D_8009EB58[temp_s0] = func_80401A50(temp_v0);
}
