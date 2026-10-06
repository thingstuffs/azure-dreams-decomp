#include "common.h"
#include "m2c_compat.h"
typedef struct S_800491F4 S_800491F4;

S_800491F4 *func_800491F4(S_800491F4 **, u8 *, s32);  /* extern */
extern u8 D_80029500;

/* Forwards the value to func_800491F4 with D_80029500 and constant 4. */
void func_800267B0(S_800491F4 **value) {
    func_800491F4(value, &D_80029500, 4);
}
