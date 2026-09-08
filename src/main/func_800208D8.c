#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80051B50();       /* extern */
extern s32 D_80408D6C;

/* Passes the object's data at offset 0x7C to func_80051B50 with D_80408D6C. */
void func_800208D8(s32 object_addr) {
    func_80051B50(object_addr + 0x7C, &D_80408D6C, 1);
}
