#include "common.h"

typedef s32 T;

extern T file_load_com();
extern T reserve_twch_load();
extern T D_80080E28;
extern T D_800D1D54;

/* Process both global objects with file_load_com, then call reserve_twch_load with 3. */
void func_800C1A0C(void) {
    file_load_com(&D_80080E28);
    file_load_com(&D_800D1D54);
    reserve_twch_load(3);
}
