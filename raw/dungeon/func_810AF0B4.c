#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define ARM_RRX(x, carry) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

extern void *D_80170838[];
s32 func_8003F270(void);
void *func_8003FD64();
s32 func_8004491C();
void func_80047784();
void *func_800A05A4();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A56E0();
s32 func_800A94A0(void *, u8 *, s32, void *);
extern M2C_UNK D_80045340;
extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern u8 D_80083460[];
extern s32 D_8008346C;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800D7960;
extern M2C_UNK D_80170E54;
extern u8 D_80173C6C[];

void func_801728B4(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    s32 temp_v0;
    s32 temp_v1_2;
    s32 temp_a1_2;
    s32 var_s4;
    s32 var_v0_2;
    s32 var_v1;
    u16 pending[4];
    u16 temp_v0_3;
    u16 temp_v0_5;
    u16 temp_v1_5;
    u8 *var_s0;
    s32 temp_v1;
    u8 *temp_v1_4;
    void *temp_a0;
    void *temp_v0_2;
    register void *temp_v0_4 ASM_REG("$2");
    register void *temp_v1_3 ASM_REG("$3");
    void *var_v0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    var_s4 = 0;
    if (temp_v1 == 1) {
        goto block_37;
    }
    if ((s32) temp_v1 >= 2) {
        goto block_4;
    }
    if (temp_v1 == 0) {
        goto block_6;
    }
    return;
block_4:
    if (temp_v1 == 2) {
        goto block_40;
    }
    return;
block_6:
    if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000)) {
        goto block_12;
    }
    temp_v0 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
    if ((u32) (temp_v0 - 1) >= 7U) {
        goto block_20;
    }
    (void)jt_keep; goto *D_80170838[(u32)((temp_v0) - 1)];
jt_c7:
    var_s4 = 1;
    goto block_17;
jt_c6:
    var_s4 = 1;
    goto block_18;
jt_c5:
    var_s4 = 1;
    goto block_19;
block_12:
    temp_v1_2 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
    if (temp_v1_2 == 2) {
        goto block_18;
    }
    if (temp_v1_2 >= 3) {
        goto block_16;
    }
    var_s0 = NULL;
    if (temp_v1_2 == 1) {
        goto block_19;
    }
    goto block_21;
block_16:
    var_s0 = NULL;
    if (temp_v1_2 != 3) {
        goto block_21;
    }
jt_c3:
block_17:
    var_s0 = arg3 + 0xE;
    goto block_21;
jt_c2:
block_18:
    var_s0 = arg3 + 0xB;
    goto block_21;
jt_c1:
block_19:
    var_s0 = arg3 + 8;
    goto block_21;
jt_c4:
block_20:
    var_s0 = NULL;
block_21:
    if (*var_s0 == 0) {
        goto block_36;
    }
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFF7F);
    {
        s32 flag = var_s4;

        ASM_KEEP(flag);
        if (flag == 0) {
            goto block_24;
        }
    }
    var_v0 = D_800814A8;
    M2C_FIELD(arg3, void **, 0x60) = var_v0;
    goto block_26;
block_24:
    if (D_8006DE24[(*var_s0 * 0x14) + 0x12] != 2) {
        goto block_27;
    }
    var_v0 = M2C_FIELD(arg3, void **, 0x60);
    if (var_v0 == NULL) {
        goto block_33;
    }
block_26:
    temp_v1_3 = M2C_FIELD(var_v0, void **, -0x14);
    M2C_FIELD(arg3, s8 *, 0x72) = (s8) M2C_FIELD(temp_v1_3, u8 *, 0x24);
    M2C_FIELD(arg3, s8 *, 0x73) = (s8) M2C_FIELD(temp_v1_3, u8 *, 0x25);
    goto block_32;
block_27:
    M2C_FIELD(arg3, void **, 0x60) = func_800A05A4(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(arg3, s16 *, 0x2A), 0x10);
    ASM_KEEP(arg3);
    var_v0_2 = M2C_FIELD(arg3, s8 *, 0x72);
    var_v1 = M2C_FIELD(arg3, s8 *, 0x73);
    if (var_v0_2 >= 0) {
        goto block_29;
    }
    var_v0_2 = 0 - var_v0_2;
block_29:
    if (var_v1 >= 0) {
        goto block_31;
    }
    var_v1 = 0 - var_v1;
block_31:
    M2C_FIELD(arg3, s8 *, 0x72) = var_v0_2;
    M2C_FIELD(arg3, s8 *, 0x73) = var_v1;
