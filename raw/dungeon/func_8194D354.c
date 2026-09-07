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

typedef s32 UnalignedS32 __attribute__((aligned(1)));

typedef struct {
    UnalignedS32 word;
} Packed4;

typedef struct {
    s32 words[4];
} FourWords __attribute__((aligned(4)));

typedef struct {
    Packed4 part[2];
} Packed8;

typedef struct {
    s32 words[8];
} EightWords;

extern void *D_80024008[];
void func_8002401C();
void func_80024494();
void func_800249E4();
s32 func_8003DE58();
s32 func_80053EF0();
M2C_UNK func_80065820();
s32 func_80069EF8();
M2C_UNK func_8009CE1C();
void *func_800A05A4();
s32 func_800A45D8();
s32 func_800A56E0();
s16 func_800BCAD0();
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_800814A0;
extern M2C_UNK D_800814A8;
extern M2C_UNK D_80082E80;
extern u16 D_80082E94;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern s32 D_80083780;
extern M2C_UNK D_800DE5DC;
extern s32 D_800E3D18;

void func_80024B54(void *arg0, void *arg1) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    M2C_UNK sp38[6];
    Packed8 sp50;
    FourWords sp58[2];
    s16 sp78[3];
    M2C_UNK *var_s1;
    register u8 *case2_page ASM_REG("$19");
    u8 *table_s5;
    u8 *table_s6;
    register M2C_UNK *var_v1 ASM_REG("$3");
    s32 *base_83780;
    register u8 *case1_page ASM_REG("$5");
    register void *held_arg1 ASM_REG("$20");
    register s16 temp_s7 ASM_REG("$23");
    s32 temp_v1;
    register s32 temp_v0_2 ASM_REG("$4");
    register s32 var_a1 ASM_REG("$5");
    register s32 var_s0 ASM_REG("$16");
    register u16 *var_v0 ASM_REG("$2");
    s32 temp_check;
    register s32 table_step ASM_REG("$2");
    register s32 post_mask ASM_REG("$4");
    register s32 post_color ASM_REG("$5");
    u16 temp_v0;
    u16 temp_v0_4;
    u16 temp_v0_5;
    u16 temp_v0_6;
    register u16 next_state ASM_REG("$2");
    u8 coord_y;
    void *temp_a0;
    register void *temp_a2 ASM_REG("$6");
    register s32 temp_a3 ASM_REG("$7");
    void *temp_v0_3;
    register void *temp_v1_2 ASM_REG("$3");

    held_arg1 = arg1;
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xA);
    M2C_FIELD(arg0, u16 *, 0x10) = (u16)(M2C_FIELD(arg0, u16 *, 0x10) + 1);
    if ((u32)temp_v1 >= 5U) {
        goto block_46;
    }
    (void)jt_keep;
    goto *D_80024008[(u32)temp_v1];
jt_c0:
    temp_a2 = (void *)0x800E0000;
    ASM_KEEP_NV(temp_a2);
    ASM_CLOBBER("$3");
    temp_v1_2 = (void *)0x80080000;
    next_state = M2C_FIELD(arg0, u16 *, 0xA);
    ASM_KEEP_DEP_NV(temp_v1_2, next_state);
    temp_v1_2 = M2C_FIELD(temp_v1_2, void **, 0x14A8);
    ASM_KEEP_DEP_NV(temp_a2, temp_v1_2);
    temp_a2 = (u8 *)temp_a2 - 0x1A24;
    M2C_FIELD(arg0, u16 *, 0x10) = 0U;
    M2C_FIELD(arg0, s16 *, 0xA) = (s16)(next_state + 1);
    M2C_FIELD(temp_v1_2, s32 *, 0xF4) = 0;
    func_80024494(M2C_FIELD(arg0, s32 *, 0) - 0x20, M2C_FIELD(arg0, u16 **, 4), temp_a2);
jt_c1:
    if (!(*M2C_FIELD(arg0, u16 **, 4) & 0x80)) {
        goto block_46;
    }
    case1_page = (u8 *)0x80080000;
    temp_v1_2 = M2C_FIELD(case1_page, void **, 0x14A8);
    M2C_FIELD(arg0, u16 *, 0x18) = 0xAU;
    M2C_FIELD(temp_v1_2, u16 *, 0xA6) = (u16)(M2C_FIELD(temp_v1_2, u16 *, 0xA6) - 1);
    temp_v0_2 = 4;
    M2C_FIELD(temp_v1_2, u8 *, 0xA8) = (u8)M2C_FIELD(arg0, u8 *, 8);
    temp_v1_2 = M2C_FIELD(case1_page, void **, 0x14A8);
    next_state = M2C_FIELD(arg0, u16 *, 0xA);
    temp_v1_2 = (void *)(s32)M2C_FIELD(temp_v1_2, u16 *, 0x2A);
    M2C_FIELD(arg0, s16 *, 0xA) = (s16)(next_state + 1);
    M2C_FIELD(arg0, u16 *, 0xE) = (u16)(s32)temp_v1_2;
    if (func_80053EF0(temp_v0_2, case1_page) == 2) {
        goto block_6;
    }
    func_800A56E0(0x300);
    M2C_FIELD(arg0, s16 *, 0x1A) = 0;
    return;
