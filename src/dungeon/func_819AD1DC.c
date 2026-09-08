#include "common.h"



typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_FIELD_V(expr, type_ptr, offset) (*(volatile type_ptr)((s8 *)(expr) + (offset)))

void func_80024A94(void) __attribute__((noreturn));
void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_800245A0;
extern M2C_UNK D_80027460;
extern M2C_UNK D_800CEEFC;

typedef struct S_819AD1DC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_819AD1DC_0;   /* temp_v0 in func_819AD1DC */

typedef struct S_819AD1DC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_819AD1DC_1;   /* temp_s3 in func_819AD1DC */

typedef struct S_819AD1DC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_819AD1DC_2;   /* temp_v1 in func_819AD1DC */

typedef struct S_819AD1DC_3 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u8 pad_22[0xE];
    s16 unk_30;
    u8 pad_32[0x6];
    s16 unk_38;
} S_819AD1DC_3;   /* temp_a2 in func_819AD1DC */

typedef struct S_819AD1DC_4 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 pad_0C[0x1];
    s8 unk_0D;
    u8 pad_0E[0xE];
    u16 unk_1C;
    u16 unk_1E;
} S_819AD1DC_4;   /* temp_a1 in func_819AD1DC */

void *func_819AD1DC(void *arg0)
{
    S_819AD1DC_1 *temp_s3;
    s32 var_s1;
    M2C_UNK *temp_s5;
    M2C_UNK *temp_s4;
    register s32 temp_s2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    void *temp_v0;
    s32 arithmetic_v0;
    register s32 arithmetic_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u16 reload_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    S_819AD1DC_4 *temp_a1;
    S_819AD1DC_3 *temp_a2;
    S_819AD1DC_2 *temp_v1;

    temp_s3 = arg0;
    var_s1 = 0;
    temp_s5 = &D_800245A0;
    temp_s4 = &D_80027460;
    temp_s2 = 8;
loop_1:
    temp_v0 = func_8003FC64(18);
    if (temp_v0 != NULL) {
        ((S_819AD1DC_0 *)temp_v0)->unk_10 = temp_s5;
        func_8004491C(temp_v0, &D_800CEEFC);
        temp_v1 = ((S_819AD1DC_0 *)temp_v0)->unk_08;
        temp_v0_2 = temp_s3->unk_02;
        temp_a2 = temp_v0 + 0x20;
        temp_v1->unk_02 = temp_v0_2;
        temp_v1->unk_0E = temp_v0_2;
        temp_a2->unk_1C = temp_v0_2;
        temp_v0_3 = temp_s3->unk_06;
        temp_v1->unk_06 = temp_v0_3;
        temp_v1->unk_12 = temp_v0_3;
        temp_a2->unk_1E = temp_v0_3;
        temp_v0_4 = temp_s3->unk_0A;
        temp_v1->unk_0A = temp_v0_4;
        temp_v1->unk_16 = temp_v0_4;
        temp_a2->unk_20 = temp_v0_4;
        temp_a1 = ((S_819AD1DC_0 *)temp_v0)->unk_0C;
        temp_a1->unk_08 = temp_s4;
        if (var_s1 != temp_s2) {
            arithmetic_v0 = 0x200;
            ASM_TAILSLOT_PIN_TIED(arithmetic_v0);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_80024A94();
            return (void *)0x200;
        }
        ASM_KEEP(temp_s2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        do { temp_a1->unk_1E = 0x800U; } while (0);
        arithmetic_v0 = (temp_s2 - var_s1) * 4;
        arithmetic_v1 = -0x80 - arithmetic_v0;
        reload_a0 = M2C_FIELD_V(temp_a1, u16 *, 0x1E);
        temp_a1->unk_0D = (u8)arithmetic_v1;
        temp_a1->unk_1C = reload_a0;
        temp_a2->unk_38 = var_s1;
        if (var_s1 == temp_s2) {
            temp_a2->unk_38 = 7;
        }
        temp_a2->unk_30 = temp_s2;
        goto block_8;
    }
block_8:
    var_s1 += 1;
    if (var_s1 < 9) {
        goto loop_1;
    }
    return temp_v0;
}
