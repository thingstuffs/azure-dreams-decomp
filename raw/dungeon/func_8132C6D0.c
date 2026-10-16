#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009A028(void *);                      /* extern */
M2C_UNK func_8009A3D0(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_800A32A4(void *);                      /* extern */
extern void *D_80174CD8;

void func_80173ED0(void) {
    M2C_UNK var_a2;
    void *temp_s0;
    void *temp_s1;

    if (D_80174CD8 != NULL) {
        temp_s1 = D_80174CD8 + 0x20;
        temp_s0 = M2C_FIELD(D_80174CD8, void **, 0xC);
        func_800A32A4(temp_s1);
        var_a2 = 0x3000;
        if (M2C_FIELD(temp_s1, s32 *, 0x1C) & 0x2000) {
            var_a2 = 0x300;
        }
        func_8009A3D0(M2C_FIELD(temp_s0, u8 *, 0x24), M2C_FIELD(temp_s0, u8 *, 0x25), var_a2);
        func_8009A028(temp_s1);
        M2C_FIELD(temp_s1, u16 *, -2) = (u16) (M2C_FIELD(temp_s1, u16 *, -2) | 0x8000);
        D_80174CD8 = NULL;
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
