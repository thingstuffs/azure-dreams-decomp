#include "common.h"

/* Sub-record living at offset 0x20 of the allocated node (same node type
 * allocated by func_8003FC64, size class 0x124 per src/w_8003FC64.c /
 * src/w_800511B4.c): a result pointer at 0xC8 and an input pointer at
 * 0xCC (both relative to the sub-record base). */
typedef struct S_800B3D50_sub {
    u8 pad0[0xC8];
    void *result;   /* 0xC8 */
    void *input;    /* 0xCC */
} S_800B3D50_sub;

typedef struct S_800B3D50_node {
    u8 pad0[0xC];
    void *field_0xC;        /* 0x0C */
    u8 pad10[0x1E - 0x10];
    u16 flags;               /* 0x1E */
    S_800B3D50_sub sub;      /* 0x20 */
} S_800B3D50_node;

extern void *func_8003FC64(s32 a0);
extern s32 func_800B1434(void *a0, s32 a1);
extern void *func_800B091C(void *a0);
extern void func_800B13D4(void *a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);
extern void func_8004491C(void *a0, void *a1);
extern void func_8004CAA0(void);
extern void func_8004B248(u16 **a0);
extern void *func_800B1590(void);

extern int D_800814A0;

void *func_800B14B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6)
{
    S_800B3D50_node *node = func_8003FC64(0);
    S_800B3D50_sub *sub;

    if (node != 0) {
        sub = &node->sub;
        if (func_800B1434(sub, 0x1F) != 0) {
            node->field_0xC = (u8 *)node + 0xDC;
            sub->result = func_800B091C(sub->input);
            func_800B13D4(sub, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
            func_8004491C(node, (void *)func_8004CAA0);
            return node;
        }
        func_8004B248((u16 **)((u8 *)node + 0xF0));
        node->flags |= 0x8000;
        node = 0;
        D_800814A0 |= 0x8000;
    }
    return node;
}

/* MECHANISM: The node/sub locals naturally hold $s0/$s1 and preserve the exact 0x40 frame.
   Discarding func_800B1590's result keeps the pre-call node as the function return value.
   LEAD 22 then places the live move v0,s0 in the converted tail-jump delay slot. */
