#include "common.h"
#include "m2c_compat.h"
typedef struct S_800491F4 S_800491F4;

S_800491F4 *func_800491F4(S_800491F4 **, u8 *, s32);  /* extern */
extern u8 D_80027F60;

/* Forwards the input to func_800491F4 with &D_80027F60 and 7. */
void func_80022B20(S_800491F4 **input) {
    func_800491F4(input, &D_80027F60, 7);
}
