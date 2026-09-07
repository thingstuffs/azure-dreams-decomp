#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern M2C_UNK func_8008F074();

extern u8 D_80045340[];
extern u8 D_80046398[];
extern u8 D_800BF72C[];
extern u8 D_800BF8DC[];
extern u8 D_800D2364[];
extern s32 D_800D237C[];
extern u8 D_800F9F78[];

void func_800BF9E4(void *arg0, void *arg1, M2C_UNK arg2) {
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;
    void *temp_v1_2;

    M2C_FIELD(arg0, M2C_UNK **, -0x10) = &D_800BF8DC[0];
    M2C_FIELD(arg0, s32 *, 0x50) = 0;
    func_8004491C(arg0 - 0x20, &D_80045340[0]);
    M2C_FIELD(arg1, s32 *, 0) = 0x0F200000;
    M2C_FIELD(arg1, s32 *, 4) = 0x02600000;
    M2C_FIELD(arg1, s32 *, 8) = 0;
    func_8008F074(arg0, arg1, &D_800D2364[0]);
    func_8003DB94(arg2, &D_800F9F78[0], 0);
    M2C_FIELD(arg0, s32 *, 0x48) = D_800D237C[0];
    temp_v0 = func_8003FC64(0x136);
    if (temp_v0 != 0) {
        func_8004491C(temp_v0, &D_80046398[0]);
        temp_v1 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800BF72C[0];
        M2C_FIELD(temp_v1, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_v1, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_v1, s16 *, 0x20) = 0x1000;
        M2C_FIELD(temp_v1, s16 *, 0x1A) = 0;
        M2C_FIELD(temp_v1, s32 *, 0xC) = 0x808080;
        M2C_FIELD(temp_v1, s32 *, 8) = 0x75;
        temp_v1_2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1_2, s32 *, 0) = 0x0FA00000;
        M2C_FIELD(temp_v1_2, s32 *, 4) = 0x02300000;
        temp_v0_2 = temp_v0 + 0x20;
        ASM_USE(temp_v0_2);
        M2C_FIELD(temp_v1_2, s32 *, 8) = 0;
        M2C_FIELD(temp_v0_2, void **, 0xA0) = arg0;
    }
}

/* MECHANISM: Natural argument liveness gives the 0x20 frame and s2/s0/s1 save order.
   A split tail sub-base plus input-only ASM_USE materializes v0 = s0 + 0x20 without a second def.
   This restores the 0xA0(v0) store and its upstream branch displacement; aligned residue is zero. */
