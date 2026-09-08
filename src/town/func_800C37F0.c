#include "common.h"

extern s8 D_80080A88;

/* set_no_change_seq: sets the flag that prevents sequence changes. */
void func_800C0F50(void) {
    D_80080A88 = 1;
}
