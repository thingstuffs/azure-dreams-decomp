/* cfail-repair: true-name warm-start */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_801690D8_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x15];
    u16 unk_18;
    u16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    s32 unk_24;
    u8 pad_28[0x34];
    union { s32 s; volatile s32 u; } unk_5C;   /* accessed as both */
    s32 unk_60;
    u8 pad_64[0x10];
    u16 unk_74;
    u16 unk_76;
    u16 unk_78;
    u16 unk_7A;
    u16 unk_7C;
    u16 unk_7E;
    u16 unk_80;
    u16 unk_82;
    u16 unk_84;
    u16 unk_86;
    u16 unk_88;
    u16 unk_8A;
} S_801690D8_0;   /* temp_s0 in func_801690D8 */

typedef struct S_801690D8_1 {
    u8 pad_00[0x96];
    u16 unk_96;
} S_801690D8_1;   /* arg0_in in func_801690D8 */

typedef struct S_801690D8_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_801690D8_2;   /* temp_v0 in func_801690D8 */

typedef struct S_801690D8_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_801690D8_3;   /* temp_a0 in func_801690D8 */

typedef struct S_801690D8_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801690D8_4;   /* temp_a0_2 in func_801690D8 */

typedef struct S_801690D8_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801690D8_5;   /* arg1_reg in func_801690D8 */

typedef struct S_801690D8_6 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_801690D8_6;   /* arg0_work in func_801690D8 */

typedef struct S_801690D8_7 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_801690D8_7;   /* temp_a0_3 in func_801690D8 */

typedef struct {
    u8 bytes[32];
} Copy32;

extern void func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern M2C_UNK D_80045340[3];
extern M2C_UNK D_800DEAE0[3];
extern Copy32 D_801648DC;
extern M2C_UNK D_80168C88[3];
extern u8 D_80175DD8[96];

