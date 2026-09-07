#include "common.h"
#include "m2c_compat.h"

void func_800247B8(void) __attribute__((noreturn));  /* extern -- frame-live dispatcher */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
extern u8 D_80024674[];
extern u8 D_80025214[];
extern u8 D_80045340[];

typedef struct S_818A4ED0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818A4ED0_0;   /* temp_v0 in func_818A4ED0 */

typedef struct S_818A4ED0_1 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818A4ED0_1;   /* temp_s0 in func_818A4ED0 */

typedef struct S_818A4ED0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818A4ED0_2;   /* temp_s0_2 in func_818A4ED0 */

typedef struct S_818A4ED0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818A4ED0_3;   /* arg1 in func_818A4ED0 */

s32 func_818A4ED0(s32 arg0, S_818A4ED0_3 *arg1) {
    s32 temp_v1;
    S_818A4ED0_1 *temp_s0;
    S_818A4ED0_2 *temp_s0_2;
    S_818A4ED0_0 *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_v0->unk_10 = D_80024674;
        temp_v0->unk_20 = arg0;
        temp_s0 = temp_v0->unk_0C;
        temp_s0->unk_08 = D_80025214;
        temp_s0->unk_12 = 0x7E07;
        temp_s0->unk_0E = 0;
        temp_s0->unk_0D = 0;
        temp_s0->unk_0C = 0;
        temp_s0->unk_10 = (u16) (temp_s0->unk_10 | 0x60);
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0x10C);
        temp_v1 = rand();
        temp_s0->unk_1A = (s16) (temp_v1 % 0x1000);
        temp_s0->unk_1E = 0;
        temp_s0->unk_1C = 0;
        func_8004491C(temp_v0, D_80045340);
        temp_s0_2 = temp_v0->unk_08;
        {
            s32 rng_v0;
            rng_v0 = rand();
        }
        temp_s0_2->unk_02 = (u16) arg1->unk_02;
        temp_s0_2->unk_06 = (u16) arg1->unk_06;
        {
            u16 final_z = arg1->unk_0A;
#ifndef NON_MATCHING
            __asm__ __volatile__("" : : : "$2");
#endif
            {
                register s32 v0pin ASM_REG("$2");   /* MATCH pin: retail basic-block layout depends on it */
                v0pin = (s32) temp_v0;
                ASM_KEEP(v0pin);   /* MATCH pin: retail basic-block layout depends on it */
                temp_s0_2->unk_0A = final_z;
                func_800247B8();
            }
        }
    }
    {
        register s32 zero_v0 ASM_REG("$2");   /* MATCH pin: retail basic-block layout depends on it */
        zero_v0 = 0;
        ASM_KEEP(zero_v0);   /* MATCH pin: retail schedule: same instructions, different order without it */
        return zero_v0;
    }
}
