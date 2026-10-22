#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"

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

extern s32 copy_records_through_end(void *a0, s32 a1);
extern void *link_shop_nodes_in_configured_order(void *a0);
extern void configure_shop_object_and_finalize(void *a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);
extern void register_node(void *a0, void *a1);
extern void draw_tinted_node_sprites_scratch(void);
extern void release_null_terminated_entries(u16 **a0);

/* Allocate and initialize a paged item-list node, returning null on failure. */
void *allocate_paged_shop_item_list(s32 parent, s32 selected_index, s32 item_count, s32 page_index, s32 last_page, s32 item_base,
    s32 display_mode)
{
    S_800B3D50_node *node = allocate_flagged_object_node(0);
    S_800B3D50_sub *sub;

    if (node != 0) {
        sub = &node->sub;
        if (copy_records_through_end(sub, 0x1F) != 0) {
            node->field_0xC = (u8 *)node + 0xDC;
            sub->result = link_shop_nodes_in_configured_order(sub->input);
            configure_shop_object_and_finalize(sub, parent, selected_index, item_count, page_index, last_page, item_base, display_mode);
            register_node(node, (void *)draw_tinted_node_sprites_scratch);
            return node;
        }
        release_null_terminated_entries((u16 **)((u8 *)node + 0xF0));
        node->flags |= 0x8000;
        node = 0;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    return node;
}
