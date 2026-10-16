#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80019B70(void *);                      /* extern */
extern M2C_UNK D_80017B48;

void func_80019BFC(void) {
    func_80019B70((M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x20), s32 (**)(M2C_UNK), 0x2D4)(0) * 8) + &D_80017B48);
}
