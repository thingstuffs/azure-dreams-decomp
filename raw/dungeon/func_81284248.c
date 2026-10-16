#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80098E28(void *);                      /* extern */
M2C_UNK func_800991C0(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_800A1F74(void *);                      /* extern */
extern void *D_8016D710;

void func_8016CA48(void) {
    M2C_UNK var_a2;
    void *temp_s0;
    void *temp_s1;

    if (D_8016D710 != NULL) {
        temp_s1 = D_8016D710 + 0x20;
        temp_s0 = M2C_FIELD(D_8016D710, void **, 0xC);
        func_800A1F74(temp_s1);
        var_a2 = 0x3000;
        if (M2C_FIELD(temp_s1, s32 *, 0x1C) & 0x2000) {
            var_a2 = 0x300;
        }
        func_800991C0(M2C_FIELD(temp_s0, u8 *, 0x24), M2C_FIELD(temp_s0, u8 *, 0x25), var_a2);
        func_80098E28(temp_s1);
        M2C_FIELD(temp_s1, u16 *, -2) = (u16) (M2C_FIELD(temp_s1, u16 *, -2) | 0x8000);
        D_8016D710 = NULL;
        *(s32 *)0x800803D4 |= 0x8000;
    }
}
