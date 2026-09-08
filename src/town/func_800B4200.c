#include "common.h"

typedef struct S_8002E5D8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} S_8002E5D8;

typedef struct S_8002E5E8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} S_8002E5E8;

extern S_8002E5D8 D_8002E5D8;
extern S_8002E5E8 D_8002E5E8;

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
} S_800B4200_a1;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} S_800B4200_a2;

typedef struct {
    s32 unk0;
    S_800B4200_a1 *unk4;
    S_800B4200_a2 *unk8;
} S_800B4200_a0;

typedef union {
    s32 value;
} S_800B4200_arg4;

/* Initialize the state and its buffers from templates, then set the position. */
void func_800B1960(S_800B4200_a0 *state, S_8002E5D8 *params,
                   S_800B4200_a2 *data, s32 x, S_800B4200_arg4 y_arg) {
    s32 y = y_arg.value;
    S_8002E5D8 *params_template = &D_8002E5D8;
    S_8002E5E8 *data_template = &D_8002E5E8;
    s32 *first_word;

    params->unk0 = params_template->unk0;
    first_word = &data_template->unk0;
    params->unk4 = params_template->unk4;
    params->unk8 = params_template->unk8;
    params->unkC = params_template->unkC;

    ((S_8002E5E8 *)data)->unk0 = *first_word;
    ((S_8002E5E8 *)data)->unk4 = data_template->unk4;
    ((S_8002E5E8 *)data)->unk8 = data_template->unk8;
    

    state->unk4 = (S_800B4200_a1 *)params;
    state->unk8 = data;
    state->unk0 = 0;

    state->unk4->unkF = 4;
    state->unk4->unk8 = x + 0x80;
    state->unk4->unkA = y;
    state->unk4->unkC = 0x200;
}
