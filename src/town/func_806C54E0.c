#include "common.h"

typedef s32 (*Callback)(s32);

typedef struct S_800164E0_0 {
    void * unk_00;
} S_800164E0_0;   /* D_80016000 in func_800164E0 */

typedef struct S_800164E0_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_800164E0_1;   /* temp_v1 in func_800164E0 */

typedef struct S_800164E0_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800164E0_2;   /* temp_v1_2 in func_800164E0 */

typedef struct S_800164E0_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x10];
    s32 unk_18;
} S_800164E0_3;   /* temp_v1_3 in func_800164E0 */

typedef struct S_800164E0_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    s32 unk_1C;
} S_800164E0_4;   /* temp_v1_4 in func_800164E0 */

typedef struct S_800164E0_5 {
    u8 pad_00[0x1C];
    void * unk_1C;
    void * unk_20;
} S_800164E0_5;   /* ((S_800164E0_0 *)D_80016000)->unk_00 in func_800164E0 */

typedef struct S_800164E0_6 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_800164E0_6;   /* (*(void * *)((u8 *)D_80016000 + 0)) in func_800164E0 */


extern s8 D_80016000[];

void func_800164E0(void) {
    void *temp_v1;
    void *temp_v1_2;
    void *temp_v1_3;
    void *temp_v1_4;

    (*(Callback *)((u8 *)(((S_800164E0_5 *)(((S_800164E0_0 *)D_80016000)->unk_00))->unk_20) + 0x248))(0);
    temp_v1 = ((S_800164E0_6 *)((*(void * *)((u8 *)D_80016000 + 0))))->unk_1C;
    ((S_800164E0_1 *)temp_v1)->unk_10 = ((S_800164E0_1 *)temp_v1)->unk_04 + 0x20;
    temp_v1_2 = ((S_800164E0_5 *)(((S_800164E0_0 *)D_80016000)->unk_00))->unk_1C;
    ((S_800164E0_2 *)temp_v1_2)->unk_14 = ((S_800164E0_2 *)temp_v1_2)->unk_08;
    (*(Callback *)((u8 *)(((S_800164E0_5 *)(((S_800164E0_0 *)D_80016000)->unk_00))->unk_20) + 0x258))(0xD);
    temp_v1_3 = ((S_800164E0_6 *)((*(void * *)((u8 *)D_80016000 + 0))))->unk_1C;
    ((S_800164E0_3 *)temp_v1_3)->unk_18 = ((S_800164E0_3 *)temp_v1_3)->unk_04;
    temp_v1_4 = ((S_800164E0_5 *)(((S_800164E0_0 *)D_80016000)->unk_00))->unk_1C;
    ((S_800164E0_4 *)temp_v1_4)->unk_1C = ((S_800164E0_4 *)temp_v1_4)->unk_08;
}
