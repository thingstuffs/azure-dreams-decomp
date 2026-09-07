#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_800193E0();
extern M2C_UNK func_80019458();
extern M2C_UNK D_80016000;
extern M2C_UNK D_80019890;

void func_805D3588(void) {
    func_800193E0(0x3EB);
    func_80019458(0x631);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x84)(0);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x20), M2C_UNK (**)(M2C_UNK *), 0x218)(&D_80019890);
}
