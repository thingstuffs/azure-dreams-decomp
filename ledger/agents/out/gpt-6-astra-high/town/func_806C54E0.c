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

/* Run two callbacks and initialize offset and saved coordinates from the current position. */
void func_800164E0(void) {
    void *offset_x_state;
    void *offset_y_state;
    void *saved_x_state;
    void *saved_y_state;

    (*(Callback *)((u8 *)(((S_800164E0_5 *)(((S_800164E0_0 *)D_80016000)->unk_00))->unk_20) + 0x248))(0);
    offset_x_state = ((S_800164E0_6 *)((*(void * *)((u8 *)D_80016000 + 0))))->unk_1C;
    ((S_800164E0_1 *)offset_x_state)->unk_10 = ((S_800164E0_1 *)offset_x_state)->unk_04 + 0x20;
    offset_y_state = ((S_800164E0_5 *)(((S_800164E0_0 *)D_80016000)->unk_00))->unk_1C;
    ((S_800164E0_2 *)offset_y_state)->unk_14 = ((S_800164E0_2 *)offset_y_state)->unk_08;
    (*(Callback *)((u8 *)(((S_800164E0_5 *)(((S_800164E0_0 *)D_80016000)->unk_00))->unk_20) + 0x258))(0xD);
    saved_x_state = ((S_800164E0_6 *)((*(void * *)((u8 *)D_80016000 + 0))))->unk_1C;
    ((S_800164E0_3 *)saved_x_state)->unk_18 = ((S_800164E0_3 *)saved_x_state)->unk_04;
    saved_y_state = ((S_800164E0_5 *)(((S_800164E0_0 *)D_80016000)->unk_00))->unk_1C;
    ((S_800164E0_4 *)saved_y_state)->unk_1C = ((S_800164E0_4 *)saved_y_state)->unk_08;
}