block_6:
    func_800A56E0(0x4300);
    M2C_FIELD(arg0, s16 *, 0x1A) = 0;
    return;
jt_c2:
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x18) - 1;
    M2C_FIELD(arg0, u16 *, 0x18) = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto block_46;
    }
    temp_v0_2 = func_80069EF8();
    var_a1 = temp_v0_2;
    if (temp_v0_2 >= 0) {
        goto block_10;
    }
    var_a1 = temp_v0_2 + 0xFFF;
block_10:
    base_83780 = &D_80083780;
    table_step = (s32)D_80083780;
    ASM_CLOBBER("$19");
    case2_page = (u8 *)0x80080000;
    M2C_FIELD(held_arg1, s32 *, 0) = table_step;
    table_step = var_a1 >> 0xC;
    table_step <<= 0xC;
    ASM_KEEP(table_step);
    temp_s7 = temp_v0_2 - table_step;
    temp_v1_2 = (void *)base_83780[1];
    M2C_FIELD(held_arg1, s32 *, 4) = (s32)temp_v1_2;
    ASM_KEEP_NV(case2_page);
    table_step = (s32)0x80080000;
    ASM_KEEP(table_step);
    temp_v1_2 = M2C_FIELD(case2_page, void **, 0x14A8);
    table_s5 = (u8 *)(table_step + 0x2E80);
    table_step = M2C_FIELD(temp_v1_2, s16 *, 0x88);
    temp_a2 = sp78;
    table_step = (table_step - 0x50) << 0x10;
    M2C_FIELD(held_arg1, s32 *, 8) = table_step;
    table_step = D_80083228;
    temp_v1 = M2C_FIELD(temp_v1_2, s16 *, 0x2A);
    temp_a3 = 0;
    table_step = ((table_step + temp_v1 + 0x100) >> 7) & 0x1C;
    temp_a0 = (void *)(s32)*(M2C_UNK *)(table_step + D_800E3D18);
    ASM_KEEP_DEP_NV(table_s5, temp_a0);
    if (func_8003DE58(temp_a0, table_s5, temp_a2, temp_a3) == 0) {
        goto block_12;
    }
    M2C_FIELD(held_arg1, s32 *, 0) = (s32)(M2C_FIELD(held_arg1, s32 *, 0) + (sp78[0] << 0x10));
    M2C_FIELD(held_arg1, s32 *, 4) = (s32)(M2C_FIELD(held_arg1, s32 *, 4) + (sp78[1] << 0x10));
    M2C_FIELD(held_arg1, s32 *, 8) = (s32)(M2C_FIELD(held_arg1, s32 *, 8) + (sp78[2] << 0x10));
block_12:
    temp_a0 = M2C_FIELD(case2_page, void **, 0x14A8);
    temp_v0_3 = func_800A05A4(temp_a0, M2C_FIELD(table_s5, u8 *, 0x24), M2C_FIELD(table_s5, u8 *, 0x25), (s16)M2C_FIELD(temp_a0, u16 *, 0x2A), 8);
    M2C_FIELD(arg0, void **, 0x14) = temp_v0_3;
    if (temp_v0_3 == NULL) {
        goto block_14;
    }
    var_s1 = M2C_FIELD(temp_v0_3, M2C_UNK **, -0x18);
    goto block_21;
block_14:
    var_s1 = sp38;
    var_s0 = 0;
    table_s6 = (u8 *)&D_8006CCD8;
    M2C_FIELD(var_s1, u16 *, 2) = (u16)((M2C_FIELD(table_s5, u8 *, 0x24) << 6) + 0x20);
    coord_y = M2C_FIELD(table_s5, u8 *, 0x25);
    table_s5 = (u8 *)&D_8006CCE8;
    M2C_FIELD(var_s1, u16 *, 6) = (u16)((coord_y << 6) + 0x20);
