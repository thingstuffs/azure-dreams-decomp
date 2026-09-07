#include "common.h"



typedef s32 M2C_UNK;

typedef struct S_8051E954_2 {
    void * unk_00;
} S_8051E954_2;   /* &D_80016000 in func_8051E954 */

typedef struct S_8051E954_3 {
    u8 pad_00[0x208];
    M2C_UNK (*unk_208)(M2C_UNK);
} S_8051E954_3;   /* (*(void **)((u8 *)temp_v1 + 0x20)) in func_8051E954 */

typedef struct S_8051E954_4 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8051E954_4;   /* ((S_8051E954_2 *)(&D_80016000))->unk_00 in func_8051E954 */

typedef struct S_8051E954_5 {
    u8 pad_00[0x224];
    M2C_UNK (*unk_224)(s32 *);
} S_8051E954_5;   /* ((S_8051E954_4 *)(((S_8051E954_2 *)(&D_80016000))->unk_00))->unk_20 in func_8051E954 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK D_80016000;
extern s32 D_80019158;

typedef struct S_8051E954_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_8051E954_0;   /* temp_s0 in func_8051E954 */

typedef struct S_8051E954_1 {
    void * unk_00;
} S_8051E954_1;   /* &D_80016000 in func_8051E954 */

void func_8051E954(s32 arg0) {
    register s32 *temp_s0 ASM_REG("$16");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    void *temp_v1;
    s32 temp_a0;
    s32 temp_a0_2;

    temp_a0 = (arg0 & 0xFFFF) | 0x06800000;
    D_80019158 = temp_a0;
    temp_a0_2 = (temp_a0 & 0xFFFF) | 0x05000000;
    temp_s0 = &D_80019158;
    ((S_8051E954_0 *)temp_s0)->unk_04 = temp_a0_2;
    arg0 = (temp_a0_2 & 0xFFFF) | 0xFF000000;
    temp_v1 = ((S_8051E954_1 *)(&D_80016000))->unk_00;
    ((S_8051E954_0 *)temp_s0)->unk_08 = arg0;
    ((S_8051E954_3 *)((*(void **)((u8 *)temp_v1 + 0x20))))->unk_208(0);
    ((S_8051E954_5 *)(((S_8051E954_4 *)(((S_8051E954_2 *)(&D_80016000))->unk_00))->unk_20))->unk_224(temp_s0);
}
