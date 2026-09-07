#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u32 word0;
    u32 word1;
} __attribute__((packed)) UA64;

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

typedef struct S_8009D3B0_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
} S_8009D3B0_0;   /* temp_t3 in func_8009D3B0 */

typedef struct S_8009D3B0_1 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_8009D3B0_1;   /* temp_t8 in func_8009D3B0 */

typedef struct S_8009D3B0_2 {
    u16 unk_00;
    u16 unk_02;
} S_8009D3B0_2;   /* var_a2 in func_8009D3B0 */

void func_8009D3B0(void) {
    UA64 sp10;
    s16 temp_a1;
    register s32 temp_t6 ASM_REG("$14");   /* MATCH pin: retail register colouring depends on it */
    register s32 bound_shifted ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s16 temp_v0_2;
    s32 var_a0;
    s16 var_a1;
    s16 var_a3;
    register s16 var_t2 ASM_REG("$10");   /* MATCH pin: load-bearing for the whole function shape */
    s16 var_v0_3;
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
    register s16 outer_end ASM_REG("$15");   /* MATCH pin: retail register colouring depends on it */
    u8 *var_a2;
    u8 temp_a0_2;
    u8 map_value;
    u8 *temp_t8;
    register s32 v1_role ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    register u8 *status ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s8 status_value;

    var_a2 = &D_80088CB0;
    sp10 = *(UA64 *)var_a2;
    v1_role = (s32)&D_80083160;
    temp_t8 = (u8 *)v1_role + 0x1DC;
    status = D_80082E80;
    status_value = ((s8 *)status)[0x26];
    if (status_value >= 0) {
        register u8 *temp_t3 ASM_REG("$11");   /* MATCH pin: load-bearing for the whole function shape */
        u8 *grid;
        u8 *map;
        s32 signed_row;
        s32 inner_bound;
        s32 outer_shifted;
        s32 inner_shifted;
        s32 row_shifted;
        s32 row_value;
        s32 signed_raw;
        s32 three;
        register s32 store_val ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        v1_role = status_value * 0x14;
        status = (u8 *)D_800E2970;
        temp_t3 = v1_role + status;
        v1_role = ((S_8009D3B0_0 *)temp_t3)->unk_02 - 1;
        var_t2 = v1_role;
        x_sum = ((S_8009D3B0_0 *)temp_t3)->unk_00 + ((S_8009D3B0_0 *)temp_t3)->unk_04;
        var_a0 = x_sum + 1;
        ASM_KEEP(x_sum);   /* MATCH pin: load-bearing for the whole function shape */
        temp_v0 = ((S_8009D3B0_0 *)temp_t3)->unk_06 + v1_role + 2;
        outer_end = temp_v0;
        if ((v1_role << 0x10) < (temp_v0 << 0x10)) {
            var_a3 = var_a0;
            bound_shifted = var_a0 << 0x10;
            temp_t6 = bound_shifted >> 0x10;
            grid = D_800EA000;
            map = D_800E50A8;
loop_3:
            temp_v0_2 = ((S_8009D3B0_0 *)temp_t3)->unk_00 - 1;
            var_a1 = temp_v0_2;
            if (temp_v0_2 < temp_t6) {
                ASM_KEEP(var_t2);   /* MATCH pin: retail keeps a computation the compiler would drop */
                var_v0_2 = var_a1 << 0x10;
                signed_raw = var_t2 << 0x10;
                signed_row = signed_raw >> 0x10;
                signed_raw = var_a3 << 0x10;
                inner_bound = signed_raw >> 0x10;
loop_5:
                row_shifted = var_a1 << 0x10;
                row_value = row_shifted >> 0x10;
                v1_role = (signed_row << ((S_8009D3B0_1 *)temp_t8)->unk_14) + row_value;
                var_a2 = (u8 *)((v1_role * 6) + (s32)grid);
                var_a0 = ((S_8009D3B0_2 *)var_a2)->unk_00;
                if (var_a0 != 0) {
                    ASM_KEEP(var_a1);   /* MATCH pin: retail keeps a computation the compiler would drop */
                    three = 3;
                    if (var_a0 != three) {
                        ASM_KEEP(v1_role);   /* MATCH pin: retail keeps a computation the compiler would drop */
                        var_v0_5 = v1_role / 2;
                        ASM_KEEP(v1_role);   /* MATCH pin: retail keeps a computation the compiler would drop */
                        v1_role = ((S_8009D3B0_2 *)var_a2)->unk_02;
                        var_a2 = (u8 *)(var_v0_5 + (s32)map);
                        status = (u8 *)((s16)(v1_role + 0x200) / 64);
                        var_a0 = (s32)status;
                        ASM_KEEP(status);   /* MATCH pin: retail register colouring depends on it */
                        v1_role = (s32)status;
                        if (v1_role >= 0x10) {
                            var_a0 = 15;
                            goto clamp_p;
                        }
                        var_v0_4 = var_a0 << 0x10;
                        if (v1_role <= 0) {
                            var_a0 = 1;
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
    u8 *negative_status;
    register s32 neg_store ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 neg_three;
    s16 var_v0_6;
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
    v1_role = ((s16) (negative_status[0x25] + *(u16 *)(temp_v0_4 + (s32)y_offsets)) << ((S_8009D3B0_1 *)temp_t8)->unk_14) + temp_a1;
    var_a2 = (u8 *)((v1_role * 6) + (s32)grid);
    neg_a0 = ((S_8009D3B0_2 *)var_a2)->unk_00;
    if (neg_a0 != 0) {
        ASM_KEEP(temp_a1);   /* MATCH pin: retail keeps a computation the compiler would drop */
        neg_three = 3;
        if (neg_a0 != neg_three) {
            ASM_KEEP(v1_role);   /* MATCH pin: retail keeps a computation the compiler would drop */
            var_v0_5 = v1_role / 2;
            ASM_KEEP(v1_role);   /* MATCH pin: retail keeps a computation the compiler would drop */
            v1_role = ((S_8009D3B0_2 *)var_a2)->unk_02;
            var_a2 = (u8 *)(var_v0_5 + (s32)map);
            status = (u8 *)((s16)(v1_role + 0x200) / 64);
            neg_a0 = (s32)status;
            ASM_KEEP(status);   /* MATCH pin: retail register colouring depends on it */
            v1_role = (s32)status;
            if (v1_role >= 0x10) {
                neg_a0 = 15;
                goto clamp_n;
            }
            var_v0_7 = neg_a0 << 0x10;
            if (v1_role <= 0) {
                neg_a0 = 1;
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
