#include "common.h"
#include "m2c_compat.h"
typedef struct S_800491F4 S_800491F4;

S_800491F4 *func_800491F4(S_800491F4 **, u8 *, s32);  /* extern */
extern u8 D_80027FF8;

/* Calls func_800491F4 for the target with fixed data and a value of 0x15. */
void func_80024C48(S_800491F4 **target) {
    func_800491F4(target, &D_80027FF8, 0x15);
}
