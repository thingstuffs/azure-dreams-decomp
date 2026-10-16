#include "common.h"
#include "m2c_compat.h"

s32 func_8003DE58(s32, void *, u16 *, M2C_UNK);     /* extern */
void *func_8003FD64(M2C_UNK, M2C_UNK *);            /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_8016BA38;
extern M2C_UNK D_8016FEE8;

void func_8016BBEC(void *arg0, void *arg1) {
    u16 sp10;
    void *temp_a1;
    void *temp_a3;
    void *temp_a3_2;
    void *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x212, &D_80083498);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, void **, 0x40) = arg0;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8016BA38;
        func_8004491C(temp_v0, &D_80045340);
        temp_a3 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a3, s16 *, 0x10) = 0x20;
        M2C_FIELD(temp_a3, s16 *, 6) = 8;
        M2C_FIELD(temp_a3, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a3, u16 *, 0x14) | 0xC);
        temp_s0 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s0, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
        M2C_FIELD(temp_s0, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
        M2C_FIELD(temp_s0, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 8);
        temp_a1 = M2C_FIELD(arg0, void **, -0x14);
        if (func_8003DE58(M2C_FIELD(temp_a1, s32 *, 8), temp_a1, &sp10, 0) != 0) {
            M2C_FIELD(temp_s0, u16 *, 2) = (u16) (M2C_FIELD(temp_s0, u16 *, 2) + sp10);
            M2C_FIELD(temp_s0, u16 *, 6) = (u16) (M2C_FIELD(temp_s0, u16 *, 6) + sp12);
            M2C_FIELD(temp_s0, u16 *, 0xA) = (u16) (M2C_FIELD(temp_s0, u16 *, 0xA) + sp14);
        }
        temp_a3_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a3_2, s16 *, 0x1E) = 0x800;
        M2C_FIELD(temp_a3_2, s16 *, 0x1C) = 0x800;
        M2C_FIELD(temp_a3_2, s8 *, 0xE) = 0x80;
        M2C_FIELD(temp_a3_2, s8 *, 0xD) = 0x80;
        M2C_FIELD(temp_a3_2, s8 *, 0xC) = 0x80;
        M2C_FIELD(temp_v0, M2C_UNK *, 0x44) = M2C_UNALIGNED32(M2C_FIELD(&D_8016FEE8, M2C_UNK *, 0));
        M2C_FIELD(temp_v0, M2C_UNK *, 0x48) = M2C_UNALIGNED32(M2C_FIELD(&D_8016FEE8, M2C_UNK *, 4));
        M2C_FIELD(temp_v0, M2C_UNK *, 0x4C) = M2C_UNALIGNED32(M2C_FIELD(&D_8016FEE8, M2C_UNK *, 8));
        M2C_FIELD(temp_a3_2, void **, 8) = (void *) (temp_v0 + 0x44);
    }
}
