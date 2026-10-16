#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94(void *, M2C_UNK *, M2C_UNK);  /* extern */
void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_800478B8(void *);                      /* extern */
s32 func_800BCB04(s32, s32, s16);                   /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_800DEEC0;
extern M2C_UNK D_80168254;

void *func_801682AC(void *arg0, void *arg1, void *arg2) {
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_v0_2;
    s32 temp_v1;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s1;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s1 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80168254;
        M2C_FIELD(temp_v0, s16 *, 0x20) = 0;
        M2C_FIELD(temp_s1, s16 *, 2) = (s16) (((u16) M2C_FIELD(arg0, u16 *, 0x2A) >> 9) & 7);
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, s8 *, 0xE) = 0x80;
        M2C_FIELD(temp_s0, s8 *, 0xD) = 0x80;
        M2C_FIELD(temp_s0, s8 *, 0xC) = 0x80;
        M2C_FIELD(temp_s0, s16 *, 0x12) = 0x7E40;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0x100);
        func_8003DB94(temp_s0, &D_800DEEC0, 0);
        func_800478B8(temp_s0);
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x800;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x800;
        func_8004491C(temp_v0, &D_80045340);
        temp_s0_2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s0_2, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
        M2C_FIELD(temp_s0_2, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
        M2C_FIELD(temp_s0_2, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 8);
        M2C_FIELD(temp_s0_2, s32 *, 0xC) = (s32) M2C_FIELD(arg1, s32 *, 0xC);
        M2C_FIELD(temp_s0_2, s32 *, 0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x10);
        M2C_FIELD(temp_s0_2, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
        temp_a2 = M2C_FIELD(temp_s1, s16 *, 2) * 2;
        temp_v1 = (s32) ((M2C_FIELD(arg2, u8 *, 0x24) + *(temp_a2 + &D_8006CCD8)) << 0x10) >> 0xA;
        M2C_FIELD(temp_s0_2, s16 *, 2) = (s16) (temp_v1 + 0x20);
        temp_a1 = (s32) ((M2C_FIELD(arg2, u8 *, 0x25) + *(temp_a2 + &D_8006CCE8)) << 0x10) >> 0xA;
        M2C_FIELD(temp_s0_2, s16 *, 6) = (s16) (temp_a1 + 0x20);
        temp_v0_2 = func_800BCB04(temp_v1 & 0xFFC0, temp_a1 & 0xFFC0, (s16) (M2C_FIELD(arg0, u16 *, 0x88) - 0x20)) << 0x10;
        if (temp_v0_2 < M2C_FIELD(temp_s0_2, s32 *, 8)) {
            M2C_FIELD(temp_s0_2, s32 *, 8) = temp_v0_2;
        }
        return temp_v0;
    }
    return NULL;
}
