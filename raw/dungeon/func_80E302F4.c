#include "common.h"
#include "m2c_compat.h"

s32 func_8003DE58(s32, void *, u16 *, M2C_UNK);     /* extern */
void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80047784(void *, M2C_UNK, M2C_UNK);    /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DDC40;
extern M2C_UNK D_80157978;

void *func_80157AF4(void *arg0, void *arg1, void *arg2) {
    u16 sp10;
    u16 sp12;
    u16 sp14;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    void *temp_a0;
    void *temp_s0;
    void *temp_s2;
    void *temp_s3;
    void *temp_v0;

    temp_s3 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), void **, -0x18);
    temp_v0 = func_8003FC64(0x312);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80157978;
        func_8004491C(temp_v0, &D_80045340);
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0, s32 *, 0x28) = (s32) M2C_FIELD(arg2, s32 *, 0x28);
        M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x800;
        M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x800;
        M2C_FIELD(temp_a0, s32 *, 0xC) = 0x808080;
        M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC);
        M2C_FIELD(temp_a0, u16 *, 0x10) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x10) | 0x20);
        func_80047784(temp_a0, 0x47, 0);
        temp_s2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v0, s32 *, 0x24) = (s32) M2C_FIELD(arg1, s32 *, 0);
        M2C_FIELD(temp_v0, s32 *, 0x28) = (s32) M2C_FIELD(arg1, s32 *, 4);
        M2C_FIELD(temp_v0, s32 *, 0x2C) = (s32) M2C_FIELD(arg1, s32 *, 8);
        M2C_FIELD(temp_v0, s32 *, 0x30) = (s32) M2C_FIELD(arg1, s32 *, 0xC);
        M2C_FIELD(temp_v0, s32 *, 0x34) = (s32) M2C_FIELD(arg1, s32 *, 0x10);
        M2C_FIELD(temp_v0, s32 *, 0x38) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
        temp_s0 = temp_v0 + 0x20;
        sp14 = 0;
        sp12 = 0;
        sp10 = 0;
        if (func_8003DE58(M2C_FIELD(arg2, s32 *, 8), arg2, &sp10, 1) != 0) {
            temp_v0_2 = M2C_FIELD(temp_s0, u16 *, 6) + sp10;
            M2C_FIELD(temp_s0, u16 *, 6) = temp_v0_2;
            M2C_FIELD(temp_s2, u16 *, 2) = temp_v0_2;
            temp_v0_3 = M2C_FIELD(temp_s0, u16 *, 0xA) + sp12;
            M2C_FIELD(temp_s0, u16 *, 0xA) = temp_v0_3;
            M2C_FIELD(temp_s2, u16 *, 6) = temp_v0_3;
            temp_v0_4 = M2C_FIELD(temp_s0, u16 *, 0xE) + sp14;
            M2C_FIELD(temp_s0, u16 *, 0xE) = temp_v0_4;
            M2C_FIELD(temp_s2, u16 *, 0xA) = temp_v0_4;
        }
        M2C_FIELD(temp_s0, s32 *, 0x10) = (s32) ((s32) (M2C_FIELD(temp_s3, s32 *, 0) - M2C_FIELD(temp_s0, s32 *, 4)) / 32);
        M2C_FIELD(temp_s0, s32 *, 0x14) = (s32) ((s32) (M2C_FIELD(temp_s3, s32 *, 4) - M2C_FIELD(temp_s0, s32 *, 8)) / 32);
        M2C_FIELD(temp_s0, s32 *, 0x18) = (s32) ((s32) ((M2C_FIELD(temp_s3, s32 *, 8) - (*(M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), u8 *, 0x13) + &D_800DDC40) << 0xF)) - M2C_FIELD(temp_s0, s32 *, 0xC)) / 32);
        return temp_v0;
    }
    return NULL;
}
