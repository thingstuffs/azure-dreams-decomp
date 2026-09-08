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

extern int D_800814A0;

/* Allocate and initialize a paged item-list node, returning null on failure. */
void *func_800B14B0(s32 parent, s32 selected_index, s32 item_count, s32 page_index, s32 last_page, s32 item_base, s32 display_mode)
{
    S_800B3D50_node *node = func_8003FC64(0);
    S_800B3D50_sub *sub;

    if (node != 0) {
        sub = &node->sub;
        if (func_800B1434(sub, 0x1F) != 0) {
            node->field_0xC = (u8 *)node + 0xDC;
            sub->result = func_800B091C(sub->input);
            func_800B13D4(sub, parent, selected_index, item_count, page_index, last_page, item_base, display_mode);
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
