#include "common.h"
typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_800C2E84();
extern M2C_UNK D_800C8788;
extern M2C_UNK D_800D627C;

void func_800C8808(void *arg0, void *arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D627C);
    M2C_FIELD(arg0, M2C_UNK **, 0x54) = &D_800C8788;
    M2C_FIELD(arg1, s32 *, 0x14) = 0xFFF60000;
}
