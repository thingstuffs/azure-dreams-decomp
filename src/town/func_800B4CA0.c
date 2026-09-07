/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B2400_8 {
    u8 pad_00[0x3C];
    s32 unk_3C;
} S_800B2400_8;   /* ((temp_v1 * 4) + arg0) in func_800B2400 */

typedef struct S_800B2400_9 {
    u8 pad_00[0x3C];
    s32 unk_3C;
} S_800B2400_9;   /* ((((S_800B2400_0 *)arg0)->unk_18 * 4) + arg0) in func_800B2400 */

typedef struct S_800B2400_10 {
    u8 pad_00[0x3C];
    s32 unk_3C;
} S_800B2400_10;   /* ((temp_v1_2 * 4) + arg0) in func_800B2400 */

typedef struct S_800B2400_11 {
    s32 unk_00;
} S_800B2400_11;   /* (temp_a0->unk_24 * 4) + ((S_800B2400_8 *)(((temp_v1 * 4) + arg0)))->unk_3C in func_800B2400 */




typedef struct {
    s32 value;
} __attribute__((packed)) M2C_UNALIGNED_WORD;

s32 func_800B2130();
M2C_UNK func_800B2190();
M2C_UNK *func_800B2280();
M2C_UNK func_800B23C0();
s32 func_800B25B4();
s32 func_800B29A4();

typedef struct S_800B2400_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
    s32 unk_18;
} S_800B2400_0;   /* arg0 in func_800B2400 */

typedef struct S_800B2400_1 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_800B2400_1;   /* temp_v1_5 in func_800B2400 */

typedef struct S_800B2400_2 {
    u8 pad_00[0x24];
    s32 unk_24;
    s32 unk_28;
} S_800B2400_2;   /* temp_a0 in func_800B2400 */

typedef struct S_800B2400_3 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800B2400_3;   /* temp_s2 in func_800B2400 */

typedef struct S_800B2400_4 {
    M2C_UNK * unk_00;
    s32 unk_04;
} S_800B2400_4;   /* temp_s0 in func_800B2400 */

typedef struct S_800B2400_5 {
    u8 pad_00[0x24];
    s32 unk_24;
} S_800B2400_5;   /* temp_sp in func_800B2400 */

typedef struct S_800B2400_6 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_800B2400_6;   /* temp_v1_3 in func_800B2400 */

typedef struct S_800B2400_7 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_800B2400_7;   /* temp_v1_4 in func_800B2400 */

s32 func_800B2400(void *arg0) {
    M2C_UNK *temp_v0_2;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_v1;
    u8 temp_byte;
    S_800B2400_2 *temp_a0;
    S_800B2400_4 *temp_s0;
    S_800B2400_3 *temp_s2;
    S_800B2400_1 *temp_v1_5;
    S_800B2400_6 *temp_v1_3;
    S_800B2400_7 *temp_v1_4;
    S_800B2400_5 *temp_sp;

    temp_v0 = func_800B2130(((S_800B2400_0 *)arg0)->unk_18);
    temp_v1_5 = arg0 + (((S_800B2400_0 *)arg0)->unk_18 * 0x10);
    if (temp_v1_5->unk_28 >= temp_v0) {
        var_v1 = 1;
        if (((S_800B2400_0 *)arg0)->unk_0C == 0) {
            var_v1 = 2;
            ASM_TAILSLOT_PIN_TIED(var_v1);   /* MATCH pin: retail delay-slot contents depend on it */
            return func_800B25B4();
        }
        goto done;
    }
    temp_v1 = ((S_800B2400_0 *)arg0)->unk_14;
    temp_a0 = arg0 + (temp_v1 * 0x10);
    if (temp_a0->unk_28 == 0) {
        var_v1 = 4;
        ASM_TAILSLOT_PIN_TIED(var_v1);   /* MATCH pin: retail delay-slot contents depend on it */
        return func_800B25B4(temp_a0);
    }
    temp_s2 = ((S_800B2400_11 *)((temp_a0->unk_24 * 4) + ((S_800B2400_8 *)(((temp_v1 * 4) + arg0)))->unk_3C))->unk_00;
    if (((S_800B2400_0 *)arg0)->unk_0C == 0) {
        temp_byte = temp_s2->unk_01;
        if (temp_byte == 0x13) {
            var_v1 = 3;
            goto done;
        }
    }
    {
        temp_s0 = ((S_800B2400_9 *)(((((S_800B2400_0 *)arg0)->unk_18 * 4) + arg0)))->unk_3C + (func_800B29A4(((S_800B2400_9 *)(((((S_800B2400_0 *)arg0)->unk_18 * 4) + arg0)))->unk_3C) * 4);
        temp_v0_2 = func_800B2280(((S_800B2400_9 *)(((((S_800B2400_0 *)arg0)->unk_18 * 4) + arg0)))->unk_3C, ((S_800B2400_0 *)arg0)->unk_18, temp_v0);
        *(M2C_UNALIGNED_WORD *)temp_v0_2 = *(M2C_UNALIGNED_WORD *)temp_s2;
        temp_s0->unk_00 = temp_v0_2;
        temp_s0->unk_04 = 0;
        temp_v1_2 = ((S_800B2400_0 *)arg0)->unk_14;
        func_800B2190(((S_800B2400_10 *)(((temp_v1_2 * 4) + arg0)))->unk_3C, (temp_sp = arg0 + (temp_v1_2 * 0x10), temp_sp->unk_24));
        temp_v1_3 = (((S_800B2400_0 *)arg0)->unk_14 * 0x10) + arg0;
        temp_v1_3->unk_28 = (s32) (temp_v1_3->unk_28 - 1);
        func_800B23C0(arg0 + ((((S_800B2400_0 *)arg0)->unk_14 * 0x10) + 0x1C));
        temp_v1_4 = arg0 + (((S_800B2400_0 *)arg0)->unk_18 * 0x10);
        temp_v1_4->unk_28 = (s32) (temp_v1_4->unk_28 + 1);
        func_800B23C0(arg0 + ((((S_800B2400_0 *)arg0)->unk_18 * 0x10) + 0x1C));
        var_v1 = 0;
    }
done:
    return var_v1;
}
