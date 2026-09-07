#include "common.h"
#include "m2c_compat.h"

typedef struct S_818B7BD0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_818B7BD0_0;   /* temp_v0 in func_818B7BD0 */

typedef struct S_818B7BD0_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    union { s16 s16; u8 u8; } unk_0E;   /* accessed as both */
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_18;   /* overlapping accesses */
    s16 unk_1C;
    s16 unk_1E;
} S_818B7BD0_1;   /* temp_s0 in func_818B7BD0 */

typedef struct S_818B7BD0_2 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x4];
    s32 unk_18;
} S_818B7BD0_2;   /* arg0 in func_818B7BD0 */

typedef struct S_818B7BD0_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818B7BD0_3;   /* arg1 in func_818B7BD0 */

typedef struct S_818B7BD0_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818B7BD0_4;   /* temp_v1_2 in func_818B7BD0 */


typedef union {
    s64 value;
    s32 word[2];
} M2C_WIDE;

#if defined(__mips__) || defined(mips)
#define M2C_HIGH_WORD(product) ((product).word[0])
#else
#define M2C_HIGH_WORD(product) ((s32) ((u64) (product).value >> 32))
#endif

void func_8002551C() __attribute__((noreturn));
void func_8003DB94(void *, void *, s32);
void *func_8003FC64();
M2C_UNK func_8004491C();
s32 func_80069EF8();
extern M2C_UNK D_800250E8;
extern M2C_UNK D_80025EE4;
extern M2C_UNK D_80045C34;

s32 func_818B7BD0(S_818B7BD0_2 *arg0, S_818B7BD0_3 *arg1) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_div_v1;
    register s32 temp_hi ASM_REG("$7");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 temp_quot ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    s32 temp_ret;
    s32 temp_v1;
    s32 var_v0;
    register s32 result ASM_REG("$2");   /* MATCH pin: retail keeps a computation the compiler would drop */
    void *temp_model;
    void *temp_tag;
    S_818B7BD0_1 *temp_s0;
    void *temp_v0;
    S_818B7BD0_4 *temp_v1_2;
    M2C_WIDE temp_product;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_tag = &D_800250E8;
        ASM_KEEP(temp_tag);   /* MATCH pin: retail schedule: same instructions, different order without it */
        temp_s0 = temp_v0 + 0x20;
        ((S_818B7BD0_0 *)temp_v0)->unk_10 = temp_tag;
        ((S_818B7BD0_0 *)temp_v0)->unk_20 = arg0;
        temp_s0->unk_0E.s16 = 0;
        temp_s0->unk_10 = 0;
        temp_ret = func_80069EF8();
        temp_div_v1 = (s32) 0x92492493;
        temp_product.value = (s64) temp_ret * temp_div_v1;
        temp_div_v1 = temp_ret >> 31;
        temp_model = &D_80025EE4;
        temp_hi = M2C_HIGH_WORD(temp_product);
        ASM_KEEP(temp_hi);   /* MATCH pin: retail register colouring depends on it */
        temp_quot = ((temp_hi + temp_ret) >> 2) - temp_div_v1;
        temp_s0->unk_12 = (s16) (temp_ret - ((temp_quot << 3) - temp_quot));
        temp_s0->unk_14 = (u16) arg0->unk_12;
        temp_s0->unk_18.at00.v = (s32) arg0->unk_18;
        temp_s0 = ((S_818B7BD0_0 *)temp_v0)->unk_0C;
        temp_s0->unk_0E.u8 = 0x80;
        temp_s0->unk_0D = 0x80;
        temp_s0->unk_0C = 0x80;
        temp_s0->unk_12 = 0x7E00;
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0x100);
        func_8003DB94(temp_s0, temp_model, 0);
        var_v0 = func_80069EF8();
        temp_v1 = var_v0;
        if (temp_v1 < 0) {
            var_v0 = temp_v1 + 0xFFF;
        }
        temp_s0->unk_18.at02.v = (s16) (temp_v1 - ((var_v0 >> 0xC) << 0xC));
        temp_s0->unk_1E = 0x400;
        temp_s0->unk_1C = 0x400;
        func_8004491C(temp_v0, &D_80045C34);
        temp_v1_2 = ((S_818B7BD0_0 *)temp_v0)->unk_08;
        ASM_KEEP(temp_v1_2);   /* MATCH pin: keeps a statement from moving across a call/branch */
        result = (s32) temp_v0;
        ASM_KEEP(result);   /* MATCH pin: retail keeps a computation the compiler would drop */
        temp_a0 = arg1->unk_00;
        temp_a1 = arg1->unk_04;
        temp_a2 = arg1->unk_08;
        temp_a3 = arg1->unk_0C;
        temp_v1_2->unk_00 = temp_a0;
        temp_v1_2->unk_04 = temp_a1;
        temp_v1_2->unk_08 = temp_a2;
        temp_v1_2->unk_0C = temp_a3;
        temp_a0 = arg1->unk_10;
        temp_a1 = arg1->unk_14;
        temp_v1_2->unk_10 = temp_a0;
        temp_v1_2->unk_14 = temp_a1;
        func_8002551C(temp_a0, temp_a1, temp_a2, temp_a3);
    }
    return 0;
}
