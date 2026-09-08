#include "common.h"

extern s32 D_80702C14[];

/* Scale the stored value by eight and add the value at 0x807030B0. */
void func_80878A54(void) {
    D_80702C14[0] = (D_80702C14[0] * 8) + *(s32 *)0x807030B0;
}
