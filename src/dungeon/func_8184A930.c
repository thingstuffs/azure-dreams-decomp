#include "common.h"

typedef struct S_80024130_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0x18];
    s32 unk_2C;
} S_80024130_0;   /* temp_v0 in func_80024130 */

typedef struct S_80024130_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80024130_1;   /* temp_s0 in func_80024130 */

typedef struct S_80024130_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024130_2;   /* temp_v1_2 in func_80024130 */

typedef struct S_80024130_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024130_3;   /* arg1 in func_80024130 */



extern s32 func_80024204();
extern s32 func_8003DB94();
extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 rand();
extern u8 D_80024048[9];
extern u8 D_80045340[9];
extern u8 D_800DE8E8[9];

s32 func_80024130(s32 arg0, S_80024130_3 *arg1)
{
    s32 temp_v1;
    s32 var_v0;
    S_80024130_1 *temp_s0;
    S_80024130_0 *temp_v0;
    S_80024130_2 *temp_v1_2;
    s32 temp_a0;
    register void *temp_ret ASM_REG("$2");   /* MATCH pin: retail basic-block layout depends on it */

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        temp_v0->unk_10 = D_80024048;
        temp_s0 = temp_v0->unk_0C;
        temp_v0->unk_2C = arg0;
        temp_s0->unk_0E = 0x80;
        temp_s0->unk_0D = 0x80;
        temp_s0->unk_0C = 0x80;
        func_8003DB94(temp_s0, D_800DE8E8, 0);
        temp_s0->unk_1E = 0x1000;
        temp_s0->unk_1C = 0x1000;
        var_v0 = rand();
        temp_v1 = var_v0;
        if (temp_v1 < 0) {
            var_v0 = temp_v1 + 0xFFF;
        }
        temp_s0->unk_1A = temp_v1 - ((var_v0 >> 0xC) << 0xC);
        func_8004491C(temp_v0, D_80045340);
        temp_v1_2 = temp_v0->unk_08;
        temp_v1_2->unk_02 = arg1->unk_02;
        temp_v1_2->unk_06 = arg1->unk_06;
        temp_a0 = arg1->unk_0A;
        ASM_KEEP(temp_a0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        temp_ret = temp_v0;
        ASM_KEEP(temp_ret);   /* MATCH pin: retail basic-block layout depends on it */
        temp_v1_2->unk_0A = temp_a0;
        return func_80024204(temp_a0);
    }
    return 0;
}

/* MECHANISM: The 0x28 frame follows from holding arg0/arg1 and the two object bases in s3/s2/s1/s0.
   Guarded a0 and v0 carriers retain the final halfword copy and object result across the dispatcher.
   LEAD 22 then emits j with the sh delay slot; u8 color fields preserve the +0x80 materialization. */
