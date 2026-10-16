#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80700D24();                            /* extern */
extern M2C_UNK D_80700774;
extern M2C_UNK D_807007D4;
extern M2C_UNK D_807007FC;
extern void *D_80700E40;
extern s32 D_80700E48;
extern void *D_80700E4C;

void func_80700D48(void) {
    M2C_UNK *temp_a0;
    u8 *var_a0;

    if (*(s32 *)0x807007B0 != 0) {
        M2C_FIELD(D_80700E4C, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, M2C_UNK), 0x68)(&D_807007D4, &D_807007FC, 0x4B);
        M2C_FIELD(D_80700E4C, M2C_UNK (**)(M2C_UNK), 0x74)(1);
    }
    *(void *)0x807007B0 = 1;
    func_80700D24();
    M2C_FIELD(D_80700E40, M2C_UNK **, 0x10) = &D_80700774;
    temp_a0 = M2C_FIELD(D_80700E40, M2C_UNK **, 0x10);
    if (M2C_FIELD(temp_a0, u8 *, 1) != 0x80) {
        var_a0 = temp_a0 + 1;
        do {
            M2C_FIELD(var_a0, s32 *, 0xB) = (s32) *((M2C_FIELD(var_a0, s32 *, 0xB) * 4) + D_80700E48);
            var_a0 += 0x14;
        } while (*var_a0 != 0x80);
    }
}