loop_15:
    temp_a0 = M2C_FIELD(case2_page, void **, 0x14A8);
    table_step = *(s16 *)((s32)((M2C_FIELD(temp_a0, u16 *, 0x2A) >> 8) & 0xE) + (s32)table_s6);
    ASM_KEEP(table_step);
    M2C_FIELD(var_s1, u16 *, 2) = (u16)(M2C_FIELD(var_s1, u16 *, 2) + (table_step << 6));
    table_step = *(s16 *)((s32)((M2C_FIELD(temp_a0, u16 *, 0x2A) >> 8) & 0xE) + (s32)table_s5);
    ASM_KEEP(table_step);
    M2C_FIELD(var_s1, u16 *, 6) = (u16)(M2C_FIELD(var_s1, u16 *, 6) + (table_step << 6));
    M2C_FIELD(var_s1, u16 *, 0xA) = (u16)M2C_FIELD(temp_a0, u16 *, 0x88);
    temp_v0_4 = func_800BCAD0(var_s1);
    M2C_FIELD(var_s1, u16 *, 0xA) = temp_v0_4;
    if ((s16)temp_v0_4 < 0x201) {
        goto block_17;
    }
    M2C_FIELD(var_s1, u16 *, 0xA) = (u16)M2C_FIELD(M2C_FIELD(case2_page, void **, 0x14A8), u16 *, 0x88);
block_17:
    temp_check = func_800A45D8(M2C_FIELD(var_s1, u16 *, 2), M2C_FIELD(var_s1, u16 *, 6), (s16)M2C_FIELD(var_s1, u16 *, 0xA));
    ASM_KEEP(temp_check);
    var_s0 += 1;
    if ((temp_check << 0x10) == 0) {
        goto block_20;
    }
    temp_a0 = M2C_FIELD(case2_page, void **, 0x14A8);
    table_step = *(s16 *)((s32)((M2C_FIELD(temp_a0, u16 *, 0x2A) >> 8) & 0xE) + (s32)table_s6);
    ASM_KEEP(table_step);
    M2C_FIELD(var_s1, u16 *, 2) = (u16)(M2C_FIELD(var_s1, u16 *, 2) - (table_step << 5));
    table_step = *(s16 *)((s32)((M2C_FIELD(temp_a0, u16 *, 0x2A) >> 8) & 0xE) + (s32)table_s5);
    ASM_KEEP(table_step);
    M2C_FIELD(var_s1, u16 *, 6) = (u16)(M2C_FIELD(var_s1, u16 *, 6) - (table_step << 5));
    M2C_FIELD(var_s1, u16 *, 0xA) = (u16)M2C_FIELD(temp_a0, u16 *, 0x88);
    temp_v0_5 = func_800BCAD0(var_s1);
    M2C_FIELD(var_s1, u16 *, 0xA) = temp_v0_5;
    if ((s16)temp_v0_5 < 0x201) {
        goto block_21;
    }
    M2C_FIELD(var_s1, u16 *, 0xA) = (u16)M2C_FIELD(M2C_FIELD(case2_page, void **, 0x14A8), u16 *, 0x88);
    goto block_21;
block_20:
    if (var_s0 < 8) {
        goto loop_15;
    }
block_21:
    func_8002401C(M2C_FIELD(held_arg1, s16 *, 2), M2C_FIELD(held_arg1, s16 *, 6), M2C_FIELD(held_arg1, s16 *, 0xA), M2C_FIELD(var_s1, s16 *, 2), (s32)M2C_FIELD(var_s1, s16 *, 6), (s32)M2C_FIELD(var_s1, s16 *, 0xA), &sp50);
    func_80065820(&sp50, sp58);
    func_800249E4((s32)arg0, held_arg1, var_s1, temp_s7, sp58[0], sp58[1], sp50);
    func_800249E4((s32)arg0, held_arg1, var_s1, (s16)(temp_s7 + 0x555), sp58[0], sp58[1], sp50);
    func_800249E4((s32)arg0, held_arg1, var_s1, (s16)(temp_s7 + 0xAAA), sp58[0], sp58[1], sp50);
    next_state = M2C_FIELD(arg0, u16 *, 0xA);
    M2C_FIELD(arg0, u16 *, 0x18) = 0x18U;
    goto block_43_store;
jt_c3:
    temp_a0 = M2C_FIELD(arg0, void **, 0x14);
    if (temp_a0 == NULL) {
        goto block_36;
    }
    M2C_FIELD(temp_a0, s32 *, 0x1C) = (s32)(M2C_FIELD(temp_a0, s32 *, 0x1C) | 0x10000000);
    temp_a2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), void **, -0x14);
    if ((s16)M2C_FIELD(arg0, u16 *, 0x18) < 0xC) {
        goto block_30;
    }
    M2C_FIELD(temp_a2, u8 *, 0xC) = (u8)(M2C_FIELD(temp_a2, u8 *, 0xC) + 8);
    M2C_FIELD(temp_a2, u8 *, 0xD) = (u8)(M2C_FIELD(temp_a2, u8 *, 0xD) - 8);
    M2C_FIELD(temp_a2, u8 *, 0xE) = (u8)(M2C_FIELD(temp_a2, u8 *, 0xE) - 8);
    if ((u8)M2C_FIELD(temp_a2, u8 *, 0xC) < 0xE1U) {
        goto block_26;
    }
    M2C_FIELD(temp_a2, u8 *, 0xC) = 0xE0U;
