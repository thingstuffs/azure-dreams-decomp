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
typedef struct {
    u32 word0;
    u32 word1;
} __attribute__((packed)) UA64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_UNALIGNED32(expr) (expr)

struct S_8003E2D8 {
    char pad0[8];
    s32 field_8;
    s32 field_C;
    s32 field_10;
};
typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 D_80083160;
extern u8 D_80082E80[];
extern s8 D_800E2970[];
extern u8 D_800E50A8[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern void func_800672D8(void *, u8 *);
extern u8 D_80088CB0;
extern u8 D_800EA000[];

void func_8009D3B0(void) {
    UA64 sp10;
    s16 temp_a1;
    register s32 temp_t6 ASM_REG("$14");
    register s32 bound_shifted ASM_REG("$2");
    register s16 temp_v0_2 ASM_REG("$2");
    s32 var_a0;
    s16 var_a1;
    register s16 var_a3 ASM_REG("$7");
    register s16 var_t2 ASM_REG("$10");
    register s16 var_v0_3 ASM_REG("$2");
    s32 temp_v0;
    s32 temp_v0_3;
    M2C_UNK temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v1_2;
    s32 temp_v1_4;
    s32 x_sum;
    s32 level_value;
    s32 level_test;
    s32 var_v0_2;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_7;
    u16 temp_a0;
    u16 temp_v1_3;
    u16 temp_v1_5;
    s16 clamped_level;
    register s16 outer_end ASM_REG("$15");
    u8 *var_a2;
    u8 temp_a0_2;
    u8 map_value;
    register u8 *temp_t8 ASM_REG("$24");
    register s32 v1_role ASM_REG("$3");
    register u8 *status ASM_REG("$2");
    s8 status_value;

    var_a2 = &D_80088CB0;
    sp10 = *(UA64 *)var_a2;
    v1_role = (s32)&D_80083160;
    temp_t8 = (u8 *)v1_role + 0x1DC;
    status = D_80082E80;
    status_value = ((s8 *)status)[0x26];
    if (status_value >= 0) {
        register u8 *temp_t3 ASM_REG("$11");
        u8 *grid;
        u8 *map;
        register s32 signed_row ASM_REG("$9");
        register s32 inner_bound ASM_REG("$8");
        s32 outer_shifted;
        s32 inner_shifted;
        s32 row_shifted;
        s32 row_value;
        register s32 signed_raw ASM_REG("$2");
        register s32 three ASM_REG("$2");
        register s32 store_val ASM_REG("$2");
        v1_role = status_value * 0x14;
        ASM_KEEP(v1_role);
        status = (u8 *)D_800E2970;
        temp_t3 = v1_role + status;
        ASM_KEEP(temp_t3);
        v1_role = M2C_FIELD(temp_t3, u16 *, 2) - 1;
        var_t2 = v1_role;
        x_sum = M2C_FIELD(temp_t3, u16 *, 0) + M2C_FIELD(temp_t3, u16 *, 4);
        var_a0 = x_sum + 1;
        ASM_KEEP(x_sum);
        temp_v0 = M2C_FIELD(temp_t3, u16 *, 6) + v1_role + 2;
        outer_end = temp_v0;
        if ((v1_role << 0x10) < (temp_v0 << 0x10)) {
            var_a3 = var_a0;
            bound_shifted = var_a0 << 0x10;
            temp_t6 = bound_shifted >> 0x10;
            grid = D_800EA000;
            map = D_800E50A8;
loop_3:
            temp_v0_2 = M2C_FIELD(temp_t3, u16 *, 0) - 1;
            var_a1 = temp_v0_2;
            if (temp_v0_2 < temp_t6) {
                ASM_KEEP(var_t2);
                var_v0_2 = var_a1 << 0x10;
                signed_raw = var_t2 << 0x10;
                signed_row = signed_raw >> 0x10;
                signed_raw = var_a3 << 0x10;
                inner_bound = signed_raw >> 0x10;
loop_5:
                row_shifted = var_a1 << 0x10;
                row_value = row_shifted >> 0x10;
                v1_role = (signed_row << M2C_FIELD(temp_t8, s16 *, 0x14)) + row_value;
                var_a2 = (u8 *)((v1_role * 6) + (s32)grid);
                var_a0 = M2C_FIELD(var_a2, u16 *, 0);
                if (var_a0 != 0) {
                    ASM_KEEP(var_a1);
                    three = 3;
                    if (var_a0 != three) {
                        ASM_KEEP(v1_role);
                        var_v0_5 = v1_role / 2;
                        ASM_KEEP(v1_role);
                        v1_role = M2C_FIELD(var_a2, u16 *, 2);
                        var_a2 = (u8 *)(var_v0_5 + (s32)map);
                        status = (u8 *)((s16)(v1_role + 0x200) / 64);
                        var_a0 = (s32)status;
                        ASM_KEEP(status);
                        v1_role = (s32)status;
                        if (v1_role >= 0x10) {
                            var_a0 = 15;
                            goto clamp_p;
                        }
                        var_v0_4 = var_a0 << 0x10;
                        if (v1_role <= 0) {
                            var_a0 = 1;
                            ASM_KEEP(var_a0);
clamp_p:
                            var_v0_4 = var_a0 << 0x10;
                        }
                        v1_role = var_v0_4 >> 0x10;
                        var_a0 = *var_a2;
                        if (var_a1 & 1) {
                            store_val = var_a0 | (v1_role << 4);
                        } else {
                            store_val = var_a0 | v1_role;
                        }
                        *var_a2 = store_val;
                    }
                }
block_16:
                var_v0_3 = var_a1 + 1;
                var_a1 = var_v0_3;
                var_v0_2 = var_v0_3 << 0x10;
                if (var_v0_3 >= inner_bound) {
                    temp_v0_2 = var_t2 + 1;
                    goto block_18;
                }
                goto loop_5;
            }
block_18:
            temp_v0_2 = var_t2 + 1;
            var_t2 = temp_v0_2;
            if ((temp_v0_2 << 0x10) < (outer_end << 0x10)) {
                goto loop_3;
            }
            goto done;
        }
    } else {
    register u8 *negative_status ASM_REG("$8");
    register s32 neg_store ASM_REG("$2");
    register s32 neg_three ASM_REG("$2");
    register s16 var_v0_6 ASM_REG("$2");
    s32 neg_a0;
    u8 *x_offsets;
    u8 *y_offsets;
    u8 *grid;
    u8 *map;
    var_a3 = 7;
    negative_status = status;
    x_offsets = D_8006CCD8;
    y_offsets = D_8006CCE8;
    grid = D_800EA000;
    map = D_800E50A8;
loop_22:
    temp_v0_4 = (var_a3 << 0x10) >> 0xF;
    temp_a1 = negative_status[0x24] + *(u16 *)(temp_v0_4 + (s32)x_offsets);
    v1_role = ((s16) (negative_status[0x25] + *(u16 *)(temp_v0_4 + (s32)y_offsets)) << M2C_FIELD(temp_t8, s16 *, 0x14)) + temp_a1;
    var_a2 = (u8 *)((v1_role * 6) + (s32)grid);
    neg_a0 = M2C_FIELD(var_a2, u16 *, 0);
    if (neg_a0 != 0) {
        ASM_KEEP(temp_a1);
        neg_three = 3;
        if (neg_a0 != neg_three) {
            ASM_KEEP(v1_role);
            var_v0_5 = v1_role / 2;
            ASM_KEEP(v1_role);
            v1_role = M2C_FIELD(var_a2, u16 *, 2);
            var_a2 = (u8 *)(var_v0_5 + (s32)map);
            status = (u8 *)((s16)(v1_role + 0x200) / 64);
            neg_a0 = (s32)status;
            ASM_KEEP(status);
            v1_role = (s32)status;
            if (v1_role >= 0x10) {
                neg_a0 = 15;
                goto clamp_n;
            }
            var_v0_7 = neg_a0 << 0x10;
            if (v1_role <= 0) {
                neg_a0 = 1;
                ASM_KEEP(neg_a0);
clamp_n:
                var_v0_7 = neg_a0 << 0x10;
            }
            v1_role = var_v0_7 >> 0x10;
            neg_a0 = *var_a2;
            if (temp_a1 & 1) {
                neg_store = neg_a0 | (v1_role << 4);
            } else {
                neg_store = neg_a0 | v1_role;
            }
            *var_a2 = neg_store;
        }
    }
block_33:
    var_v0_6 = var_a3 - 1;
    var_a3 = var_v0_6;
    if ((var_v0_6 << 0x10) < 0) {
        goto done;
    }
    goto loop_22;
    }
done:
    return func_800672D8(&sp10, D_800E50A8);
}
