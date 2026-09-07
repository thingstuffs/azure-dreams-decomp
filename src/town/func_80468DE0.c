#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"



typedef struct S_80019DE0_5 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80019DE0_5;   /* ((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v in func_80019DE0 */

typedef struct S_80019DE0_6 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_80019DE0_6;   /* (*(void **)((u8 *)D_80016000 + 0)) in func_80019DE0 */

typedef struct S_80019DE0_7 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_80019DE0_7;   /* ((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v in func_80019DE0 */

typedef struct S_80019DE0_8 {
    u8 pad_00[0x258];
    M2C_UNK (*unk_258)(M2C_UNK);
} S_80019DE0_8;   /* ((S_80019DE0_5 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v))->unk_20 in func_80019DE0 */




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

void func_80019DE0(S_80019DE0_0 *arg0) {
    u16 temp_v0;
    u16 temp_v0_2;
    u32 temp_shift;
    S_80019DE0_1 *temp_a0;
    S_80019DE0_2 *temp_a0_2;

    ((S_80019DE0_8 *)(((S_80019DE0_5 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v))->unk_20))->unk_258(1);
    temp_v0 = arg0->unk_00;
    temp_a0 = ((S_80019DE0_6 *)((*(void **)((u8 *)D_80016000 + 0))))->unk_1C;
    temp_shift = (u32) temp_v0 << 0x10;
    temp_a0->unk_04 = (s32) (temp_a0->unk_04 + ((s32) (((s32) temp_shift >> 0x10) + (temp_shift >> 0x1F)) >> 1));
    temp_v0_2 = arg0->unk_02;
    temp_a0_2 = ((S_80019DE0_7 *)(((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v))->unk_1C;
    temp_shift = (u32) temp_v0_2 << 0x10;
    temp_a0_2->unk_08 = (s32) (temp_a0_2->unk_08 + ((s32) (((s32) temp_shift >> 0x10) + (temp_shift >> 0x1F)) >> 1));
}

/* MECHANISM: The true-space function holds the hi/lo-class D_80016000 page in s0
   and arg0 in s1 across the indirect call; all three root loads use one pointer slot.
   The narrow u16 loads plus explicit s16 rounding preserve the two arithmetic sequences. */
