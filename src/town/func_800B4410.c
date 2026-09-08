#include "common.h"

typedef struct Node { s32 unk0; void *data; void *anchor; s32 unkC; } Node;
extern s32 D_8002E5D8[4];

/* Initializes four nodes with a shared anchor and default data. */
void func_800B1B70(void *state)
{
    s32 node_index;
    s32 data_offset;
    s32 node_offset;
    s32 first_word;
    void *anchor;
    s32 *default_data;
    s32 *data_row;
    Node **node_slot;
    Node *node;

    node_index = 0;
    anchor = (u8 *)state + 0x20;
    do {
        default_data = D_8002E5D8;
        node_slot = (Node **)((u8 *)state + node_index * 4);
        node_offset = 0x58 + node_index * 0x10;
        data_offset = 0x98 + node_index * 0x10;
        data_row = (s32 *)((u8 *)state + node_index * 0x10);
        node = (Node *)((u8 *)state + node_offset);
        node_slot[0x12] = node;
        node->data = (u8 *)state + data_offset;
        node_slot[0x12]->anchor = (first_word = D_8002E5D8[0], anchor);
        data_row[0x26] = first_word;
        data_row[0x27] = default_data[1];
        data_row[0x28] = default_data[2];
        data_row[0x29] = default_data[3];
        node_index++;
    } while (node_index < 4);
}
