#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *, s32);      /* extern */
M2C_UNK *func_8004A658(u8, u8);                     /* extern */
M2C_UNK func_800BC26C(void *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8006E240;
extern M2C_UNK D_80162978;

void func_80162D48(void *arg0, void *arg1, void *arg2) {
    M2C_UNK *var_v0;
    s32 temp_a2;
    void *temp_s1;
    void *temp_s3;
    void *temp_v0;
    void *temp_v1;

    if (M2C_FIELD(arg2, u8 *, 0x49) != 0) {
        temp_v0 = func_8003FC64(0x12);
        if (temp_v0 != NULL) {
            temp_v1 = M2C_FIELD(temp_v0, void **, 8);
            temp_s1 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_v1, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0);
            M2C_FIELD(temp_v1, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 4);
            temp_a2 = M2C_FIELD(arg0, s32 *, 8);
            M2C_FIELD(temp_v1, s32 *, 0x10) = 0;
            M2C_FIELD(temp_v1, s32 *, 0xC) = 0;
            M2C_FIELD(temp_v1, s32 *, 0x14) = 0xFFEE0000;
            M2C_FIELD(temp_v1, s32 *, 8) = temp_a2;
            func_8004491C(temp_v0, &D_80045340, temp_a2);
            M2C_FIELD(temp_s1, s32 *, 0xC) = 0x808080;
            temp_s3 = temp_v0 + 0x20;
            M2C_FIELD(temp_s1, s16 *, 0x1E) = 0xC90;
            M2C_FIELD(temp_s1, s16 *, 0x1C) = 0xC90;
            if (M2C_FIELD(arg2, u8 *, 0x49) == 0x12) {
                var_v0 = &D_8006E240;
            } else {
                var_v0 = func_8004A658(M2C_FIELD(arg2, u8 *, 0x49), M2C_FIELD(arg2, u8 *, 0x48));
            }
            M2C_FIELD(temp_s1, M2C_UNK **, 8) = var_v0;
            M2C_FIELD(temp_s3, s16 *, 0xA8) = (s16) M2C_FIELD(arg1, u8 *, 0x24);
            M2C_FIELD(temp_s3, s16 *, 0xAA) = (s16) M2C_FIELD(arg1, u8 *, 0x25);
            M2C_FIELD(temp_s3, M2C_UNK *, 0x48) = M2C_UNALIGNED32(M2C_FIELD(arg2, u8 *, 0x48));
            func_800BC26C(temp_v0, 0, 0, 0);
            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80162978;
        }
    }
}
