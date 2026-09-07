#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Node {
    u8 pad0[0x10];
    void (*cb)(void);
    u8 pad14[0xC];
    s32 field_0x20;
} Node;

extern void *func_8003FC64(u32);
extern void func_8008C304(void);
extern void *D_800CFCA8;

void func_8008C374(void) {
    Node *v = func_8003FC64(0);
    if (v != NULL) {
        v->cb = func_8008C304;
        v->field_0x20 = 0;
        v = (Node *)((u8 *)v + 0x20);
        D_800CFCA8 = v;
    }
}
