#include "common.h"



typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_800247B4(void) __attribute__((noreturn));
extern M2C_UNK func_8003DB94();
extern void *func_8003FC64(s32);
extern M2C_UNK func_8004491C();
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern M2C_UNK D_80024330[];
extern M2C_UNK D_80045340[];
extern M2C_UNK D_800DEAE0[];

typedef struct S_8185CE28_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_8185CE28_0;   /* temp_v0 in func_8185CE28 */

typedef struct S_8185CE28_1 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    s16 unk_22;
    s16 unk_24;
} S_8185CE28_1;   /* temp_s1 in func_8185CE28 */

typedef struct S_8185CE28_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8185CE28_2;   /* arg1 in func_8185CE28 */

typedef struct S_8185CE28_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8185CE28_3;   /* temp_s0 in func_8185CE28 */

s32 func_8185CE28(s32 arg0, S_8185CE28_2 *arg1, s16 arg2)
{
    s16 temp_v1;
    s32 temp_a0;
    S_8185CE28_3 *temp_s0;
    S_8185CE28_1 *temp_s1;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_a0 = arg2 * 3;
        ((S_8185CE28_0 *)temp_v0)->unk_20 = arg0;
        temp_s1 = temp_v0 + 0x20;
        ((S_8185CE28_0 *)temp_v0)->unk_10 = D_80024330;
        temp_v1 = temp_a0 % 8;
        temp_s1->unk_1C = temp_v1 << 9;
        temp_s1->unk_20 = 0x20;
        temp_s1->unk_1E = 0;
        temp_s1->unk_22 = -8;
        temp_s1->unk_24 = temp_v1;
        temp_s1->unk_06 = arg1->unk_02;
        temp_s1->unk_0A = arg1->unk_06;
        temp_s1->unk_0E = arg1->unk_0A;
        temp_s0 = ((S_8185CE28_0 *)temp_v0)->unk_0C;
        temp_s0->unk_0E = 0x80;
        temp_s0->unk_0D = 0x80;
        temp_s0->unk_0C = 0x80;
        func_8003DB94(temp_s0, D_800DEAE0, 0);
        temp_s0->unk_1E = 0x1800;
        temp_s0->unk_1C = 0x1800;
        temp_s0->unk_12 = 0x7E0B;
        temp_s0->unk_14 |= 0xC;
        temp_s0->unk_10 |= 0x20;
        temp_s0->unk_14 |= 0x100;
        func_8004491C(temp_v0, D_80045340);
        temp_s0 = ((S_8185CE28_0 *)temp_v0)->unk_08;
        temp_s0->unk_02 = temp_s1->unk_06 +
            ((func_800644B8(temp_s1->unk_1C) >> 4) *
             temp_s1->unk_20 >> 8);
        temp_s0->unk_06 = temp_s1->unk_0A +
            ((func_80064584(temp_s1->unk_1C) >> 4) *
             temp_s1->unk_20 >> 8);
        {
            u16 final_z = temp_s1->unk_0E;
#ifndef NON_MATCHING
            __asm__ __volatile__("" : : : "$2");
#endif
            {
                register s32 v0pin ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
                v0pin = (s32)temp_v0;
                ASM_KEEP(v0pin);   /* MATCH pin: load-bearing for the whole function shape */
                temp_s0->unk_0A = final_z - 8;
                func_800247B4();
            }
        }
    }
    {
        register s32 zero_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        zero_v0 = 0;
        ASM_KEEP(zero_v0);   /* MATCH pin: retail schedule: same instructions, different order without it */
        return zero_v0;
    }
}
