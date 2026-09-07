#include "common.h"

extern s32 func_800188E4();
extern s16 D_80019088[28];

void func_800168E0(void) {
    s16 *p;
    s32 i;

    i = 0;
    p = D_80019088;
    do {
        s32 value = *p;

        p += 4;
        i += 1;
        func_800188E4(value);
    } while (i < 7);

    func_800188E4(0x60E);
    func_800188E4(0x606);
    func_800188E4(0x611);
}
