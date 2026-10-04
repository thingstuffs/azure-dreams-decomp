#include "common.h"
#include "m2c_compat.h"

void func_800214A4();                            /* extern */
extern s32 D_800287C8;

/* Clears D_800287C8 and runs func_800214A4. */
void func_80020A0C(void) {
    D_800287C8 = 0;
    func_800214A4();
}
