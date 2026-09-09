#include "common.h"

extern s8 D_80016000[];
extern s32 D_800183D0[];
extern s32 D_800183D8[];

typedef struct S_func_8065C250_0 {
    void *unk_00;
} S_func_8065C250_0;

typedef struct S_func_8065C250_1 {
    u8 pad_00[0x20];
    void *unk_20;
} S_func_8065C250_1;

typedef struct S_func_8065C250_2 {
    u8 pad_00[0x3C];
    void (*unk_3C)(s32 *, s32);
    u8 pad_40[0x8];
    s32 (*unk_48)(s32, s32 *);
} S_func_8065C250_2;

// Calls two callbacks with shared arguments, passing the first callback's result to the second.
void func_8065C250(void) {
    S_func_8065C250_0 *dispatchRoot = (S_func_8065C250_0 *)D_80016000;
    s32 *sharedArguments = D_800183D8;
    s32 callbackResult;

    callbackResult = ((S_func_8065C250_2 *)((S_func_8065C250_1 *)dispatchRoot->unk_00)->unk_20)->unk_48(D_800183D0[0], sharedArguments);
    ((S_func_8065C250_2 *)((S_func_8065C250_1 *)dispatchRoot->unk_00)->unk_20)->unk_3C(sharedArguments, callbackResult);
}
