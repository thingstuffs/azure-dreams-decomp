#include "common.h"
#include "m2c_compat.h"
typedef struct S_800491F4 S_800491F4;

S_800491F4 *func_800491F4(S_800491F4 **, u8 *, s32);  /* extern */
extern u8 D_80027F68;

/* Forwards the input with fixed data D_80027F68 and parameter 0x12. */
void func_800237C4(S_800491F4 **input) {
    func_800491F4(input, &D_80027F68, 0x12);
}
