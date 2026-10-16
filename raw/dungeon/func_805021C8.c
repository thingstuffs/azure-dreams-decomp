#include "common.h"
#include "m2c_compat.h"

s32 func_80033BC0(M2C_UNK);                         /* extern */
M2C_UNK func_8009A21C(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
s32 func_800A6928(M2C_UNK, M2C_UNK);                /* extern */
extern s16 D_8008146C;
extern M2C_UNK D_800E3CD8;

s32 func_800199C8(s32 arg0) {
    void *temp_v0;

    if (*(s32 *)0x80012090 == 0) {
        if (D_8008146C == 2) {
            if ((func_80033BC0(0xA2) != 0) && ((func_800A6928(0xC, 8) << 0x10) != 0)) {
                temp_v0 = ((s32) (arg0 << 0x10) >> 0xD) + &D_800E3CD8;
                M2C_FIELD(temp_v0, s16 *, 0) = 4;
                M2C_FIELD(temp_v0, s16 *, 2) = 8;
                M2C_FIELD(temp_v0, s16 *, 4) = 8;
                M2C_FIELD(temp_v0, s16 *, 6) = 0;
                func_8009A21C(8, 8, 0x20);
                return 1;
            }
            goto block_5;
        }
        /* Duplicate return node #6. Try simplifying control flow for better match */
        return 0;
    }
block_5:
    return 0;
}
