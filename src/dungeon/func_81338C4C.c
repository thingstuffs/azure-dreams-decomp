/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_8016FC4C_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8016FC4C_0;   /* var_a0 in func_8016FC4C */

typedef struct S_8016FC4C_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8016FC4C_1_pre;   /* the 0x14 bytes before temp_v0 in func_8016FC4C, addressed as temp_v0[-1] */

typedef struct S_8016FC4C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8016FC4C_2;   /* temp_v1 in func_8016FC4C */

typedef struct S_8016FC4C_3 {
    u8 pad_00[0x94];
    s16 unk_94;
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} S_8016FC4C_3;   /* arg0 in func_8016FC4C */

typedef struct S_8016FC4C_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8016FC4C_4;   /* temp_s5 in func_8016FC4C */

typedef struct S_8016FC4C_5 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    union { u16 s; volatile u16 u; } unk_1E;   /* accessed as both */
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8016FC4C_5;   /* object in func_8016FC4C */

typedef struct S_8016FC4C_6 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_8016FC4C_6;   /* entity in func_8016FC4C */

typedef struct S_8016FC4C_7 {
    s16 unk_00;
    s16 unk_02;
} S_8016FC4C_7;   /* (u8 *)table_ptr in func_8016FC4C */

typedef struct S_8016FC4C_8 {
    u8 pad_00[0x3228];
    s16 unk_3228;
    u8 pad_322A[0x2B26];
    void * unk_5D50;
} S_8016FC4C_8;   /* (u8 *)common_page in func_8016FC4C */


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
    register u16 var_a0_4 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    u8 temp_v1_2;
    S_8016FC4C_4 *temp_s5;
    S_8016FC4C_6 *entity;
    register S_8016FC4C_5 *object ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */
    void *temp_v0;
    S_8016FC4C_2 *temp_v1;
    void *var_a0;
    void *var_a0_2;
    void *var_a0_3;
    register u32 common_page ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    u32 table_page;
    u16 table_angle;
    u32 table_ptr;
    u8 temp_case4_state;

    entity = arg1;
    object = arg2;
    var_s0 = 1;
    temp_s5 = D_80175D50[0] + 0x20;
    var_a0 = D_800E3D7C[0] + 4;
    do {
        temp_v0 = ((S_8016FC4C_0 *)var_a0)->unk_AC;
        if (temp_v0 != NULL) {
            temp_v1 = ((S_8016FC4C_1_pre *)temp_v0)[-1].unk_00;
            temp_v1->unk_14 = (u16)(temp_v1->unk_14 & 0xFFBF);
        }
        var_s0 -= 1;
        var_a0 -= 4;
    } while (var_s0 >= 0);
    temp_v1_2 = ((S_8016FC4C_3 *)arg0)->unk_9A;
    switch (temp_v1_2) {
    case 0: {
        s32 step0;
        s32 angle0;
        temp_s5->unk_2A = func_800A0818(
            object->unk_24, object->unk_25,
            D_80082E80[0x24], D_80082E80[0x25], &sp18);
        ((S_8016FC4C_3 *)arg0)->unk_96 = (u16)(((S_8016FC4C_3 *)arg0)->unk_96 + 1);
        temp_v0_2 = object->unk_1E.s;
        temp_v0_2 = (u16)(temp_v0_2 - 0x14);
        object->unk_1E.s = temp_v0_2;
        temp_v0_3 = object->unk_1C;
        angle0 = object->unk_1E.u;
        temp_v0_3 = (u16)(temp_v0_3 - 0x14);
        angle0 <<= 6;
        angle0 = 0 - angle0;
        object->unk_1C = temp_v0_3;
        if (angle0 < 0) angle0 += 0xFFF;
        var_v1 = angle0;
        var_s0 = 0;
        step0 = var_v1 >> 0xC;
        var_a0_2 = arg0 - 0x20;
        do {
            func_80164ED0(var_a0_2, 0xFFFFFF, 0xE, 0, 0, step0);
            var_s0 += 1;
            var_a0_2 = arg0 - 0x20;
        } while (var_s0 < 6);
        if ((s16)((S_8016FC4C_3 *)arg0)->unk_96 == 1) func_800A56E0(0xB1);
        var_v0 = ((s16)((S_8016FC4C_3 *)arg0)->unk_96 < 120);
        goto block_84;
    }
    case 1: {
        s32 step1;
        temp_s5->unk_2A = func_800A0818(
            object->unk_24, object->unk_25,
            D_80082E80[0x24], D_80082E80[0x25], &sp18);
        ASM_CLOBBER("$16");   /* MATCH pin: load-bearing for the whole function shape */
        var_v0 = 0 - (object->unk_1E.s << 6);
        var_s0 = 0;
        if (var_v0 < 0) var_v0 += 0xFFF;
        step1 = var_v0 >> 0xC;
        var_a0_3 = arg0 - 0x20;
        do {
            func_80164ED0(var_a0_3, 0xFFFFFF, 0xE, 0, 0, step1);
            var_s0 += 1;
            var_a0_3 = arg0 - 0x20;
        } while (var_s0 < 6);
        temp_v0_2 = ((S_8016FC4C_3 *)arg0)->unk_96 + 1;
        ((S_8016FC4C_3 *)arg0)->unk_96 = temp_v0_2;
        if (!(temp_v0_2 & 1)) {
            temp_s1 = (func_80069EF8(var_a0_3) & 0x1F) - 0xF;
            temp_s1 = (s16)(((s32)temp_s1 << 16) >> 16);
            temp_s0 = (s16)((func_80069EF8() & 0x1F) - 0xF);
            func_801655EC(entity, temp_s1, temp_s0, (s16)((0 - (func_80069EF8() & 0x1F)) - 0xA));
        }
        if (!(((S_8016FC4C_3 *)arg0)->unk_96 & 7)) func_800A56E0(0x817);
        var_v0 = ((s16)((S_8016FC4C_3 *)arg0)->unk_96 < 20);
        goto block_84;
    }
    case 2:
        temp_v0_3 = ((S_8016FC4C_3 *)arg0)->unk_96 + 1;
        ((S_8016FC4C_3 *)arg0)->unk_96 = temp_v0_3;
        if (!(temp_v0_3 & 7)) func_800A56E0(0x817);
        if (!(((S_8016FC4C_3 *)arg0)->unk_96 & 1)) {
            temp_rand = func_80069EF8();
            temp_s1_2 = (temp_rand & 0x1F) - 0xF;
            temp_s1_2 = (s16)(((s32)temp_s1_2 << 16) >> 16);
            temp_s0_2 = (func_80069EF8() & 0x1F) - 0xF;
            temp_s0_2 = (s16)(((s32)temp_s0_2 << 16) >> 16);
            func_801655EC(entity, temp_s1_2, temp_s0_2, (s16)((0 - (func_80069EF8() & 0x1F)) - 0xA));
            goto common_tail;
        }
        goto common_tail;
    case 4:
        temp_v0_4 = ((S_8016FC4C_3 *)arg0)->unk_96 + 1;
        ((S_8016FC4C_3 *)arg0)->unk_96 = temp_v0_4;
        if (((s16)temp_v0_4 == 3) || ((s16)temp_v0_4 == 6) || ((s16)temp_v0_4 == 9) || ((s16)temp_v0_4 == 0xC)) {
            var_a0_4 = temp_s5->unk_2A;
            temp_v1_3 = var_a0_4 - 0x200;
            ASM_KEEP(var_a0_4);   /* MATCH pin: retail branch polarity depends on it */
            if (temp_v1_3 < 0) var_a0_4 = temp_v1_3 + 0x1000;
            else var_a0_4 = temp_v1_3;
            temp_s5->unk_2A = var_a0_4;
        }
        if ((s16)((S_8016FC4C_3 *)arg0)->unk_96 < 0xE) goto common_tail;
        temp_case4_state = ((S_8016FC4C_3 *)arg0)->unk_9A;
        ASM_KEEP(temp_case4_state);   /* MATCH pin: retail schedule: same instructions, different order without it */
        table_page = 0x80170000U;
        ASM_KEEP(table_page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ((S_8016FC4C_3 *)arg0)->unk_96 = 0U;
        ASM_KEEP(temp_case4_state);   /* MATCH pin: retail schedule: same instructions, different order without it */
        temp_case4_state = (u8)(temp_case4_state + 1);
        ((S_8016FC4C_3 *)arg0)->unk_9A = temp_case4_state;
        table_angle = temp_s5->unk_2A;
        table_page += 0x3AFC;
        table_ptr = ((table_angle >> 7) & 0x1C);
        table_ptr += table_page;
        entity->unk_0C = (s32)(((S_8016FC4C_7 *)((u8 *)table_ptr))->unk_00 * 0x30000);
        table_ptr = (((u16)temp_s5->unk_2A >> 7) & 0x1C);
        table_ptr += table_page;
        entity->unk_10 = (s32)(((S_8016FC4C_7 *)((u8 *)table_ptr))->unk_02 * 0x30000);
        goto common_tail;
    case 5:
        entity->unk_00.at00.v = (s32)(entity->unk_00.at00.v + entity->unk_0C);
        entity->unk_04.at00.v = (s32)(entity->unk_04.at00.v + entity->unk_10);
        temp_v0_5 = ((S_8016FC4C_3 *)arg0)->unk_96 + 1;
        ((S_8016FC4C_3 *)arg0)->unk_96 = temp_v0_5;
        if ((s16)temp_v0_5 < 6) goto common_tail;
        ((S_8016FC4C_3 *)arg0)->unk_96 = 0U;
        ((S_8016FC4C_3 *)arg0)->unk_9A = (u8)(((S_8016FC4C_3 *)arg0)->unk_9A + 1);
        goto common_tail;
    block_84:
        if (var_v0 != 0) goto common_tail;
        ((S_8016FC4C_3 *)arg0)->unk_9A = (u8)(((S_8016FC4C_3 *)arg0)->unk_9A + 1);
        ((S_8016FC4C_3 *)arg0)->unk_96 = 0U;
        goto common_tail;
    case 7:
        object->unk_14 = (u16)(object->unk_14 | 0x80);
        entity->unk_04.at02.v = 1;
        entity->unk_00.at02.v = 1;
        goto common_tail;
    default:
        goto common_tail;
    }
common_tail:
    common_page = 0x80170000;
    ASM_KEEP(common_page);   /* MATCH pin: load-bearing for the whole function shape */
    if (((S_8016FC4C_8 *)((u8 *)common_page))->unk_5D50 != 0) {
        s32 compare_state;
        s32 current_state;
        common_page = 0x80080000U;
        ASM_KEEP(common_page);   /* MATCH pin: load-bearing for the whole function shape */
        common_page = (u32)(s32)((S_8016FC4C_8 *)((u8 *)common_page))->unk_3228;
        temp_s0_3 = (((s32)common_page + (s16)temp_s5->unk_2A + 0x100) >> 9) & 7;
        current_state = ((S_8016FC4C_3 *)arg0)->unk_94;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
        compare_state = temp_s0_3;
        ASM_KEEP(compare_state);   /* MATCH pin: load-bearing for the whole function shape */
        if (current_state != compare_state) {
            func_80047738(object, *(object->unk_2C + compare_state), object->unk_04);
            ((S_8016FC4C_3 *)arg0)->unk_94 = temp_s0_3;
        }
        func_800478B8(object);
    }
}
