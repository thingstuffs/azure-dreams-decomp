#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CA1E0_0 {
    u8 pad_00[0x24];
    union { u8 s; volatile u8 u; } unk_24;   /* accessed as both */
    union { u8 s; volatile u8 u; } unk_25;   /* accessed as both */
    s8 unk_26;
} S_800CA1E0_0;   /* temp_s2 in func_800CA1E0 */

typedef struct S_800CA1E0_1 {
    u8 pad_00[0x14];
    s16 unk_14;
    s16 unk_16;
} S_800CA1E0_1;   /* temp_table in func_800CA1E0 */

typedef struct S_800CA1E0_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
} S_800CA1E0_2;   /* temp_arg2 in func_800CA1E0 */

typedef struct S_800CA1E0_3 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_800CA1E0_3;   /* (void *)temp_e_index in func_800CA1E0 */


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
    s32 temp_a0;
    s32 temp_s5;
    register s32 temp_s0 ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 temp_s1;
    register s32 temp_s4 ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 temp_index;
    s32 temp_raw_byte;
    register s32 temp_raw_half ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 temp_v1 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 temp_a1;
    s32 temp_a2;
    void *temp_a3;
    register u16 temp_entry_a3 ASM_REG("$7");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 temp_e_index;
    register u16 *temp_ccd8_base ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register u16 *temp_fp;
    u16 *temp_s6;
    u16 *temp_dceac_page;
    u16 *temp_dcebc_page;
    register u16 temp_s7 ASM_REG("$23");   /* MATCH pin: load-bearing for the whole function shape */
    register u32 temp_table_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 temp_tail_value;
    u32 temp_v0;
    register u32 temp_v1_3 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 temp_result ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register u16 temp_arg3_copy ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register S_800CA1E0_0 *temp_s2 ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register S_800CA1E0_2 *temp_arg2 ASM_REG("$8");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u8 *temp_table;
    s32 final_value;
    void *var_a1;

    var_a1 = arg1;
    temp_s2 = var_a1;
    ASM_KEEP_NV(temp_s2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_entry_a3 = arg3;
    ASM_KEEP_NV(temp_entry_a3);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    temp_a0 = (arg0 >> 9) & 7;
    temp_s5 = temp_a0;
    ASM_KEEP_NV(temp_s5);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    temp_ccd8_base = D_8006CCD8;
    temp_index = temp_s5 << 1;
    ASM_KEEP_NV(temp_index);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    temp_fp = (u16 *)((u32)temp_index + (u32)temp_ccd8_base);
    temp_raw_byte = temp_s2->unk_24.s;
    temp_raw_half = *temp_fp;
    ASM_KEEP_NV(temp_s5);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_CLOBBER("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    temp_a0 = temp_s5;
    ASM_KEEP_NV(temp_a0);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    sp18 = temp_entry_a3;
    temp_s1 = temp_raw_byte + temp_raw_half;
    temp_table_page = 0x80080000;
    ASM_KEEP_DEP_NV(temp_table_page, temp_s1);   /* MATCH pin: retail immediate-load split depends on it */
    temp_v1 = temp_s1 & 0xFFFF;
    temp_table = (u8 *)(temp_table_page + 0x333C);
    if (temp_v1 == 0) {
        goto block_tail;
    }
    ASM_KEEP_NV(temp_table);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    var_a1 = (void *)1;
    if (((1 << ((S_800CA1E0_1 *)temp_table)->unk_14) - 1) < temp_v1) {
        return -1;
    }
    temp_ccd8_base = D_8006CCE8;
    temp_s6 = (u16 *)((u32)temp_index + (u32)temp_ccd8_base);
    temp_raw_byte = temp_s2->unk_25.s;
    temp_raw_half = *temp_s6;
    temp_s0 = temp_raw_byte + temp_raw_half;
    temp_v1 = temp_s0 & 0xFFFF;
    if (temp_v1 == 0) {
        return -1;
    }
    if (!(((1 << ((S_800CA1E0_1 *)temp_table)->unk_16) - 1) < temp_v1)) {
        goto block_body;
    }
block_tail:
    temp_tail_value = -1;
    ASM_TAILSLOT_PIN_TIED(temp_tail_value);   /* MATCH pin: retail delay-slot contents depend on it */
    return func_800CA410(temp_a0, var_a1, temp_table);
block_body:
    temp_v1_3 = temp_s2->unk_24.u;
    temp_v0 = temp_s2->unk_25.u;
    temp_arg2 = arg2;
    temp_v1_3 <<= 6;
    ASM_KEEP_NV(temp_v1_3);   /* MATCH pin: load-bearing for the whole function shape */
    temp_a1 = temp_v1_3 >> 6;
    ASM_KEEP_NV(temp_a1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_v0 <<= 6;
    ASM_KEEP_NV(temp_v0);   /* MATCH pin: load-bearing for the whole function shape */
    temp_a2 = temp_v0 >> 6;
    ASM_KEEP_NV(temp_a2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_s0 = temp_v1_3 + 0x20;
    temp_s7 = temp_arg2->unk_88;
    temp_s4 = temp_v0 + 0x20;
    if ((func_8009A540(temp_a0, temp_a1, temp_a2, (s16) (temp_s7 - temp_entry_a3)) << 0x10) == 0) {
        goto block_body_tail;
    }
    temp_a2 = temp_s5;
    ASM_KEEP_NV(temp_a2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_a3 = &sp10;
    ASM_KEEP_NV(temp_a3);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_dceac_page = D_800DCEAC;
    temp_dceac_page = (u16 *)((u32)temp_index + (u32)temp_dceac_page);
    ASM_KEEP_NV(temp_dceac_page);   /* MATCH pin: retail immediate-load split depends on it */
    temp_dcebc_page = D_800DCEBC;
    temp_dcebc_page = (u16 *)((u32)temp_index + (u32)temp_dcebc_page);
    ASM_KEEP_NV(temp_dcebc_page);   /* MATCH pin: retail immediate-load split depends on it */
    temp_a0 = temp_s2->unk_24.s;
    ASM_KEEP_NV(temp_a0);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    temp_a1 = temp_s2->unk_25.s;
    ASM_KEEP_NV(temp_a1);   /* MATCH pin: retail schedule: same instructions, different order without it */
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
    ASM_TAILSLOT_PIN_TIED(temp_tail_value);   /* MATCH pin: retail delay-slot contents depend on it */
    return func_800CA410();
block_body_continue:
    if (temp_s2->unk_26 < 0) {
        temp_a0 = func_8009FB34((temp_s2->unk_24.s + *temp_fp) & 0xFFFF, (temp_s2->unk_25.s + *temp_s6) & 0xFFFF);
        if (temp_a0 >= 0) {
            temp_e_index = temp_a0 << 2;
            temp_ccd8_base = (u16 *)D_800E2970;
            temp_e_index = (temp_e_index + temp_a0) << 2;
            temp_e_index = temp_e_index + (u32)temp_ccd8_base;
            ASM_KEEP_NV(temp_e_index);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
            temp_a0 = temp_s1 & 0xFFFF;
            if (!(((S_800CA1E0_3 *)((void *)temp_e_index))->unk_0C & 2)) {
                goto block_final;
            }
            temp_arg2 = arg2;
            if (!(temp_arg2->unk_1C & 0x2000)) {
                goto block_body_tail;
            }
        }
    }
    temp_a0 = temp_s1 & 0xFFFF;
block_final:
    temp_arg3_copy = sp18;
    ASM_KEEP_NV(temp_arg3_copy);   /* MATCH pin: retail register colouring depends on it */
    final_value = (s16)func_800BCB04(temp_a0, temp_s0 & 0xFFFF, (s16) (temp_s7 - temp_arg3_copy));
    temp_result = -1;
    if (final_value < 0x201) {
        temp_result = 1;
    }
    return temp_result;
}
