#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"


typedef struct S_8001659C_6 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_8001659C_6;   /* (*(void **)((u8 *)(&D_80016000) + 0)) in func_8001659C */




typedef struct S_8001659C_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_8001659C_0;   /* temp_v1 in func_8001659C */

typedef struct S_8001659C_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x10];
    s32 unk_18;
} S_8001659C_2;   /* temp_v1_3 in func_8001659C */

/* Invoke state callbacks and copy the base position into two pairs, offsetting the first Y by 32. */
void func_8001659C(void) {
    S_8001659C_0 *first_x_state;
    TownPositionState *first_y_state;
    S_8001659C_2 *second_x_state;
    TownPositionState *second_y_state;

    ((s32 (*) (s32))D_80016000->unk_20->callback_248)(0);
    first_x_state = ((S_8001659C_6 *)((*(void **)((u8 *)(((s32 *)&D_80016000)) + 0))))->unk_1C;
    first_x_state->unk_10 = (s32) first_x_state->unk_04;
    first_y_state = D_80016000->unk_1C;
    first_y_state->unk_14 = (s32) (first_y_state->y + 0x20);
    ((s32 (*) (s32))D_80016000->unk_20->callback_258)(0xD);
    second_x_state = ((S_8001659C_6 *)((*(void **)((u8 *)(((s32 *)&D_80016000)) + 0))))->unk_1C;
    second_x_state->unk_18 = (s32) second_x_state->unk_04;
    second_y_state = D_80016000->unk_1C;
    second_y_state->unk_1C = (s32) second_y_state->y;
}
