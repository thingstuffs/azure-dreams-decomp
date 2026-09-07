#include "common.h"

/* Clears bit 0x2000 in a0's 0x1E flags halfword, then allocates a node via
 * func_8003FC64(0). On success, stashes a1 at node+0x24, stores a0 at
 * node+0x20, fires a status/sound event (func_80053DA8(0xD1)), installs
 * func_8004ED5C as the node's callback (node+0x10), and forwards the
 * node's tail (node+0x28) to func_8004EB3C to finish initialization.
 * Returns the allocated node (or NULL). */
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
extern s16 func_80053DA8(s32 a0);

void *func_8004EDA8(void *a0, void *a1)
{
    S_8004EDA8_owner *s2 = (S_8004EDA8_owner *)a0;
    void *s3 = a1;
    S_8004EDA8_node *s1;
    u8 *s0;

    s2->flags_0x1E = s2->flags_0x1E & 0xDFFF;
    s1 = (S_8004EDA8_node *)func_8003FC64(0);
    if (s1 != 0) {
        s0 = (u8 *)&s1->owner_0x20;
        *(void **)(s0 + 4) = s3;
        s1->owner_0x20 = s2;
        func_80053DA8(0xD1);
        *(void (**)(void *))(s0 - 0x10) = func_8004ED5C;
        func_8004EB3C((u8 *)s1 + 0x28);
    }
    return s1;
}
