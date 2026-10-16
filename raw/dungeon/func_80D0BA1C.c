#include "common.h"
#include "m2c_compat.h"

s32 func_8003DE58(s32, void *, u16 *, M2C_UNK);     /* extern */
void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
extern M2C_UNK D_800DDC40;
extern M2C_UNK D_8014CCEC;
extern M2C_UNK D_8014CD40;
extern M2C_UNK D_80151EBC;

void func_8014D21C(void *arg0, void *arg1, void *arg3) {
    u16 sp10;
    s8 var_a0;
    s8 var_v1;
    u16 var_v0;
    u8 temp_v0_2;
    void *temp_a1;
    void *temp_a2;
    void *temp_s0;
    void *temp_s2;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s2 = temp_v0 + 0x20;
        M2C_FIELD(temp_s2, s16 *, 0x18) = 2;
        M2C_FIELD(temp_s2, s16 *, 0x1A) = 2;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8014CD40;
        func_8004491C(temp_v0, &D_8014CCEC);
        temp_v1 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v1, u16 *, 0x14) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x14) & 0xFFF3);
        temp_s0 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s0, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 2);
        M2C_FIELD(temp_s0, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 6);
        M2C_FIELD(temp_s0, u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
        temp_a1 = M2C_FIELD(arg0, void **, -0x14);
        if (func_8003DE58(M2C_FIELD(temp_a1, s32 *, 8), temp_a1, &sp10, 0) != 0) {
            M2C_FIELD(temp_s0, u16 *, 2) = (u16) (M2C_FIELD(temp_s0, u16 *, 2) + sp10);
            M2C_FIELD(temp_s0, u16 *, 6) = (u16) (M2C_FIELD(temp_s0, u16 *, 6) + sp12);
            var_v0 = M2C_FIELD(temp_s0, u16 *, 0xA) + sp14;
        } else {
            var_v0 = M2C_FIELD(temp_s0, u16 *, 0xA) - 0x14;
        }
        M2C_FIELD(temp_s0, u16 *, 0xA) = var_v0;
        temp_v1_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v1_2, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_v1_2, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_v1_2, u8 *, 0xE) = 0xA0U;
        M2C_FIELD(temp_v1_2, u8 *, 0xD) = 0xA0U;
        M2C_FIELD(temp_v1_2, s8 *, 0xC) = 0xA0;
        M2C_FIELD(temp_v0, s8 *, 0x20) = 0xA0;
        M2C_FIELD(temp_s2, u8 *, 1) = (u8) M2C_FIELD(temp_v1_2, u8 *, 0xD);
        M2C_FIELD(temp_s2, u8 *, 2) = (u8) M2C_FIELD(temp_v1_2, u8 *, 0xE);
        if ((M2C_FIELD(arg3, void **, 0x60) != NULL) && !(M2C_FIELD(arg3, s32 *, 0x14) & 0x04000000)) {
            M2C_FIELD(temp_s2, s16 *, 0x60) = 0;
            M2C_FIELD(temp_s2, s16 *, 0x5C) = 0;
            M2C_FIELD(temp_s2, s16 *, 0x58) = 0;
            temp_a2 = M2C_FIELD(M2C_FIELD(arg3, void **, 0x60), void **, -0x18);
            M2C_FIELD(temp_s2, s16 *, 0x5A) = (s16) ((s32) ((M2C_FIELD(temp_a2, s16 *, 2) - (s16) M2C_FIELD(temp_s0, u16 *, 2)) - (*((((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 7) & 0x1C) + &D_80151EBC) * 0x10)) / 2);
            M2C_FIELD(temp_s2, s16 *, 0x5E) = (s16) ((s32) ((M2C_FIELD(temp_a2, s16 *, 6) - (s16) M2C_FIELD(temp_s0, u16 *, 6)) - (M2C_FIELD(((((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 7) & 0x1C) + &D_80151EBC), s16 *, 2) * 0x10)) / 2);
            M2C_FIELD(temp_s2, s16 *, 0x62) = (s16) ((s32) ((M2C_FIELD(temp_a2, s16 *, 0xA) - (s16) M2C_FIELD(temp_s0, u16 *, 0xA)) - ((u8) *(M2C_FIELD(M2C_FIELD(arg3, void **, 0x60), u8 *, 0x13) + &D_800DDC40) >> 1)) / 2);
            return;
        }
        M2C_FIELD(temp_s2, s16 *, 0x60) = 0;
        M2C_FIELD(temp_s2, s16 *, 0x5C) = 0;
        M2C_FIELD(temp_s2, s16 *, 0x58) = 0;
        temp_v0_2 = M2C_FIELD(arg3, u8 *, 0x72);
        var_a0 = (s8) M2C_FIELD(arg3, u8 *, 0x73);
        var_v1 = (s8) temp_v0_2;
        if (temp_v0_2 & 0x80) {
            var_v1 = -var_v1;
        }
        if (var_a0 & 0x8000) {
            var_a0 = -var_a0;
        }
        M2C_FIELD(temp_s2, s16 *, 0x5A) = (s16) ((s32) (((s32) (var_v1 << 0x10) >> 0xA) - ((s16) M2C_FIELD(temp_s0, u16 *, 2) - 0x20)) / 2);
        M2C_FIELD(temp_s2, s16 *, 0x62) = 0;
        M2C_FIELD(temp_s2, s16 *, 0x5E) = (s16) ((s32) (((s32) (var_a0 << 0x10) >> 0xA) - ((s16) M2C_FIELD(temp_s0, u16 *, 6) - 0x20)) / 2);
    }
}