block_32:
block_33:
    pending[0] = M2C_FIELD(arg1, u16 *, 2);
    pending[1] = M2C_FIELD(arg1, u16 *, 6);
    pending[2] = M2C_FIELD(arg1, u16 *, 0xA);
    if (func_800A94A0(arg3, var_s0, var_s4, arg0 + 0x98) == 0) {
        goto block_56;
    }
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
    func_800A56E0(0x703);
    ASM_MEM_BARRIER();
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    temp_v0_2 = func_8003FD64(0x112, &D_80083498);
    M2C_FIELD(arg0, void **, 0xA0) = temp_v0_2;
    if (temp_v0_2 == NULL) {
        goto block_56;
    }
    func_8004491C(temp_v0_2, &D_80045340);
    M2C_FIELD(temp_v0_2, M2C_UNK **, 0x10) = &D_800D7960;
    M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 8), s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 8), s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 8), s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + 0xFF800000);
    M2C_FIELD(temp_v0_2, s8 *, 0xBB) = 0;
    temp_a0 = M2C_FIELD(temp_v0_2, void **, 0xC);
    M2C_FIELD(temp_v0_2, u16 *, 0x4A) = (u16) M2C_FIELD(arg3, s16 *, 0x2A);
    temp_v1_2 = M2C_FIELD(arg2, s32 *, 0x28);
    M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x1000;
    M2C_FIELD(temp_a0, s32 *, 0x28) = temp_v1_2;
    temp_v0_3 = M2C_FIELD(arg2, u16 *, 0x14);
    temp_a1_2 = 0x2D;
    M2C_FIELD(temp_a0, u16 *, 0x14) = temp_v0_3;
    temp_v1_5 = M2C_FIELD(arg2, u16 *, 0x12);
    M2C_FIELD(temp_a0, s16 *, 0x10) = 0;
    M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (temp_v0_3 | 0xC);
    M2C_FIELD(temp_a0, s16 *, 0x12) = (s16) (temp_v1_5 - 0x80);
    M2C_FIELD(temp_a0, s32 *, 0xC) = (s32) M2C_FIELD(arg2, s32 *, 0xC);
    func_80047784(temp_a0, temp_a1_2, 0);
    return;
block_36:
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    D_8008346C = 0;
    M2C_FIELD(D_800814A8, u16 *, 0xA6) = (u16) (M2C_FIELD(D_800814A8, u16 *, 0xA6) - 1);
    func_800A4ACC(arg3);
    M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
    M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80170E54;
    M2C_FIELD(arg3, s8 *, 0x73) = 0;
    M2C_FIELD(arg3, s8 *, 0x72) = 0;
    M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
    return;
block_37:
    if (func_8003F270() == 0) {
        goto block_39;
    }
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
    return;
block_39:
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
block_40:
    temp_v0_4 = M2C_FIELD(arg0, void **, 0xA0);
    ASM_KEEP(temp_v0_4);
    if (temp_v0_4 == NULL) {
        goto block_43;
    }
    var_s0 = temp_v0_4;
    temp_a0 = M2C_FIELD(var_s0, void **, 0xC);
    if (!(M2C_FIELD(temp_a0, u16 *, 0x14) & 0xE000)) {
        goto block_43;
    }
    M2C_FIELD(var_s0, u8 *, 0xBB) = 0xFF;
    M2C_FIELD(arg0, void **, 0xA0) = NULL;
block_43:
    if (M2C_FIELD(arg2, s8 *, 4) != 4) {
        goto block_45;
    }
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x1000) {
        goto block_46;
    }
block_45:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_47;
    }
block_46:
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
    M2C_FIELD(arg0, u16 *, 0x96) = 3U;
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x80);
block_47:
    temp_v0_5 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_5;
    if ((temp_v0_5 << 0x10) > 0) {
        goto block_49;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
block_49:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_56;
    }
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_80173C6C) {
        goto block_52;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80173C6C;
    func_80047784(arg2, D_80173C6C[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
block_52:
    temp_v1_4 = D_80083460;
    if (M2C_FIELD(temp_v1_4, s32 *, 0xC) != 0) {
        goto block_56;
    }
    M2C_FIELD(temp_v1_4, u16 *, 0xA) = (u16) (M2C_FIELD(temp_v1_4, u16 *, 0xA) - 1);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
    M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80170E54;
    func_800A4ACC(arg3);
    if ((s8) M2C_FIELD(arg3, u8 *, 0x6D) <= 0) {
        goto block_55;
    }
    M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
block_55:
    M2C_FIELD(arg3, s8 *, 0x73) = 0;
    M2C_FIELD(arg3, s8 *, 0x72) = 0;
    M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
    func_800A56E0(0xB4);
block_56:
    return;
}
