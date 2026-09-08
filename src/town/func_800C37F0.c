#include "common.h"

extern s8 D_80080A88;

/* jyotyu_set_reserve_pool: set the reserve pool flag. */
void func_800C0F50(void) {
    D_80080A88 = 1;
}
