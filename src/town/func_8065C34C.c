#include "common.h"

typedef struct {
    s32 v;
} __attribute__((packed)) UA32;

typedef struct S_func_8065C34C_0 {
    u8 pad_00[0x20];
    void *unk_20;
} S_func_8065C34C_0;

typedef struct S_func_8065C34C_1 {
    u8 pad_00[0x50];
    s32 (*unk_50)(UA32 *);
} S_func_8065C34C_1;

extern void *D_80016000;
extern UA32 D_80016020;
extern s32 D_80018340;
extern s32 D_800183D0;

/* Set the state to 9 and cache the callback result using a copy of the global arguments. */
void func_8065C34C(void) {
    UA32 callback_args;
    S_func_8065C34C_0 *context;
    S_func_8065C34C_1 *callback_table;

    callback_args = D_80016020;
    context = D_80016000;
    callback_table = context->unk_20;
    D_800183D0 = 9;
    D_80018340 = callback_table->unk_50(&callback_args);
}
