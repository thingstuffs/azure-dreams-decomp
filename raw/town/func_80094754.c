#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80091F48();
extern M2C_UNK func_80093D48();
extern M2C_UNK func_80095C80();

void func_80091EB4(void *arg0, void *arg1, M2C_UNK arg2) {
    s32 temp_v1;
    u16 temp_v0;

    func_80095C80(arg1);
    temp_v0 = M2C_FIELD(arg0, u16 *, 0xA) - 1;
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x34) << 0x10;
    M2C_FIELD(arg0, u16 *, 0xA) = temp_v0;
    if ((s16) temp_v0 <= 0) {
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg0, s16 *, 0x34) << 0x10);
        func_80093D48(arg0, arg1, arg2);
        func_80091F48();
        return;
    }
    M2C_FIELD(arg1, s32 *, 0x14) =
        (s32) ((s32) (temp_v1 - M2C_FIELD(arg1, s32 *, 8)) /
               (s16) temp_v0);
}
