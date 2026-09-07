#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern void *func_8004DA74(void *a0, u8 *a1, s32 a2);
extern void func_800B180C(void *a0, s32 a1);
extern void func_800B18F8(s32 a0);
extern s32 D_80078D6C[4];
extern u8 D_800D1560[16];

void func_800B19F8(void *arg0)
{
    register s32 v88 ASM_REG("$5");

    M2C_FIELD(M2C_FIELD(arg0, void **, 0x48), s32 *, 0) = (s32) D_80078D6C;
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x48), void **, 4), s16 *, 8) = 0;
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x48), void **, 4), s16 *, 0xA) = 0;

    M2C_FIELD(M2C_FIELD(arg0, void **, 0x4C), s32 *, 0) = M2C_FIELD(arg0, s32 *, 8);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x4C), void **, 4), s16 *, 8) = 0;
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x4C), void **, 4), s16 *, 0xA) = 0xF;

    M2C_FIELD(M2C_FIELD(arg0, void **, 0x54), s32 *, 0) =
        (s32) func_8004DA74(M2C_FIELD(arg0, void **, 0xC), D_800D1560, 0);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x54), void **, 4), s16 *, 8) = 0x43;
    v88 = 0x88;
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x54), void **, 4), s16 *, 0xA) = v88;

    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x50), void **, 4), s16 *, 8) = 0x67;
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x50), void **, 4), s16 *, 0xA) = v88;

    func_800B180C(arg0, v88);
    func_800B18F8(M2C_FIELD(arg0, s32 *, 8));
}
