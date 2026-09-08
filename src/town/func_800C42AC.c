#include "common.h"

typedef s32 T;

extern T func_80041284();
extern T func_8008B408();
extern T D_80080E28;
extern T D_800D1D54;

/* Process both global objects with func_80041284, then call func_8008B408 with 3. */
void func_800C1A0C(void) {
    func_80041284(&D_80080E28);
    func_80041284(&D_800D1D54);
    func_8008B408(3);
}
