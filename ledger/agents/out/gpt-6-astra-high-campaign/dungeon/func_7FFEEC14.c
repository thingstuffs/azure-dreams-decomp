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

/* Allocates a node, initializes its callback and field, and saves the field pointer. */
void func_8008C374(void) {
    Node *node = func_8003FC64(0);
    if (node != NULL) {
        node->cb = func_8008C304;
        node->field_0x20 = 0;
        node = (Node *)((u8 *)node + 0x20);
        D_800CFCA8 = node;
    }
}
