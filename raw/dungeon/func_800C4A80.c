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

extern u16 D_8006CCD8[];
extern u8 D_8008333C[32];
extern u16 D_8006CCE8[];
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];
extern s8 D_800E2970[];
M2C_UNK func_8009A350();
s16 func_8009FB34();
s16 func_800BCB04();
s32 func_800CA410();

s32 func_800CA1E0(u32 arg0, void *arg1, void *volatile arg2, u16 arg3) {
    u16 sp10;
    u16 sp18;
    register s32 temp_a0 ASM_REG("$4");
    register s32 temp_s5 ASM_REG("$21");
    register s32 temp_s0 ASM_REG("$16");
    register s32 temp_s1 ASM_REG("$17");
    register s32 temp_s4 ASM_REG("$20");
    register s32 temp_index ASM_REG("$19");
    register s32 temp_raw_byte ASM_REG("$3");
    register s32 temp_raw_half ASM_REG("$2");
    register s32 temp_v1 ASM_REG("$3");
    register s32 temp_a1 ASM_REG("$5");
    register s32 temp_a2 ASM_REG("$6");
    register void *temp_a3 ASM_REG("$7");
    register u16 temp_entry_a3 ASM_REG("$7");
    register s32 temp_e_index ASM_REG("$3");
    register u16 *temp_ccd8_base ASM_REG("$2");
    register u16 *temp_fp;
    register u16 *temp_s6 ASM_REG("$22");
    register u16 *temp_dceac_page ASM_REG("$3");
    register u16 *temp_dcebc_page ASM_REG("$2");
    register u16 temp_s7 ASM_REG("$23");
    register u32 temp_table_page ASM_REG("$2");
    register s32 temp_tail_value ASM_REG("$2");
    register u32 temp_v0 ASM_REG("$2");
    register u32 temp_v1_3 ASM_REG("$3");
    register s32 temp_result ASM_REG("$2");
    register u16 temp_arg3_copy ASM_REG("$8");
    register void *temp_s2 ASM_REG("$18");
    register void *temp_arg2 ASM_REG("$8");
    register u8 *temp_table ASM_REG("$6");
    s32 final_value;
    void *var_a1;

    var_a1 = arg1;
    temp_s2 = var_a1;
    ASM_KEEP_NV(temp_s2);
    temp_entry_a3 = arg3;
    ASM_KEEP_NV(temp_entry_a3);
    temp_a0 = (arg0 >> 9) & 7;
    ASM_KEEP_NV(temp_a0);
    temp_s5 = temp_a0;
    ASM_KEEP_NV(temp_s5);
    temp_ccd8_base = D_8006CCD8;
    ASM_KEEP_NV(temp_ccd8_base);
    temp_index = temp_s5 << 1;
    ASM_KEEP_NV(temp_index);
    temp_fp = (u16 *)((u32)temp_index + (u32)temp_ccd8_base);
    ASM_KEEP_NV(temp_fp);
    temp_raw_byte = M2C_FIELD(temp_s2, u8 *, 0x24);
    ASM_KEEP_NV(temp_raw_byte);
    temp_raw_half = *temp_fp;
    ASM_KEEP_NV(temp_s5);
    ASM_CLOBBER("$4");
    temp_a0 = temp_s5;
    ASM_KEEP_NV(temp_a0);
    ASM_SCHED_BARRIER();
    sp18 = temp_entry_a3;
    temp_s1 = temp_raw_byte + temp_raw_half;
    temp_table_page = 0x80080000;
    ASM_KEEP_DEP_NV(temp_table_page, temp_s1);
    temp_v1 = temp_s1 & 0xFFFF;
    temp_table = (u8 *)(temp_table_page + 0x333C);
    if (temp_v1 == 0) {
        goto block_tail;
    }
    ASM_KEEP_NV(temp_table);
    var_a1 = (void *)1;
    if (((1 << M2C_FIELD(temp_table, s16 *, 0x14)) - 1) < temp_v1) {
        return -1;
    }
    temp_ccd8_base = D_8006CCE8;
    ASM_KEEP_NV(temp_ccd8_base);
    temp_s6 = (u16 *)((u32)temp_index + (u32)temp_ccd8_base);
    ASM_KEEP_NV(temp_s6);
    temp_raw_byte = M2C_FIELD(temp_s2, u8 *, 0x25);
    ASM_KEEP_NV(temp_raw_byte);
    temp_raw_half = *temp_s6;
    temp_s0 = temp_raw_byte + temp_raw_half;
    temp_v1 = temp_s0 & 0xFFFF;
    if (temp_v1 == 0) {
        return -1;
    }
    if (!(((1 << M2C_FIELD(temp_table, s16 *, 0x16)) - 1) < temp_v1)) {
        goto block_body;
    }
block_tail:
    ASM_KEEP_NV(temp_table);
    temp_tail_value = -1;
    ASM_TAILSLOT_PIN_TIED(temp_tail_value);
    return func_800CA410(temp_a0, var_a1, temp_table);
block_body:
    temp_v1_3 = M2C_FIELD(temp_s2, volatile u8 *, 0x24);
    temp_v0 = M2C_FIELD(temp_s2, volatile u8 *, 0x25);
    temp_arg2 = arg2;
    temp_v1_3 <<= 6;
    ASM_KEEP_NV(temp_v1_3);
    temp_a1 = temp_v1_3 >> 6;
    ASM_KEEP_NV(temp_a1);
    temp_v0 <<= 6;
    ASM_KEEP_NV(temp_v0);
    temp_a2 = temp_v0 >> 6;
    ASM_KEEP_NV(temp_a2);
    temp_s0 = temp_v1_3 + 0x20;
    temp_s7 = M2C_FIELD(temp_arg2, u16 *, 0x88);
    temp_s4 = temp_v0 + 0x20;
    if ((func_8009A540(temp_a0, temp_a1, temp_a2, (s16) (temp_s7 - temp_entry_a3)) << 0x10) == 0) {
        goto block_body_tail;
    }
    temp_a2 = temp_s5;
    ASM_KEEP_NV(temp_a2);
    temp_a3 = &sp10;
    ASM_KEEP_NV(temp_a3);
    temp_dceac_page = D_800DCEAC;
    ASM_KEEP_NV(temp_dceac_page);
    temp_dceac_page = (u16 *)((u32)temp_index + (u32)temp_dceac_page);
    ASM_KEEP_NV(temp_dceac_page);
    temp_dcebc_page = D_800DCEBC;
    ASM_KEEP_NV(temp_dcebc_page);
    temp_dcebc_page = (u16 *)((u32)temp_index + (u32)temp_dcebc_page);
    ASM_KEEP_NV(temp_dcebc_page);
    temp_a0 = M2C_FIELD(temp_s2, u8 *, 0x24);
    ASM_KEEP_NV(temp_a0);
    temp_a1 = M2C_FIELD(temp_s2, u8 *, 0x25);
    ASM_KEEP_NV(temp_a1);
    temp_raw_byte = *temp_dceac_page;
    temp_raw_half = *temp_dcebc_page;
    temp_s1 = temp_raw_byte + temp_s0;
    temp_s0 = temp_raw_half + temp_s4;
    func_8009A350(temp_a0, temp_a1, temp_a2, temp_a3);
    if ((sp10 & 0x8002) != 0) {
        goto block_body_tail;
    }
    goto block_body_continue;
block_body_tail:
    temp_tail_value = 0;
    ASM_TAILSLOT_PIN_TIED(temp_tail_value);
    return func_800CA410();
block_body_continue:
    if (M2C_FIELD(temp_s2, s8 *, 0x26) < 0) {
        temp_a0 = func_8009FB34((M2C_FIELD(temp_s2, u8 *, 0x24) + *temp_fp) & 0xFFFF, (M2C_FIELD(temp_s2, u8 *, 0x25) + *temp_s6) & 0xFFFF);
        ASM_KEEP_NV(temp_a0);
        if (temp_a0 >= 0) {
            temp_e_index = temp_a0 << 2;
            ASM_KEEP_NV(temp_e_index);
            temp_ccd8_base = (u16 *)D_800E2970;
            ASM_KEEP_NV(temp_ccd8_base);
            temp_e_index = (temp_e_index + temp_a0) << 2;
            ASM_KEEP_NV(temp_e_index);
            temp_e_index = temp_e_index + (u32)temp_ccd8_base;
            ASM_KEEP_NV(temp_e_index);
            temp_a0 = temp_s1 & 0xFFFF;
            if (!(M2C_FIELD((void *)temp_e_index, u16 *, 0xC) & 2)) {
                goto block_final;
            }
            ASM_SCHED_BARRIER();
            temp_arg2 = arg2;
            if (!(M2C_FIELD(temp_arg2, s32 *, 0x1C) & 0x2000)) {
                goto block_body_tail;
            }
        }
    }
    temp_a0 = temp_s1 & 0xFFFF;
block_final:
    temp_arg3_copy = sp18;
    ASM_KEEP_NV(temp_arg3_copy);
    final_value = (s16)func_800BCB04(temp_a0, temp_s0 & 0xFFFF, (s16) (temp_s7 - temp_arg3_copy));
    temp_result = -1;
    if (final_value < 0x201) {
        temp_result = 1;
    }
    return temp_result;
}
