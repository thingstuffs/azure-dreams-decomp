#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_801565B4(void *, void *, void *);      /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80073414;
extern M2C_UNK D_8007361C;
extern M2C_UNK D_801567F0;
extern M2C_UNK D_801575E0;

void func_80156D98(void *arg0, void *arg1, void *arg3) {
    s32 var_v0;
    void *temp_a0;
    void *temp_a2;
    void *temp_a2_2;
    void *temp_s1;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = func_8003FC64(0x12);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_801567F0;
        func_8004491C(temp_v0, &D_80045340);
        temp_a2 = M2C_FIELD(temp_v0, void **, 0xC);
        temp_s1 = temp_v0 + 0x20;
        M2C_FIELD(temp_a2, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a2, u16 *, 0x14) & 0xFFF3);
        M2C_FIELD(temp_s1, void **, 0x34) = arg0;
        M2C_FIELD(temp_v0, M2C_UNK *, 0x4C) = M2C_UNALIGNED32(M2C_FIELD(arg3, s8 *, 0x48));
        func_801565B4(temp_v0 + 0x4C, arg3, temp_a2);
        M2C_FIELD(arg3, s8 *, 0x48) = 0;
        M2C_FIELD(arg3, s8 *, 0x49) = 0;
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 2);
        M2C_FIELD(temp_v1, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 6);
        M2C_FIELD(temp_v1, s16 *, 0xA) = (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 0x20);
        M2C_FIELD(temp_s1, s32 *, 0x54) = (s32) (*((((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 7) & 0x1C) + &D_801575E0) << 0x12);
        M2C_FIELD(temp_s1, s32 *, 0x5C) = 0xFFF80000;
        M2C_FIELD(temp_s1, s32 *, 0x68) = 0x14900;
        M2C_FIELD(temp_s1, s32 *, 0x58) = (s32) (M2C_FIELD(((((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 7) & 0x1C) + &D_801575E0), s16 *, 2) << 0x12);
        M2C_FIELD(temp_s1, s16 *, 0x24) = (s16) (((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 9) & 7);
        temp_a2_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a2_2, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_a2_2, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_a2_2, s16 *, 6) = (s16) (M2C_FIELD(((((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 7) & 0x1C) + &D_801575E0), s16 *, 2) * 6);
        M2C_FIELD(arg0, s16 *, 0xA2) = 0x4D;
        M2C_FIELD(temp_s1, s8 *, 0x50) = (s8) ((s16) M2C_FIELD(arg1, u16 *, 2) / 64);
        M2C_FIELD(temp_s1, s8 *, 0x51) = (s8) ((s16) M2C_FIELD(arg1, u16 *, 6) / 64);
        M2C_FIELD(temp_a2_2, s8 *, 0xE) = 0x80;
        M2C_FIELD(temp_a2_2, s8 *, 0xD) = 0x80;
        M2C_FIELD(temp_a2_2, s8 *, 0xC) = 0x80;
        temp_a0 = (M2C_FIELD(temp_s1, u8 *, 0x2D) * 0x14) + &D_80073414;
        if (M2C_FIELD(temp_a0, u8 *, 0) == 0) {
            var_v0 = M2C_FIELD(temp_s1, u8 *, 0x2C) * 4;
        } else {
            var_v0 = M2C_FIELD(temp_s1, u8 *, 0x2C) * 2;
        }
        M2C_FIELD(temp_a2_2, s32 *, 8) = (s32) *((M2C_FIELD((((var_v0 + M2C_FIELD(temp_s1, u8 *, 0x2C)) * 4) + M2C_FIELD(temp_a0, s32 *, 0xC)), s16 *, 2) * 4) + &D_8007361C);
    }
}
