#include "common.h"

#define FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

typedef struct {
    s32 v;
} __attribute__((packed)) UA32;

extern void *D_80016000;
extern UA32 D_80016020;
extern s32 D_80018340;
extern s32 D_800183D0;

void func_8065C34C(void) {
    UA32 sp10;
    void *ptr;
    void *row;

    sp10 = D_80016020;
    ptr = D_80016000;
    row = FIELD(ptr, void **, 0x20);
    D_800183D0 = 9;
    D_80018340 = FIELD(row, s32 (**)(UA32 *), 0x50)(&sp10);
}
