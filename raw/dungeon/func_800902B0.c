#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80088AF8[];
s32 func_8003E4FC();
void func_800424E0();
void func_80042560();
M2C_UNK func_80042640();
void func_80042B68();
void func_80043914();
s32 func_80047DB8();
void func_80047DF0();
void func_80048A44();
void func_80095D30() __attribute__((noreturn));
void func_80095D34() __attribute__((noreturn));
M2C_UNK func_80093C70();
M2C_UNK func_80093D8C();
M2C_UNK func_800956B8();
M2C_UNK func_80099F04();
M2C_UNK func_80099F70();
void *(*func_800A0B94())(M2C_UNK, s8, s8, s16);
s32 func_800A1618();
M2C_UNK func_800A56E0();
extern M2C_UNK D_8003E140;
extern s32 D_80081488;
extern u8 *D_80082EB0;
extern s16 D_80083228;
extern u8 D_80083460[12];
extern M2C_UNK D_8008ACDC;
extern u8 D_800DCFB0[];
extern u8 D_800DD138[];
extern u8 D_800DD140[];
extern void *D_800E3DF0[];
extern s8 D_800E3E40;

void func_80095A10(u8 *incoming0, void *incoming1, void *incoming2, u8 *incoming3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6 };
    register u8 *arg0 ASM_REG("$18") = incoming0;
    void *arg1 = incoming1;
    void *arg2 = incoming2;
    register u8 *arg3 ASM_REG("$19") = incoming3;
    u8 *var_a1;
    s32 temp_v0;
    s32 temp_v0_2;
    u32 temp_flags;
    u16 temp_v0_4;
    u16 temp_v1_3;
    u8 *temp_s1;
    u32 temp_a0;
    void *temp_v0_3;
    void *temp_v1;
    void *temp_v1_2;
    u8 *temp_v1_4;

    temp_a0 = M2C_FIELD(arg0, u8 *, 0x9B);
    temp_s1 = D_80082EB0;
    if (temp_a0 >= 7U) {
        goto block_22;
    }
    (void)jt_keep; goto *D_80088AF8[(u32)(temp_a0)];
jt_c0:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_22;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = D_800DD138;
    func_80048A44(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + D_800DD138), 0, 1);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x200);
    func_80093C70(arg0, arg1, arg2);
    func_80093D8C(arg0, arg1, arg2);
    return func_80095D30();
jt_c1:
    temp_v0 = func_800A1618(M2C_FIELD(temp_s1, u8 *, 0), 2);
    if (temp_v0 == 0) {
        goto block_18;
    }
    D_80081488 = func_80047DB8(M2C_FIELD(temp_s1, u8 *, 0));
    func_800A0B94(M2C_FIELD(temp_s1, u8 *, 0), temp_v0, 0);
    (*(s8 *)&D_800E3E40) = 0;
    func_8003E4FC(0xFF, &D_8003E140, &D_800E3E40);
    return func_80095D30();
jt_c2:
    if (M2C_FIELD(&D_800E3E40, u8 *, 0) == 0) {
        goto block_22;
    }
    func_80047DF0(temp_a0);
    return func_80095D30();
jt_c3:
    temp_v0_2 = func_800A1618(M2C_FIELD(temp_s1, u8 *, 0), 2);
    if (temp_v0_2 == 0) {
        goto block_22;
    }
    func_80043914(D_80082EB0);
    temp_v0_3 = func_800A0B94(M2C_FIELD(temp_s1, u8 *, 0), temp_v0_2, 1)(6, M2C_FIELD(arg3, s8 *, 0x72), M2C_FIELD(arg3, s8 *, 0x73), (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20));
    if (temp_v0_3 == NULL) {
        goto block_12;
    }
    M2C_FIELD(arg3, void **, 0x60) = temp_v0_3;
    D_800E3DF0[M2C_FIELD(temp_s1, u8 *, 3) & 0x1F] = temp_v0_3;
    temp_v1 = M2C_FIELD(temp_v0_3, void **, -0x14);
    M2C_FIELD(temp_v1, s16 *, 0x1E) = 0x800;
    M2C_FIELD(temp_v1, s16 *, 0x1C) = 0x800;
    temp_v1_2 = M2C_FIELD(temp_v0_3, void **, -0x18);
    M2C_FIELD(temp_v1_2, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(temp_v1_2, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 6);
    M2C_FIELD(temp_v1_2, s16 *, 0xA) = (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 0x10);
    func_80042640(temp_v0_3, M2C_FIELD(temp_v0_3, u8 *, 0x13));
    func_800424E0(temp_v0_3, M2C_FIELD(temp_v0_3, u8 *, 0x13), temp_s1);
    temp_flags = M2C_FIELD(temp_v0_3, s32 *, 0x1C);
    temp_flags |= 0x02000000;
    temp_flags |= 0x20000;
    M2C_FIELD(temp_v0_3, s32 *, 0x1C) = temp_flags;
    func_80042560(temp_v0_3);
    func_800A56E0(0x704);
    func_80042B68(temp_v0_3, 3);
    func_80042B68(temp_v0_3, 1);
    if (M2C_FIELD(temp_v0_3, u8 *, 0x25) != 0) {
        goto block_12;
    }
    M2C_FIELD(temp_v0_3, u8 *, 0x25) = 1U;
block_12:
    temp_a0 = *(volatile u8 *)((u8 *)arg0 + 0x9B);
    {
        register u16 timer ASM_REG("$3") = 0x10U;
        M2C_FIELD(arg0, u16 *, 0x96) = timer;
        return func_80095D34();
    }
jt_c4:
    temp_v0_4 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_4;
    if ((temp_v0_4 << 0x10) > 0) {
        goto block_22;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = D_800DD140;
    func_80048A44(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + D_800DD140), 0, 1);
    goto block_18;
jt_c5:
    temp_v1_3 = M2C_FIELD(arg2, u16 *, 0x14);
    if (!(temp_v1_3 & 0x6000)) {
        goto block_22;
    }
    var_a1 = D_800DCFB0;
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (temp_v1_3 & 0xFDFF);
block_17:
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = var_a1;
    func_80048A44(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + var_a1), 0, 1);
block_18:
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    return;
jt_c6:
    if (M2C_FIELD(M2C_FIELD(arg3, void **, 0x60), s32 *, 0x14) & 0x100000) {
        goto block_22;
    }
    func_800956B8(arg0, arg1, arg2, temp_s1);
    M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8008ACDC;
    func_80099F70(M2C_FIELD(arg3, s32 *, 0x5C));
    func_80099F04(M2C_FIELD(arg3, s32 *, 0x5C));
    temp_v1_4 = D_80083460;
    M2C_FIELD(temp_v1_4, u16 *, 2) = (u16) (M2C_FIELD(temp_v1_4, u16 *, 2) | 0x812);
block_22:
    return;
}
