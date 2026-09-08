#include "common.h"

#define FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

typedef struct {
    s32 v;
} __attribute__((packed)) UA32;

extern void *D_80016000;
extern UA32 D_80016020;
extern s32 D_80018340;
extern s32 D_800183D0;

/* Set the state to 9 and cache the callback result using a copy of the global arguments. */
void func_8065C34C(void) {
    UA32 callback_args;
    void *context;
    void *callback_table;

    callback_args = D_80016020;
    context = D_80016000;
    callback_table = FIELD(context, void **, 0x20);
    D_800183D0 = 9;
    D_80018340 = FIELD(callback_table, s32 (**)(UA32 *), 0x50)(&callback_args);
}
