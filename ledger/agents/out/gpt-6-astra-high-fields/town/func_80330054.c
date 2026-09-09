#include "common.h"

typedef struct S_func_8001A854_0 {
    void *unk_00;
} S_func_8001A854_0;

typedef struct S_func_8001A854_1 {
    u8 pad_00[0x1C];
    void *unk_1C;
    void *unk_20;
} S_func_8001A854_1;

typedef struct S_func_8001A854_2 {
    u8 pad_00[0x258];
    void (*unk_258)(s32);
} S_func_8001A854_2;

typedef struct S_func_8001A854_3 {
    u8 pad_00[4];
    u16 unk_04;
    u8 pad_06[2];
    u16 unk_08;
} S_func_8001A854_3;

typedef struct S_func_8001A854_4 {
    u16 unk_00;
    u16 unk_02;
} S_func_8001A854_4;

extern s8 D_80016000[];

/* Calls the state handler and copies two state values to the output. */
void func_8001A854(S_func_8001A854_4 *output, s32 handler_arg) {
    ((S_func_8001A854_2 *)((S_func_8001A854_1 *)((S_func_8001A854_0 *)D_80016000)->unk_00)->unk_20)->unk_258(handler_arg);
    output->unk_00 = ((S_func_8001A854_3 *)((S_func_8001A854_1 *)((S_func_8001A854_0 *)D_80016000)->unk_00)->unk_1C)->unk_04;
    output->unk_02 = ((S_func_8001A854_3 *)((S_func_8001A854_1 *)((S_func_8001A854_0 *)D_80016000)->unk_00)->unk_1C)->unk_08;
}