void func_801690D8(S_801690D8_1 *arg0_in, void *arg1, s32 arg2, s32 arg3) {
    s32 sp10[8];
    s32 var_s1;
    s32 var_s6;
    s32 temp_a2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a1_4;
    S_801690D8_3 *temp_a0;
    S_801690D8_4 *temp_a0_2;
    S_801690D8_7 *temp_a0_3;
    S_801690D8_0 *temp_s0;
    void *temp_v0;
    S_801690D8_6 *arg0_work;
    s32 *stack_base;
    u16 *coeff_ptr;
    u8 *table_base;
    S_801690D8_5 *arg1_reg;

    arg1_reg = arg1;
    arg0_work = arg0_in;
    *(Copy32 *)sp10 = D_801648DC;
    var_s1 = 0;
    stack_base = sp10;
    var_s6 = 0xFFFF;
    table_base = D_80175DD8;
    do {
        temp_v0 = func_8003FC64(0x12);
        temp_s0 = temp_v0 + 0x20;
        if (temp_v0 != NULL) {
            temp_s0->unk_18 = 0xEU;
            if ((var_s1 == 0) || (var_s1 == 7)) {
                temp_s0->unk_18 = 8U;
            }
            if ((var_s1 == 1) || (var_s1 == 6)) {
                temp_s0->unk_18 = (s16) (temp_s0->unk_18 - 4);
            }
            if ((var_s1 == 2) || (var_s1 == 5)) {
                temp_s0->unk_18 = (u16) (temp_s0->unk_18 - 2);
            }
            temp_s0->unk_1A = (u16) arg0_in->unk_96;
            temp_s0->unk_1C = var_s1;
            temp_s0->unk_1E = 0;
            temp_s0->unk_24 = arg3;
            ((S_801690D8_2 *)temp_v0)->unk_10 = &D_80168C88;
            func_8004491C(temp_v0, &D_80045340);
            temp_a0 = ((S_801690D8_2 *)temp_v0)->unk_0C;
            temp_a0->unk_10 = 0x20;
            temp_a0->unk_14 = (u16) (temp_a0->unk_14 | 0x8C);
            temp_a0_2 = ((S_801690D8_2 *)temp_v0)->unk_08;
            temp_a0_2->unk_00 = (s32) arg1_reg->unk_00;
            temp_a0_2->unk_04 = (s32) arg1_reg->unk_04;
            temp_a0_2->unk_08 = (s32) (arg1_reg->unk_08 + 0xFFC80000);
            temp_s0->unk_8A = 0U;
            temp_s0->unk_84 = 0U;
            temp_s0->unk_7E = 0U;
            temp_s0->unk_78 = 0U;
            temp_s0->unk_88 = 0U;
            temp_s0->unk_82 = 0U;
            temp_s0->unk_86 = 0U;
            temp_s0->unk_80 = 0U;
            temp_s0->unk_74 = (u16) (M2C_FIELD(stack_base, s16 *, (((u16) arg0_work->unk_2A >> 7) & 0x1C)) * 0xF);
            temp_s0->unk_7A = (u16) (M2C_FIELD(stack_base, s16 *, (((u16) arg0_work->unk_2A >> 7) & 0x1C)) * 0xF);
            temp_s0->unk_76 = (u16) ((s16) *(volatile u16 *)(((s8 *) stack_base + (((u16) arg0_work->unk_2A >> 7) & 0x1C)) + 2) * 0xF);
            temp_s0->unk_7C = (u16) ((s16) *(volatile u16 *)(((s8 *) stack_base + (((u16) arg0_work->unk_2A >> 7) & 0x1C)) + 2) * 0xF);
            temp_a2 = var_s1 - 1;
            temp_s0->unk_5C.s = M2C_FIELD(stack_base, s16 *, ((((s32) (arg0_work->unk_2A << 0x10) >> 0x19) + 6) & 7) << 2) * 0x3333;
            coeff_ptr = (u16 *)((s8 *)stack_base + (((((s32) (arg0_work->unk_2A << 0x10) >> 0x19) + 6) & 7) << 2));
            temp_s0->unk_60 = (s32) ((s16) coeff_ptr[1] * 0x3333);
            var_a1 = temp_s0->unk_5C.s * temp_a2;
            if (var_a1 < 0) {
                var_a1 += var_s6;
            }
            var_a0 = temp_s0->unk_5C.u * temp_a2;
            temp_s0->unk_7A = (u16) (temp_s0->unk_7A + (var_a1 >> 0x10));
            if (var_a0 < 0) {
                var_a0 += var_s6;
            }
            var_a1_2 = temp_s0->unk_60 * temp_a2;
            temp_s0->unk_86 = (u16) (temp_s0->unk_86 + (var_a0 >> 0x10));
            if (var_a1_2 < 0) {
                var_a1_2 += var_s6;
            }
            var_a0_2 = temp_s0->unk_60 * temp_a2;
            temp_s0->unk_7C = (u16) (temp_s0->unk_7C + (var_a1_2 >> 0x10));
            if (var_a0_2 < 0) {
                var_a0_2 += var_s6;
            }
            var_a1_3 = temp_s0->unk_5C.s * var_s1;
            temp_s0->unk_88 = (u16) (temp_s0->unk_88 + (var_a0_2 >> 0x10));
            if (var_a1_3 < 0) {
                var_a1_3 += var_s6;
            }
            var_a0_3 = temp_s0->unk_5C.s * var_s1;
            temp_s0->unk_74 = (u16) (temp_s0->unk_74 + (var_a1_3 >> 0x10));
            if (var_a0_3 < 0) {
                var_a0_3 += var_s6;
            }
            var_a1_4 = temp_s0->unk_60 * var_s1;
            temp_s0->unk_80 = (u16) (temp_s0->unk_80 + (var_a0_3 >> 0x10));
            if (var_a1_4 < 0) {
                var_a1_4 += var_s6;
            }
            var_a0_4 = temp_s0->unk_60 * var_s1;
            temp_s0->unk_76 = (u16) (temp_s0->unk_76 + (var_a1_4 >> 0x10));
            if (var_a0_4 < 0) {
                var_a0_4 += var_s6;
            }
            temp_s0->unk_82 = (u16) (temp_s0->unk_82 + (var_a0_4 >> 0x10));
            temp_a0_3 = ((S_801690D8_2 *)temp_v0)->unk_0C;
            temp_a0_3->unk_1E = 0x1000;
            temp_a0_3->unk_1C = 0x1000;
            temp_a0_3->unk_0D = 0x60U;
            temp_s0->unk_00 = (
                temp_a0_3->unk_0C = 0xF0U,
                temp_a0_3->unk_0E = 0xFFU,
                temp_a0_3->unk_0C);
            temp_s0->unk_01 = (u8) temp_a0_3->unk_0D;
            temp_s0->unk_02 = (u8) temp_a0_3->unk_0E;
            func_8003DB94(temp_a0_3, &D_800DEAE0, 0);
            M2C_FIELD(((temp_s0->unk_1C * 0x60) + table_base), u16 *, 0) = temp_s0->unk_80;
            M2C_FIELD(((temp_s0->unk_1C * 0x60) + table_base), u16 *, 2) = (u16) temp_s0->unk_82;
            M2C_FIELD(((temp_s0->unk_1C * 0x60) + table_base), u16 *, 4) = (u16) temp_s0->unk_84;
            M2C_FIELD(((temp_s0->unk_1C * 0x60) + table_base), u16 *, 6) = (u16) temp_s0->unk_86;
            M2C_FIELD(((temp_s0->unk_1C * 0x60) + table_base), u16 *, 8) = (u16) temp_s0->unk_88;
            M2C_FIELD(((temp_s0->unk_1C * 0x60) + table_base), u16 *, 0xA) = (u16) temp_s0->unk_8A;
            M2C_FIELD(((temp_s0->unk_1C * 0x60) + table_base), u16 *, 0x54) = (u16) temp_s0->unk_74;
            M2C_FIELD(((temp_s0->unk_1C * 0x60) + table_base), u16 *, 0x56) = (u16) temp_s0->unk_76;
            M2C_FIELD(((temp_s0->unk_1C * 0x60) + table_base), u16 *, 0x58) = (u16) temp_s0->unk_78;
            M2C_FIELD(((temp_s0->unk_1C * 0x60) + table_base), u16 *, 0x5A) = (u16) temp_s0->unk_7A;
            M2C_FIELD(((temp_s0->unk_1C * 0x60) + table_base), u16 *, 0x5C) = (u16) temp_s0->unk_7C;
            M2C_FIELD(((temp_s0->unk_1C * 0x60) + table_base), u16 *, 0x5E) = (u16) temp_s0->unk_7E;
        }
        var_s1 += 1;
    } while (var_s1 < 8);
}
