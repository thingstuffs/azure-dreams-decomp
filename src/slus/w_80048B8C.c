#include "common.h"

#include "common.h"

typedef struct S_80048B8C_node {
    u8 flags;
    u8 pad1[3];
    u16 val;
    u8 pad6[6];
} S_80048B8C_node;

typedef struct S_80048B8C_entry {
    u8 pad0[2];
    s16 type;
    S_80048B8C_node *node;
} S_80048B8C_entry;

typedef struct S_80048B8C {
    u8 *list;
    s32 index;
    u8 *listEnd;
} S_80048B8C;

/* Mark unprocessed type-2 node sequences and set the low six value bits to 14. */
void func_80048B8C(S_80048B8C *entries) {
    u8 *entry_pos;
    S_80048B8C_node *node;
    S_80048B8C_entry *entry;
    volatile u16 *value_ptr;
    u16 value;
    u32 masked_value;
    signed char value_mask;

    entry_pos = entries->list + (entries->index << 2);
    if (entry_pos < entries->listEnd) {
        entry = (S_80048B8C_entry *)entry_pos;
        value_mask = ~0x3F;
        do {
            if (entry->type == 2) {
                node = entry->node;
                masked_value = node->flags;
                if (!(masked_value & 8)) {
                    node->flags = masked_value | 8;
                    value_ptr = &node->val;
                    do {
                        value = *value_ptr;
                        masked_value = value & value_mask;
                        *value_ptr = masked_value;
                        ASM_KEEP_NV(masked_value);
                        *value_ptr = masked_value + 0xE;
                        value_ptr = (u16 *)((u8 *)value_ptr + 0xC);
                    } while (!((node++)->flags & 0x80));
                }
            }
            entry = (S_80048B8C_entry *)((u8 *)entry + 8);
            entry_pos += 8;
        } while (entry_pos < entries->listEnd);
    }
}
