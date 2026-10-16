#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64(M2C_UNK, void *);               /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80047784(void *, M2C_UNK, M2C_UNK);    /* extern */
extern M2C_UNK D_8016E74C;
extern M2C_UNK D_8016F540;

void func_8016EB90(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_a0;
    void *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x100, arg0);
    if (temp_v0 != NULL) {
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        temp_s0 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8016E74C;
        M2C_FIELD(temp_s0, void **, 0x14) = (void *) M2C_FIELD(arg0, void **, 0xC);
        M2C_FIELD(temp_s0, void **, 0x18) = (void *) M2C_FIELD(arg0, void **, 8);
        M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_a0, s32 *, 0xC) = 0x808080;
        M2C_FIELD(temp_a0, s32 *, 0x28) = (s32) M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x14), s32 *, 0x28);
        M2C_FIELD(temp_a0, u16 *, 0x12) = (u16) M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x14), u16 *, 0x12);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), u16 *, 2) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), u16 *, 6) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), u16 *, 0xA) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA);
        func_80047784(temp_a0, 0x46, 0);
        func_8004491C(temp_v0, &D_8016F540);
        M2C_FIELD(temp_v0, s32 *, 0x20) = arg1;
        M2C_FIELD(temp_s0, s32 *, 4) = arg2;
        M2C_FIELD(temp_s0, s32 *, 8) = arg3;
        M2C_FIELD(temp_s0, void **, 0xC) = arg0;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
    }
}