block_26:
    if ((u8)M2C_FIELD(temp_a2, u8 *, 0xD) >= 0x20U) {
        goto block_28;
    }
    M2C_FIELD(temp_a2, u8 *, 0xD) = 0x20U;
block_28:
    if ((u8)M2C_FIELD(temp_a2, u8 *, 0xE) >= 0x20U) {
        goto block_36;
    }
    M2C_FIELD(temp_a2, u8 *, 0xE) = 0x20U;
    goto block_36;
block_30:
    M2C_FIELD(temp_a2, u8 *, 0xC) = (u8)(M2C_FIELD(temp_a2, u8 *, 0xC) - 8);
    M2C_FIELD(temp_a2, u8 *, 0xD) = (u8)(M2C_FIELD(temp_a2, u8 *, 0xD) + 8);
    M2C_FIELD(temp_a2, u8 *, 0xE) = (u8)(M2C_FIELD(temp_a2, u8 *, 0xE) + 8);
    if ((u8)M2C_FIELD(temp_a2, u8 *, 0xC) >= 0x80U) {
        goto block_32;
    }
    M2C_FIELD(temp_a2, u8 *, 0xC) = 0x80U;
block_32:
    if ((u8)M2C_FIELD(temp_a2, u8 *, 0xD) < 0x81U) {
        goto block_34;
    }
    M2C_FIELD(temp_a2, u8 *, 0xD) = 0x80U;
block_34:
    var_v0 = (u16 *)(u32)M2C_FIELD(temp_a2, u8 *, 0xE);
    if ((u32)var_v0 < 0x81U) {
        var_v0 = (u16 *)0x80080000;
        goto block_37;
    }
    M2C_FIELD(temp_a2, u8 *, 0xE) = 0x80U;
block_36:
    var_v0 = (u16 *)0x80080000;
block_37:
    if (M2C_FIELD(var_v0, u16 *, 0x2E94) & 0x8000) {
        goto block_39;
    }
    temp_v0_6 = M2C_FIELD(arg0, u16 *, 0x18) - 1;
    M2C_FIELD(arg0, u16 *, 0x18) = temp_v0_6;
    if ((s16)temp_v0_6 >= 0) {
        goto block_46;
    }
block_39:
    if (M2C_FIELD(arg0, void **, 0x14) == NULL) {
        goto block_41;
    }
    func_8009CE1C(M2C_FIELD(arg0, void **, 0x14), 0xA, M2C_FIELD(arg0, u8 *, 9), 9, (s32)(s16)((M2C_FIELD(arg0, u16 *, 0xE) << 9) + 0x800), M2C_FIELD(arg0, s32 *, 0), 1);
    post_mask = 0xEFFFFFFF;
    post_color = 0x00808080;
    temp_v1_2 = M2C_FIELD(arg0, void **, 0x14);
    M2C_FIELD(temp_v1_2, s32 *, 0x1C) = (s32)(M2C_FIELD(temp_v1_2, s32 *, 0x1C) & post_mask);
    temp_a2 = M2C_FIELD(temp_v1_2, void **, -0x14);
    M2C_FIELD(temp_a2, s32 *, 0xC) = post_color;
block_41:
    var_v1 = (M2C_UNK *)0x80080000;
    if (M2C_FIELD(arg0, s16 *, 0x1A) == 0) {
        goto block_45_base;
    }
block_43:
    next_state = M2C_FIELD(arg0, u16 *, 0xA);
block_43_store:
    M2C_FIELD(arg0, s16 *, 0xA) = (s16)(next_state + 1);
    goto block_46;
jt_c4:
    if (M2C_FIELD(arg0, s16 *, 0x1A) != 0) {
        goto block_46;
    }
    var_v1 = (M2C_UNK *)0x80080000;
block_45_base:
    var_v1 = (M2C_UNK *)((u8 *)var_v1 + 0x3460);
block_45:
    M2C_FIELD(var_v1, s32 *, 0xC) = 0;
    M2C_FIELD(var_v1, u16 *, 0xA) = (u16)(M2C_FIELD(var_v1, u16 *, 0xA) - 1);
    M2C_FIELD(arg0, u16 *, -2) = (u16)(M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32)(M2C_FIELD(&D_800814A0, s32 *, 0) | 0x8000);
    return;
block_46:
    M2C_FIELD(arg0, s16 *, 0x1A) = 0;
    return;
}
