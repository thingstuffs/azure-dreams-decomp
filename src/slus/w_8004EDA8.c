#include "common.h"

/* Node returned by func_8003FC64. We only model the fields touched here:
 * a "public" area starting at offset 0x20 (owner back-pointer), and two
 * writes made through a pointer into that area: +4 (the stashed a1 arg)
 * and -0x10 (a callback function pointer at absolute offset 0x10). */
typedef struct S_8004EDA8_node {
    u8 pad_0x0[0x20];
    void *owner_0x20;   /* 0x20: back-pointer to a0 */
    void *arg_0x24;      /* 0x24: stashed a1 */
} S_8004EDA8_node;

/* The object passed in as a0: only its 0x1E halfword (flags) is touched
 * here, matching the field used across the func_8003FC64 family. */
typedef struct S_8004EDA8_owner {
    u8 pad_0x0[0x1E];
    u16 flags_0x1E;   /* 0x1E */
} S_8004EDA8_owner;

extern void *func_8003FC64(s32 a0);
extern void func_8004EB3C(void *a0);
extern void func_8004ED5C(void *a0);
extern s16 SD_Call(s32 a0);

/* Clears the owner flag and allocates and initializes a callback node with its context. */
void *func_8004EDA8(void *owner_arg, void *context_arg)
{
    S_8004EDA8_owner *owner = (S_8004EDA8_owner *)owner_arg;
    void *context = context_arg;
    S_8004EDA8_node *node;
    u8 *node_fields;

    owner->flags_0x1E = owner->flags_0x1E & 0xDFFF;
    node = (S_8004EDA8_node *)func_8003FC64(0);
    if (node != 0) {
        node_fields = (u8 *)&node->owner_0x20;
        *(void **)(node_fields + 4) = context;
        node->owner_0x20 = owner;
        SD_Call(0xD1);
        *(void (**)(void *))(node_fields - 0x10) = func_8004ED5C;
        func_8004EB3C((u8 *)node + 0x28);
    }
    return node;
}
