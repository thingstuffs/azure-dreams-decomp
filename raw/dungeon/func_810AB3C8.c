#include "common.h"
#include "m2c_compat.h"

s32 func_8003DE58(s32, void *, u16 *, M2C_UNK);     /* extern */
void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80047784(void *, M2C_UNK, M2C_UNK);    /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80150A00;

void *func_80150BC8(void *arg1, void *arg2) {
    u16 sp10;
    u16 sp12;
    u16 sp14;
    void *temp_a0;
    void *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x312);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80150A00;
        func_8004491C(temp_v0, &D_80045340);
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0, s32 *, 0x28) = (s32) M2C_FIELD(arg2, s32 *, 0x28);
        M2C_FIELD(temp_a0, s8 *, 0xE) = 0x80;
        M2C_FIELD(temp_a0, s8 *, 0xD) = 0x80;
        M2C_FIELD(temp_a0, s8 *, 0xC) = 0x80;
        M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_a0, s16 *, 6) = 1;
        M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC);
        M2C_FIELD(temp_a0, u16 *, 0x10) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x10) | 0x20);
        func_80047784(temp_a0, 0x37, 0);
        temp_s0 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s0, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
        M2C_FIELD(temp_s0, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
        M2C_FIELD(temp_s0, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 8);
        M2C_FIELD(temp_s0, s32 *, 0xC) = (s32) M2C_FIELD(arg1, s32 *, 0xC);
        M2C_FIELD(temp_s0, s32 *, 0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x10);
        M2C_FIELD(temp_s0, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
        sp14 = 0;
        sp12 = 0;
        sp10 = 0;
        if (func_8003DE58(M2C_FIELD(arg2, s32 *, 8), arg2, &sp10, 0) != 0) {
            M2C_FIELD(temp_s0, u16 *, 2) = (u16) (M2C_FIELD(temp_s0, u16 *, 2) + sp10);
            M2C_FIELD(temp_s0, u16 *, 6) = (u16) (M2C_FIELD(temp_s0, u16 *, 6) + sp12);
            M2C_FIELD(temp_s0, u16 *, 0xA) = (u16) (M2C_FIELD(temp_s0, u16 *, 0xA) + sp14);
        }
        return temp_v0;
    }
    return NULL;
}
