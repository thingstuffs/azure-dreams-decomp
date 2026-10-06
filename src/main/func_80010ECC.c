#include "common.h"
#include "m2c_compat.h"
typedef struct S_800491F4 S_800491F4;

S_800491F4 *func_800491F4(S_800491F4 **, u8 *, s32);  /* extern */
extern u8 D_80027FC4;

/* Forwards the value to func_800491F4 with D_80027FC4 and 10. */
void func_80023ECC(S_800491F4 **value) {
    func_800491F4(value, &D_80027FC4, 0xa);
}
