#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FD64();
extern M2C_UNK func_8004491C();
extern M2C_UNK D_800D6804[3];
extern M2C_UNK D_800D68F4[3];

void func_800D6AD4(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5) {
    register s32 held_arg4 ASM_REG("$20") = arg4;
    register s32 held_arg5 ASM_REG("$21") = arg5;
    s32 temp_a2;
    void *temp_s0;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;
    void *temp_v1_2;
    void *temp_v1_3;

    temp_v0 = func_8003FD64(0x211, arg0);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = D_800D6804;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), u16 *, 2) =
            (u16)M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), u16 *, 6) =
            (u16)M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), u16 *, 0xA) =
            (u16)M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA);
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1, u16 *, 2) =
            (u16)(M2C_FIELD(temp_v1, u16 *, 2) + arg2);
        temp_v1_2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1_2, u16 *, 6) =
            (u16)(M2C_FIELD(temp_v1_2, u16 *, 6) + arg3);
        temp_v1_3 = M2C_FIELD(temp_v0, void **, 8);
        temp_a2 = held_arg5 << 0x12;
        M2C_FIELD(temp_v1_3, u16 *, 0xA) =
            (u16)(M2C_FIELD(temp_v1_3, u16 *, 0xA) + held_arg4);
        temp_v0_2 = M2C_FIELD(temp_v0, void **, 8);
        temp_s0 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0_2, s32 *, 0x10) = 0;
        M2C_FIELD(temp_v0_2, s32 *, 0xC) = 0;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0x14) =
            (s32)(0xFFFA0000 - temp_a2);
        M2C_FIELD(temp_s0, s16 *, 0x32) = 0x14;
        M2C_FIELD(temp_s0, s16 *, 0x34) = 0x14;
        func_8004491C(temp_v0, D_800D68F4, temp_a2);
        M2C_FIELD(temp_v0, s32 *, 0x20) = arg1;
        M2C_FIELD(temp_s0, s32 *, 8) = arg1;
        ASM_KEEP(held_arg4);
        ASM_KEEP(held_arg5);
    }
}
