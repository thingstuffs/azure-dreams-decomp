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

void func_80047738();
void func_800478B8();
s32 func_80069EF8();
u16 func_800A0818(u8, u8, u8, u8, s32 *);
M2C_UNK func_800A56E0();
M2C_UNK func_80164ED0();
M2C_UNK func_801655EC(void *, s16, s16, s16);
extern u8 D_80082E80[64];
extern s16 D_80083228[8];
extern u8 *D_800E3D7C[3];
extern s16 D_80173AFC[16];
extern void *D_80175D50[3];

void func_8016FC4C(void *arg0, void *arg1, void *arg2) {
    M2C_UNK sp18;
    s32 temp_s0;
    s16 temp_s0_2;
    s32 temp_s0_3;
    s16 temp_s1;
    s16 temp_s1_2;
    s32 temp_rand;
    s32 var_s0;
    s32 var_v0;
    s32 var_v1;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_5;
    s16 temp_v1_3;
    register u16 var_a0_4 ASM_REG("$4");
    u8 temp_v1_2;
    void *temp_s5;
    register void *entity ASM_REG("$19");
    register void *object ASM_REG("$20");
    void *temp_v0;
    void *temp_v1;
    void *var_a0;
    void *var_a0_2;
    void *var_a0_3;
    register u32 common_page ASM_REG("$2");
    register u32 table_page ASM_REG("$4");
    u16 table_angle;
    u32 table_ptr;
    register u8 temp_case4_state ASM_REG("$2");

    entity = arg1;
    object = arg2;
    var_s0 = 1;
    temp_s5 = D_80175D50[0] + 0x20;
    var_a0 = D_800E3D7C[0] + 4;
    do {
        temp_v0 = M2C_FIELD(var_a0, void **, 0xAC);
        if (temp_v0 != NULL) {
            temp_v1 = M2C_FIELD(temp_v0, void **, -0x14);
            M2C_FIELD(temp_v1, u16 *, 0x14) = (u16)(M2C_FIELD(temp_v1, u16 *, 0x14) & 0xFFBF);
        }
        var_s0 -= 1;
        var_a0 -= 4;
    } while (var_s0 >= 0);
    temp_v1_2 = M2C_FIELD(arg0, u8 *, 0x9A);
    switch (temp_v1_2) {
    case 0: {
        s32 step0;
        register s32 angle0 ASM_REG("$3");
        M2C_FIELD(temp_s5, u16 *, 0x2A) = func_800A0818(
            M2C_FIELD(object, u8 *, 0x24), M2C_FIELD(object, u8 *, 0x25),
            D_80082E80[0x24], D_80082E80[0x25], &sp18);
        M2C_FIELD(arg0, u16 *, 0x96) = (u16)(M2C_FIELD(arg0, u16 *, 0x96) + 1);
        temp_v0_2 = M2C_FIELD(object, u16 *, 0x1E);
        temp_v0_2 = (u16)(temp_v0_2 - 0x14);
        M2C_FIELD(object, u16 *, 0x1E) = temp_v0_2;
        ASM_SCHED_BARRIER();
        temp_v0_3 = M2C_FIELD(object, u16 *, 0x1C);
        angle0 = M2C_FIELD(object, volatile u16 *, 0x1E);
        temp_v0_3 = (u16)(temp_v0_3 - 0x14);
        ASM_KEEP(angle0);
        angle0 <<= 6;
        angle0 = 0 - angle0;
        M2C_FIELD(object, u16 *, 0x1C) = temp_v0_3;
        if (angle0 < 0) angle0 += 0xFFF;
        var_v1 = angle0;
        var_s0 = 0;
        step0 = var_v1 >> 0xC;
        ASM_KEEP(step0);
        var_a0_2 = arg0 - 0x20;
        do {
            func_80164ED0(var_a0_2, 0xFFFFFF, 0xE, 0, 0, step0);
            var_s0 += 1;
            var_a0_2 = arg0 - 0x20;
        } while (var_s0 < 6);
        if ((s16)M2C_FIELD(arg0, u16 *, 0x96) == 1) func_800A56E0(0xB1);
        var_v0 = ((s16)M2C_FIELD(arg0, u16 *, 0x96) < 120);
        goto block_84;
    }
    case 1: {
        s32 step1;
        M2C_FIELD(temp_s5, u16 *, 0x2A) = func_800A0818(
            M2C_FIELD(object, u8 *, 0x24), M2C_FIELD(object, u8 *, 0x25),
            D_80082E80[0x24], D_80082E80[0x25], &sp18);
        ASM_CLOBBER("$16");
        var_v0 = 0 - (M2C_FIELD(object, u16 *, 0x1E) << 6);
        var_s0 = 0;
        if (var_v0 < 0) var_v0 += 0xFFF;
        step1 = var_v0 >> 0xC;
        ASM_KEEP(step1);
        var_a0_3 = arg0 - 0x20;
        do {
            func_80164ED0(var_a0_3, 0xFFFFFF, 0xE, 0, 0, step1);
            var_s0 += 1;
            var_a0_3 = arg0 - 0x20;
        } while (var_s0 < 6);
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
        if (!(temp_v0_2 & 1)) {
            temp_s1 = (func_80069EF8(var_a0_3) & 0x1F) - 0xF;
            ASM_KEEP(temp_s1);
            temp_s1 = (s16)(((s32)temp_s1 << 16) >> 16);
            temp_s0 = (s16)((func_80069EF8() & 0x1F) - 0xF);
            func_801655EC(entity, temp_s1, temp_s0, (s16)((0 - (func_80069EF8() & 0x1F)) - 0xA));
        }
        if (!(M2C_FIELD(arg0, u16 *, 0x96) & 7)) func_800A56E0(0x817);
        var_v0 = ((s16)M2C_FIELD(arg0, u16 *, 0x96) < 20);
        goto block_84;
    }
    case 2:
        temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_3;
        if (!(temp_v0_3 & 7)) func_800A56E0(0x817);
        if (!(M2C_FIELD(arg0, u16 *, 0x96) & 1)) {
            temp_rand = func_80069EF8();
            temp_s1_2 = (temp_rand & 0x1F) - 0xF;
            ASM_KEEP(temp_s1_2);
            temp_s1_2 = (s16)(((s32)temp_s1_2 << 16) >> 16);
            temp_s0_2 = (func_80069EF8() & 0x1F) - 0xF;
            ASM_KEEP(temp_s0_2);
            temp_s0_2 = (s16)(((s32)temp_s0_2 << 16) >> 16);
            func_801655EC(entity, temp_s1_2, temp_s0_2, (s16)((0 - (func_80069EF8() & 0x1F)) - 0xA));
            goto common_tail;
        }
        goto common_tail;
    case 4:
        temp_v0_4 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_4;
        if (((s16)temp_v0_4 == 3) || ((s16)temp_v0_4 == 6) || ((s16)temp_v0_4 == 9) || ((s16)temp_v0_4 == 0xC)) {
            var_a0_4 = M2C_FIELD(temp_s5, u16 *, 0x2A);
            temp_v1_3 = var_a0_4 - 0x200;
            ASM_KEEP(var_a0_4);
            ASM_KEEP(temp_v1_3);
            if (temp_v1_3 < 0) var_a0_4 = temp_v1_3 + 0x1000;
            else var_a0_4 = temp_v1_3;
            M2C_FIELD(temp_s5, u16 *, 0x2A) = var_a0_4;
        }
        if ((s16)M2C_FIELD(arg0, u16 *, 0x96) < 0xE) goto common_tail;
        temp_case4_state = M2C_FIELD(arg0, u8 *, 0x9A);
        ASM_KEEP(temp_case4_state);
        table_page = 0x80170000U;
        ASM_KEEP(table_page);
        M2C_FIELD(arg0, u16 *, 0x96) = 0U;
        ASM_KEEP(temp_case4_state);
        temp_case4_state = (u8)(temp_case4_state + 1);
        M2C_FIELD(arg0, u8 *, 0x9A) = temp_case4_state;
        table_angle = M2C_FIELD(temp_s5, u16 *, 0x2A);
        ASM_SCHED_BARRIER();
        table_page += 0x3AFC;
        ASM_KEEP(table_page);
        table_ptr = ((table_angle >> 7) & 0x1C);
        table_ptr += table_page;
        M2C_FIELD(entity, s32 *, 0xC) = (s32)(M2C_FIELD((u8 *)table_ptr, s16 *, 0) * 0x30000);
        table_ptr = (((u16)M2C_FIELD(temp_s5, u16 *, 0x2A) >> 7) & 0x1C);
        table_ptr += table_page;
        M2C_FIELD(entity, s32 *, 0x10) = (s32)(M2C_FIELD((u8 *)table_ptr, s16 *, 2) * 0x30000);
        goto common_tail;
    case 5:
        M2C_FIELD(entity, s32 *, 0) = (s32)(M2C_FIELD(entity, s32 *, 0) + M2C_FIELD(entity, s32 *, 0xC));
        M2C_FIELD(entity, s32 *, 4) = (s32)(M2C_FIELD(entity, s32 *, 4) + M2C_FIELD(entity, s32 *, 0x10));
        temp_v0_5 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_5;
        if ((s16)temp_v0_5 < 6) goto common_tail;
        M2C_FIELD(arg0, u16 *, 0x96) = 0U;
        M2C_FIELD(arg0, u8 *, 0x9A) = (u8)(M2C_FIELD(arg0, u8 *, 0x9A) + 1);
        goto common_tail;
    block_84:
        if (var_v0 != 0) goto common_tail;
        M2C_FIELD(arg0, u8 *, 0x9A) = (u8)(M2C_FIELD(arg0, u8 *, 0x9A) + 1);
        M2C_FIELD(arg0, u16 *, 0x96) = 0U;
        goto common_tail;
    case 7:
        M2C_FIELD(object, u16 *, 0x14) = (u16)(M2C_FIELD(object, u16 *, 0x14) | 0x80);
        M2C_FIELD(entity, s16 *, 6) = 1;
        M2C_FIELD(entity, s16 *, 2) = 1;
        goto common_tail;
    default:
        goto common_tail;
    }
common_tail:
    common_page = 0x80170000;
    ASM_KEEP(common_page);
    if (M2C_FIELD((u8 *)common_page, void **, 0x5D50) != 0) {
        register s32 compare_state ASM_REG("$3");
        s32 current_state;
        common_page = 0x80080000U;
        ASM_KEEP(common_page);
        common_page = (u32)(s32)M2C_FIELD((u8 *)common_page, s16 *, 0x3228);
        ASM_KEEP(common_page);
        temp_s0_3 = (((s32)common_page + (s16)M2C_FIELD(temp_s5, u16 *, 0x2A) + 0x100) >> 9) & 7;
        current_state = M2C_FIELD(arg0, s16 *, 0x94);
        ASM_SCHED_BARRIER();
        compare_state = temp_s0_3;
        ASM_KEEP(compare_state);
        if (current_state != compare_state) {
            func_80047738(object, *(M2C_FIELD(object, u8 **, 0x2C) + compare_state), M2C_FIELD(object, s8 *, 4));
            M2C_FIELD(arg0, s16 *, 0x94) = temp_s0_3;
        }
        func_800478B8(object);
    }
}
