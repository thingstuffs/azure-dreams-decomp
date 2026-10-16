#include "common.h"
#include "m2c_compat.h"

void func_804084DC(void *arg0) {
    if (arg0 == NULL) {
        (M2C_UNK (*)(M2C_UNK, M2C_UNK, M2C_UNK))0x8007C040(0x8040086C, 0x80400894, 0x183);
        (M2C_UNK (*)(M2C_UNK))0x8007BEF0(1);
    }
    (M2C_UNK (*)(s32))0x80404DBC(M2C_FIELD(arg0, s32 *, 0x40));
    (M2C_UNK (*)(s32))0x804077D4(M2C_FIELD(arg0, s32 *, 0x44));
    M2C_FIELD(arg0, u16 *, 0x1E) = (u16) (M2C_FIELD(arg0, u16 *, 0x1E) | 0x8000);
    *(void *)0x8008DAB4 = (s32) (*(s32 *)0x8008DAB4 | 0x8000);
}
