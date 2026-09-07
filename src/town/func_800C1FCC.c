#include "common.h"
typedef s32 M2C_UNK;

typedef struct S_800BF72C_3 {
    u8 pad_00[0xA0];
    void * unk_A0;
} S_800BF72C_3;   /* arg0 in func_800BF72C */

typedef struct S_800BF72C_4 {
    u8 pad_00[0x68];
    u16 unk_68;
} S_800BF72C_4;   /* ((S_800BF72C_3 *)arg0)->unk_A0 in func_800BF72C */



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_800BC574(void *, s32);
extern s32 D_80012D5C;
extern void *D_80089930[];

/* The final state reset is coupled to the non-overflow path.  This is a
 * defined source-level guard whose natural branch leader is the epilogue. */
typedef struct S_800BF72C_0 {
    u8 pad_00[0x68];
    s16 unk_68;
} S_800BF72C_0;   /* arg0 in func_800BF72C */

typedef struct S_800BF72C_1 {
    s32 unk_00;
    s32 unk_04;
} S_800BF72C_1;   /* arg1 in func_800BF72C */

typedef struct S_800BF72C_2 {
    u8 pad_00[0x2D5C];
    u32 unk_2D5C;
} S_800BF72C_2;   /* clock in func_800BF72C */

void func_800BF72C(S_800BF72C_0 *arg0, S_800BF72C_1 *arg1) {
    static void *const sw_keep[] = {
        &&block_0, &&block_1, &&block_2, &&block_3, &&block_4
    };
    s32 stack_record[6];
    s16 temp_v1_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1_3;
    s32 stack_low;
    u16 temp_v1;
    u32 swi;
    u32 *clock;
    u32 value;

    temp_v1 = ((S_800BF72C_4 *)(((S_800BF72C_3 *)arg0)->unk_A0))->unk_68;
    if ((temp_v1 & 1) && arg0->unk_68 == 0)
        arg0->unk_68 = (s16)temp_v1;
    temp_v1_2 = arg0->unk_68;
    swi = temp_v1_2;
    if (swi >= 5) goto block_0;
    (void)sw_keep;
    goto *D_80089930[swi];

block_1:
    temp_v1_3 = arg1->unk_04 + 0x40000;
    arg1->unk_04 = temp_v1_3;
    if (temp_v1_3 > 0x023FFFFF) {
        arg1->unk_04 = 0x02400000;
        goto block_15;
    }
    goto block_0;

block_2:
    temp_v0 = arg1->unk_00 + 0x40000;
    arg1->unk_00 = temp_v0;
    if (temp_v0 == 0x10000000) {
        clock = (u32 *)0x80010000;
        value = ((S_800BF72C_2 *)clock)->unk_2D5C;
        if ((value % 1000U) == 777U) {
            stack_record[0] = 0x0FA00000;
            stack_low = 0xFFF80000;
            stack_record[1] = arg1->unk_04;
            stack_record[2] = stack_low;
            func_800BC574(stack_record, 0x200);
        }
    }
    if (arg1->unk_00 > 0x105FFFFF) {
        arg1->unk_00 = 0x10600000;
        goto block_18;
    }
    goto block_0;

block_3:
    temp_v0_2 = arg1->unk_00 + 0xFFFC0000;
    arg1->unk_00 = temp_v0_2;
    if (temp_v0_2 <= 0x0FA00000) {
        arg1->unk_00 = 0x0FA00000;
        goto block_15;
    }
    goto block_0;

block_15:
    arg0->unk_68 =
        (s16)((u16)arg0->unk_68 + 1);
    goto block_0;

block_4:
    temp_v0_3 = arg1->unk_04 + 0xFFFC0000;
    arg1->unk_04 = temp_v0_3;
    if (temp_v0_3 > 0x02300000)
        goto block_0;
    arg1->unk_04 = 0x02300000;
    arg0->unk_68 = 0;
    goto block_0;
block_18:
    arg0->unk_68 = 0;
block_0:
    return;
}
