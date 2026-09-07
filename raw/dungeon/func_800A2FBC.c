/* cfail-repair: tf7-phase1-cache-v3 */
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

s32 func_8003DE58();
s32 func_80098920();
M2C_UNK func_8009A028();
s32 func_8009B164();
void *func_8009B25C();
M2C_UNK func_800A2B04();
M2C_UNK func_800A7A7C();
M2C_UNK func_800A891C();
M2C_UNK func_800A8CA8();
M2C_UNK func_800A8E20();
M2C_UNK func_800A8E50();
M2C_UNK func_800B66C8();
s16 func_800BCB04();
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern M2C_UNK D_80081484;
extern s32 D_800814A0[3];
extern void *D_800814A8;
extern u16 D_80083460[6];
extern u8 D_800DD7DC[];
extern s32 D_800E3540;
extern void *D_800E3D7C[3];

#ifdef NON_MATCHING
#define DUNGEON_FLAGS_PAGE ((s8 *)D_800814A0 - 0x14A0)
#else
#define DUNGEON_FLAGS_PAGE ((s8 *)0x80080000)
#endif

void func_800A871C(void *arg0, void *arg1, void *arg2) {
    register void *r_arg0 ASM_REG("$18") = arg0;
    register void *r_arg1 ASM_REG("$19") = arg1;
    register void *incoming_arg2 ASM_REG("$6") = arg2;
    register void *r_arg2 ASM_REG("$17");
    register void *temp_s0 ASM_REG("$16");
    u16 sp18[3];
    s16 temp_a0;
    s32 temp_a0_4;
    s16 temp_v0;
    s16 temp_v1_2;
    s16 var_a2;
    s16 var_a2_2;
    register s32 *temp_v1 ASM_REG("$3");
    register s32 temp_a0_2 ASM_REG("$4");
    register s32 temp_a0_5 ASM_REG("$4");
    s32 temp_a0_8;
    s32 temp_axis_adjusted;
    s32 temp_axis_scaled;
    register s32 temp_v1_3 ASM_REG("$20");
    s32 temp_v1_4;
    register u16 temp_a0_7 ASM_REG("$4");
    u16 temp_v0_3;
    u16 temp_v0_4;
    register u8 *temp_a0_3 ASM_REG("$4");
    register u8 *temp_a0_6 ASM_REG("$4");
    register u8 *temp_table_x_2 ASM_REG("$3");
    register u8 *temp_table_x_3 ASM_REG("$3");
    register u8 *temp_table_x_4 ASM_REG("$3");
    void *temp_a1;
    void *temp_a1_2;
    register void *temp_a1_3 ASM_REG("$5");
    void *temp_v0_2;
    void *temp_v0_5;
    u8 *temp_table_y_hot;
    register u8 *temp_table_y_derived ASM_REG("$3");
    register s32 temp_tail_result ASM_REG("$3");
    register s32 temp_tail_delta ASM_REG("$2");
    register u8 *temp_e_page ASM_REG("$2");
    register void *temp_global_814A8 ASM_REG("$3");
    s32 temp_global_sum;
    register s32 temp_global_flags ASM_REG("$2");
    register s32 temp_height ASM_REG("$6");

    ASM_KEEP4_NV(r_arg0, r_arg1, r_arg2, incoming_arg2);
    temp_s0 = r_arg0;
    r_arg2 = incoming_arg2;
    temp_v1 = M2C_FIELD(temp_s0, s32 **, 0x9C);
    if ((temp_v1 == &D_80081484) && (M2C_FIELD(temp_v1, u8 *, 1) == 0)) {
        M2C_FIELD(temp_s0, s32 **, 0x9C) = &D_800E3540;
    }
    temp_v1_2 = M2C_FIELD(r_arg0, s16 *, 0xA0);
    if (temp_v1_2 != 0) {
        if (temp_v1_2 != 1) {
            func_800A8E20();
            return;
        }
        goto block_type1;
    }
    {
        if (M2C_FIELD(temp_s0, s32 *, 0x1C) & 0x200000) {
            M2C_FIELD(temp_s0, u16 *, 0x2A) = (u16) M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x60), u16 *, 0x2A);
            if (func_8003DE58(
                    M2C_FIELD(
                        M2C_FIELD(
                            **M2C_FIELD(M2C_FIELD(r_arg0, void **, 0x90), s32 ***, 0x28) +
                                ((s32) M2C_FIELD(M2C_FIELD(M2C_FIELD(r_arg0, void **, 0x90), void **, 0x2C), u8 *, 2) * 4),
                            s32 *, 0),
                        s32 *, 4),
                    M2C_FIELD(r_arg0, void **, 0x90), sp18, 0) == 0) {
                M2C_FIELD(&sp18[2], s16 *, 0) = -0x30;
            }
            M2C_FIELD(r_arg1, s16 *, 0xA) = (s16) (M2C_FIELD(M2C_FIELD(r_arg0, void **, 0x8C), u16 *, 0xA) + sp18[2]);
            M2C_FIELD(r_arg2, u8 *, 0x24) = (u8) M2C_FIELD(M2C_FIELD(r_arg0, void **, 0x90), u8 *, 0x24);
            M2C_FIELD(r_arg2, u8 *, 0x25) = (u8) M2C_FIELD(M2C_FIELD(r_arg0, void **, 0x90), u8 *, 0x25);
            func_800A2B04(r_arg1, M2C_FIELD(r_arg2, volatile u8 *, 0x24), M2C_FIELD(r_arg2, volatile u8 *, 0x25));
            M2C_FIELD(r_arg0, s16 *, 0xA0) = (s16) ((u16) M2C_FIELD(r_arg0, s16 *, 0xA0) + 1);
            temp_a1 = M2C_FIELD(temp_s0, void * volatile *, 0x60);
            temp_a0_4 = M2C_FIELD(temp_s0, s16 *, 0x8A);
            temp_v0_4 = M2C_FIELD(temp_a1, u16 *, 0x2A);
            M2C_FIELD(temp_s0, s16 *, 0x6A) = (s16) temp_v0_4;
            temp_v1_3 = (temp_v0_4 >> 9) & 7;
            if (temp_a0_4 != 0) {
                s16 *temp_table_x = (s16 *)&D_8006CCD8;
                temp_v1_4 = temp_v1_3 * 2;
                temp_table_y_hot = (u8 *)&D_8006CCE8;
                ASM_KEEP_NV(temp_table_y_hot);
                temp_table_y_derived = (u8 *)((unsigned long)temp_v1_4 + (unsigned long)temp_table_y_hot);
                temp_tail_result = func_800BCB04((((M2C_FIELD(r_arg2, u8 *, 0x24) + (*(s16 *)((u8 *)temp_table_x + temp_v1_4) * temp_a0_4)) << 6) + 0x20) & 0xFFE0, (((M2C_FIELD(r_arg2, u8 *, 0x25) + (M2C_FIELD(temp_table_y_derived, s16 *, 0) * temp_a0_4)) << 6) + 0x20) & 0xFFE0, M2C_FIELD(r_arg1, s16 *, 0xA));
                ASM_KEEP_NV(temp_tail_result);
                if (temp_tail_result < 0x200) {
                    temp_tail_delta = temp_tail_result - M2C_FIELD(r_arg1, s16 *, 0xA);
                    ASM_TAILSLOT_PIN(temp_tail_delta);
                    func_800A891C();
                    return;
                }
                M2C_FIELD(r_arg1, s32 *, 0x14) = (s32) ((s32) ((M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x60), s16 *, 0x88) - M2C_FIELD(r_arg1, s16 *, 0xA)) << 0xF) / (s16) M2C_FIELD(temp_s0, u16 *, 0x8A));
            }
            temp_table_x_2 = (u8 *)&D_8006CCD8;
            ASM_KEEP(temp_table_x_2);
            temp_a0_5 = temp_v1_3 * 2;
            ASM_KEEP_NV(temp_a0_5);
            M2C_FIELD(r_arg2, u8 *, 0x24) = (u8) (M2C_FIELD(r_arg2, u8 *, 0x24) + M2C_FIELD((u8 *)((unsigned long)temp_a0_5 + (unsigned long)temp_table_x_2), u8 *, 0));
            temp_a0_6 = (u8 *)&D_8006CCE8 + temp_a0_5;
            M2C_FIELD(r_arg2, u8 *, 0x25) = (u8) (M2C_FIELD(r_arg2, u8 *, 0x25) + M2C_FIELD(temp_a0_6, u8 *, 0));
            M2C_FIELD(r_arg0, s16 *, 0xA4) = 2;
            func_800A8E50();
            return;
        }
        temp_a1_2 = M2C_FIELD(r_arg0, void **, 0x90);
        if ((func_8003DE58(M2C_FIELD(temp_a1_2, s32 *, 8), temp_a1_2, sp18, 0) != 0) && (M2C_FIELD(temp_s0, s32 *, 0x1C) & 0x80000)) {
            M2C_FIELD(r_arg0, s16 *, 0xA2) = 1;
            M2C_FIELD(r_arg1, s16 *, 2) = (s16) (M2C_FIELD(M2C_FIELD(r_arg0, void **, 0x8C), u16 *, 2) + sp18[0]);
            M2C_FIELD(r_arg1, s16 *, 6) = (s16) (M2C_FIELD(M2C_FIELD(r_arg0, void **, 0x8C), u16 *, 6) + sp18[1]);
            temp_global_sum = M2C_FIELD(M2C_FIELD(r_arg0, void **, 0x8C), u16 *, 0xA) + sp18[2];
            ASM_KEEP(temp_global_sum);
            temp_global_814A8 = D_800814A8;
            ASM_KEEP_NV(temp_global_814A8);
            M2C_FIELD(r_arg1, s16 *, 0xA) = (s16) (temp_global_sum + 8);
            M2C_FIELD(temp_s0, u16 *, 0x88) = M2C_FIELD(temp_global_814A8, u16 *, 0x88);
            goto block_A8B54;
        }
        if (M2C_FIELD(r_arg0, s16 *, 0xA2) != 0) {
            if (M2C_FIELD(temp_s0, s32 *, 0x1C) & 0x80000) {
                temp_e_page = (u8 *)0x800E0000;
                goto block_A8B58;
            }
            {
                temp_v0_5 = M2C_FIELD(temp_s0, void **, 0x60);
                temp_table_x_3 = (u8 *)&D_8006CCD8;
                temp_a0_7 = M2C_FIELD(temp_v0_5, u16 *, 0x2A);
                temp_a1_3 = M2C_FIELD(temp_v0_5, void **, -0x14);
                M2C_FIELD(temp_s0, s16 *, 0x6A) = (s16) temp_a0_7;
                temp_a0_8 = (temp_a0_7 >> 8) & 0xE;
                M2C_FIELD(r_arg2, u8 *, 0x24) = (u8) (M2C_FIELD(temp_a1_3, u8 *, 0x24) + M2C_FIELD((u8 *)((unsigned long)temp_a0_8 + (unsigned long)temp_table_x_3), u8 *, 0));
                M2C_FIELD(r_arg2, u8 *, 0x25) = (u8) (M2C_FIELD(temp_a1_3, u8 *, 0x25) + M2C_FIELD((u8 *)&D_8006CCE8 + temp_a0_8, u8 *, 0));
                func_800A2B04(r_arg1, M2C_FIELD(r_arg2, volatile u8 *, 0x24), M2C_FIELD(r_arg2, volatile u8 *, 0x25));
                var_a2_2 = func_800BCB04((M2C_FIELD(r_arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(r_arg2, u8 *, 0x25) << 6) | 0x20, M2C_FIELD(r_arg1, s16 *, 0xA));
                if (var_a2_2 >= 0x201) {
                    var_a2_2 = (s16) (u16) M2C_FIELD(r_arg1, s16 *, 0xA);
                }
                func_800A7A7C(M2C_FIELD(r_arg2, u8 *, 0x24), M2C_FIELD(r_arg2, u8 *, 0x25), var_a2_2, M2C_FIELD(r_arg2, s32 *, 8), M2C_FIELD(r_arg0, s32 **, 0x9C));
                M2C_FIELD(r_arg0, u16 *, -2) = (u16) (M2C_FIELD(r_arg0, u16 *, -2) | 0x8000);
                temp_global_flags = D_800814A0[0];
                ASM_KEEP_NV(temp_global_flags);
                temp_height = M2C_FIELD(r_arg1, s16 *, 0xA);
                D_800814A0[0] = (s32) (temp_global_flags | 0x8000);
                M2C_FIELD(r_arg1, s16 *, 0xA) = func_800BCB04((M2C_FIELD(r_arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(r_arg2, u8 *, 0x25) << 6) | 0x20, temp_height);
                func_800B66C8(r_arg1);
                func_8009A028(temp_s0);
                func_800A8E50();
                ASM_KEEP(temp_s0);
                return;
            }
block_A8B54:
            temp_e_page = (u8 *)0x800E0000;
block_A8B58:
            if (M2C_FIELD(M2C_FIELD(temp_e_page, void **, 0x3D7C), s32 *, 0x124) == 0) {
                register void *temp_call_arg ASM_REG("$4") = temp_s0;
                register s8 *temp_flags_page ASM_REG("$3") = DUNGEON_FLAGS_PAGE;
                M2C_FIELD(r_arg0, u16 *, -2) = (u16) (M2C_FIELD(r_arg0, u16 *, -2) | 0x8000);
                temp_global_flags = M2C_FIELD(temp_flags_page, s32 *, 0x14A0);
                temp_global_flags |= 0x8000;
                func_8009A028((M2C_FIELD(temp_flags_page, s32 *, 0x14A0) = temp_global_flags, temp_call_arg));
                func_800A8E50();
                return;
            }
            goto block_49;
        }
        return;
    }
block_type1:
    temp_a0 = M2C_FIELD(r_arg0, s16 *, 0xA4);
    if (temp_a0 != 0) {
        temp_axis_scaled = M2C_FIELD(r_arg2, u8 *, 0x24);
        temp_axis_adjusted = M2C_FIELD(r_arg1, s16 *, 2);
        temp_axis_scaled <<= 6;
        temp_axis_adjusted -= 0x20;
        ASM_KEEP_NV(temp_axis_adjusted);
        M2C_FIELD(r_arg1, s32 *, 0xC) = (s32) (((temp_axis_scaled - temp_axis_adjusted) << 0x10) / temp_a0);
        temp_axis_scaled = M2C_FIELD(r_arg2, u8 *, 0x25);
        temp_axis_adjusted = M2C_FIELD(r_arg1, s16 *, 6);
        temp_axis_adjusted -= 0x20;
        temp_axis_scaled <<= 6;
        M2C_FIELD(r_arg1, s32 *, 0x10) = (s32) (((temp_axis_scaled - temp_axis_adjusted) << 0x10) / (s16) M2C_FIELD(r_arg0, s16 *, 0xA4));
    }
    temp_v0 = (u16) M2C_FIELD(r_arg0, s16 *, 0xA4) - 1;
    M2C_FIELD(r_arg0, s16 *, 0xA4) = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto block_49;
    }
    temp_v0_2 = func_8009B25C(temp_s0, M2C_FIELD(r_arg2, u8 *, 0x24), M2C_FIELD(r_arg2, u8 *, 0x25), M2C_FIELD(temp_s0, s16 *, 0x88));
    if (temp_v0_2 != NULL) {
        if ((M2C_FIELD(temp_v0_2, u8 *, 0x13) == 0x1F) && !(M2C_FIELD(temp_v0_2, s32 *, 0x1C) & 0x228) && (D_800DD7DC[0] != 0)) {
            M2C_FIELD(temp_v0_2, s32 *, 0x14) = (s32) (M2C_FIELD(temp_v0_2, s32 *, 0x14) | 0x800000);
            M2C_FIELD(temp_v0_2, s32 *, 0x48) = M2C_FIELD(M2C_FIELD(r_arg0, s32 **, 0x9C), s32 *, 0);
            func_800A8CA8(temp_v0_2);
            return;
        }
        if (func_80098920(temp_v0_2, M2C_FIELD(r_arg0, s32 **, 0x9C), 0xD, temp_s0) != 0) {
            ASM_KEEP(temp_s0);
            M2C_FIELD(r_arg0, u16 *, -2) = (u16) (M2C_FIELD(r_arg0, u16 *, -2) | 0x8000);
            D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
            func_8009A028(temp_s0);
            D_80083460[5] = (u16) (D_80083460[5] - 1);
            func_800A8E50();
            return;
        }
    }
    if ((func_8009B164(M2C_FIELD(temp_s0, s16 *, 0x6A), r_arg1, r_arg2) << 0x10) != 0) {
        temp_v0_3 = M2C_FIELD(temp_s0, u16 *, 0x8A) - 1;
        M2C_FIELD(temp_s0, u16 *, 0x8A) = temp_v0_3;
        if ((temp_v0_3 << 0x10) > 0) {
            func_800A2B04(r_arg1, M2C_FIELD(r_arg2, u8 *, 0x24), M2C_FIELD(r_arg2, u8 *, 0x25));
            temp_table_x_4 = (u8 *)&D_8006CCD8;
            ASM_KEEP(temp_table_x_4);
            temp_a0_2 = ((u16) M2C_FIELD(temp_s0, s16 *, 0x6A) >> 8) & 0xE;
            ASM_KEEP_NV(temp_a0_2);
            M2C_FIELD(r_arg2, u8 *, 0x24) = (u8) (M2C_FIELD(r_arg2, u8 *, 0x24) + M2C_FIELD((u8 *)((unsigned long)temp_a0_2 + (unsigned long)temp_table_x_4), u8 *, 0));
            temp_a0_3 = (u8 *)&D_8006CCE8 + temp_a0_2;
            M2C_FIELD(r_arg2, u8 *, 0x25) = (u8) (M2C_FIELD(r_arg2, u8 *, 0x25) + *temp_a0_3);
            M2C_FIELD(r_arg0, s16 *, 0xA4) = 2;
            func_800A8E20();
            return;
        }
    }
    var_a2 = func_800BCB04((M2C_FIELD(r_arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(r_arg2, u8 *, 0x25) << 6) | 0x20, M2C_FIELD(r_arg1, s16 *, 0xA));
    if (var_a2 >= 0x201) {
        var_a2 = (s16) (u16) M2C_FIELD(r_arg1, s16 *, 0xA);
    }
    func_800A7A7C(M2C_FIELD(r_arg2, u8 *, 0x24), M2C_FIELD(r_arg2, u8 *, 0x25), var_a2, M2C_FIELD(r_arg2, s32 *, 8), M2C_FIELD(r_arg0, s32 **, 0x9C));
    M2C_FIELD(r_arg0, u16 *, -2) = (u16) (M2C_FIELD(r_arg0, u16 *, -2) | 0x8000);
    D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
            func_8009A028(temp_s0);
    D_80083460[5] = (u16) (D_80083460[5] - 1);
block_49:
    M2C_FIELD(r_arg1, s32 *, 0) = (s32) (M2C_FIELD(r_arg1, s32 *, 0) + M2C_FIELD(r_arg1, s32 *, 0xC));
    M2C_FIELD(r_arg1, s32 *, 4) = (s32) (M2C_FIELD(r_arg1, s32 *, 4) + M2C_FIELD(r_arg1, s32 *, 0x10));
    M2C_FIELD(r_arg1, s32 *, 8) = (s32) (M2C_FIELD(r_arg1, s32 *, 8) + M2C_FIELD(r_arg1, s32 *, 0x14));
}
