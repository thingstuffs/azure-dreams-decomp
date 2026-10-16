#include "common.h"
#include "m2c_compat.h"

void *func_804083FC(s32 arg0, M2C_UNK arg1) {
    void *var_s0;

    var_s0 = (void *)0x8040C5C0;
    if ((s32 (*)(M2C_UNK))0x80047FD8(0x8040C5C0) == 0) {
        var_s0 = (void *(*)(M2C_UNK, M2C_UNK, M2C_UNK))0x8003C714(0, 0x8040C5C0, 0x19);
        if (var_s0 == NULL) {
            (M2C_UNK (*)(M2C_UNK, M2C_UNK, M2C_UNK))0x8007C040(0x8040086C, 0x80400894, 0x173);
            (M2C_UNK (*)(M2C_UNK))0x8007BEF0(1);
            goto block_3;
        }
    } else {
block_3:
        (M2C_UNK (*)(void *))0x804084DC(var_s0);
        *(void *)0x8040C5DE = (u16) (*(u16 *)0x8040C5DE & 0x7FFF);
        (M2C_UNK (*)(M2C_UNK, M2C_UNK))0x8007BFE0(0x8040C5E0, 0x44);
    }
    (M2C_UNK (*)(M2C_UNK, s32, M2C_UNK))0x80408394(0x8040C5E0, arg0, arg1);
    M2C_FIELD(var_s0, s32 *, 0x10) = 0x804083A0;
    return var_s0;
}
