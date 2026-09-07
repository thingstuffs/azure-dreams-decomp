#include "common.h"

extern void *D_80026690;
void func_8002640C(void);

void func_800266B0(s32 *arg0) {
    s32 temp = *arg0 << 10;

    *(s16 *) (*(s32 *) ((u8 *) arg0 + 0x64) + 6) = temp;
    *arg0 += 1;
    if (*arg0 >= 5) {
        *arg0 = 0;
        *(void **) ((u8 *) arg0 - 0x10) = &D_80026690;
    }
    func_8002640C();
}
