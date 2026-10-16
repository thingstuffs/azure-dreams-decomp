#include "common.h"
#include "m2c_compat.h"

void func_804054E8(void *arg0) {
    if (M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x7C) << 7) + 0x800A0000), s32 *, -0x2228) != 0) {
        (M2C_UNK (*)())0x80404EA0();
        return;
    }
    (M2C_UNK (*)())0x804053A0();
}
