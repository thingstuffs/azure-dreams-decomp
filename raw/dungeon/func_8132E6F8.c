#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

void *func_8003FD64();
M2C_UNK func_8004491C();
s32 rand();
extern u8 D_80164BC4[];
extern u8 D_801654F0[];

void func_801656F8(void *arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6)
{
    register s32 held_arg4 ASM_REG("$19") = arg4;
    register s32 held_arg5 ASM_REG("$20") = arg5;
    void *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x211, arg0);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, void **, 0x10) = D_801654F0;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 2) = (s16)
            (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2) + arg3);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 6) = (s16)
            (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6) + held_arg4);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 0xA) = (s16)
            (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA) + held_arg5);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0xC), s16 *, 6) = 6;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0xC) = (s32)
            (((rand() & 0x7FFF) - 0x4000) << 4);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0x10) = (s32)
            (((rand() & 0x7FFF) - 0x4000) << 4);
        temp_s0 = temp_v0 + 0x20;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0x14) = arg6;
        M2C_FIELD(temp_s0, s16 *, 0x14) = arg1;
        M2C_FIELD(temp_s0, s16 *, 0x32) = 8;
        M2C_FIELD(temp_s0, s16 *, 0x34) = 8;
        func_8004491C(temp_v0, D_80164BC4);
        M2C_FIELD(temp_v0, s32 *, 0x20) = arg2;
        M2C_FIELD(temp_s0, s32 *, 8) = arg2;
    }
}
