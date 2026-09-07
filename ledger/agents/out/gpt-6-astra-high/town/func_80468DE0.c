#include "common.h"
#include "m2c_compat.h"

typedef struct S_80019DE0_3 {
    void * unk_00;
} S_80019DE0_3;   /* &D_80016000 in func_80019DE0 */

typedef struct S_80019DE0_4 {
    void * unk_00;
} S_80019DE0_4;   /* D_80016000 in func_80019DE0 */

typedef struct S_80019DE0_5 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80019DE0_5;   /* ((S_80019DE0_3 *)(&D_80016000))->unk_00 in func_80019DE0 */

typedef struct S_80019DE0_6 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_80019DE0_6;   /* (*(void **)((u8 *)D_80016000 + 0)) in func_80019DE0 */

typedef struct S_80019DE0_7 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_80019DE0_7;   /* ((S_80019DE0_4 *)D_80016000)->unk_00 in func_80019DE0 */

typedef struct S_80019DE0_8 {
    u8 pad_00[0x258];
    M2C_UNK (*unk_258)(M2C_UNK);
} S_80019DE0_8;   /* ((S_80019DE0_5 *)(((S_80019DE0_3 *)(&D_80016000))->unk_00))->unk_20 in func_80019DE0 */




extern s8 D_80016000[];

typedef struct S_80019DE0_0 {
    u16 unk_00;
    u16 unk_02;
} S_80019DE0_0;   /* arg0 in func_80019DE0 */

typedef struct S_80019DE0_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80019DE0_1;   /* temp_a0 in func_80019DE0 */

typedef struct S_80019DE0_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80019DE0_2;   /* temp_a0_2 in func_80019DE0 */

/* Calls the active callback and adds signed half-deltas, rounded toward zero, to two target fields. */
void func_80019DE0(S_80019DE0_0 *deltas) {
    u16 first_delta;
    u16 second_delta;
    u32 shifted_delta;
    S_80019DE0_1 *first_target;
    S_80019DE0_2 *second_target;

    ((S_80019DE0_8 *)(((S_80019DE0_5 *)(((S_80019DE0_3 *)(&D_80016000))->unk_00))->unk_20))->unk_258(1);
    first_delta = deltas->unk_00;
    first_target = ((S_80019DE0_6 *)((*(void **)((u8 *)D_80016000 + 0))))->unk_1C;
    shifted_delta = (u32) first_delta << 0x10;
    first_target->unk_04 = (s32) (first_target->unk_04 + ((s32) (((s32) shifted_delta >> 0x10) + (shifted_delta >> 0x1F)) >> 1));
    second_delta = deltas->unk_02;
    second_target = ((S_80019DE0_7 *)(((S_80019DE0_4 *)D_80016000)->unk_00))->unk_1C;
    shifted_delta = (u32) second_delta << 0x10;
    second_target->unk_08 = (s32) (second_target->unk_08 + ((s32) (((s32) shifted_delta >> 0x10) + (shifted_delta >> 0x1F)) >> 1));
}
