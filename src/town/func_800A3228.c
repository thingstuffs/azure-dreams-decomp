#include "common.h"

typedef struct Node {
    struct Node *next;
    u8 pad_04[0xC];
    s32 field_10;
    u8 pad_14[0xA];
    volatile u16 flags;
} Node;

typedef struct {
    Node *head;
    s32 pad[2];
} ListHead;

typedef struct {
    u8 pad_00[0x48];
    s32 field_48;
} NodeData;

extern ListHead D_80081498;
extern s32 D_800A0708;

/* Finds the first node with the required key and value whose 0x400 flag is clear. */
void *func_800A0988(s32 requested_value)
{
    Node *node;
    Node *next_node;
    s32 node_key;
    s32 required_node_key;
    NodeData *node_data;
    void *result;

    node = D_80081498.head;
    if (node == 0) {
        goto not_found;
    }
    required_node_key = (s32)&D_800A0708;
loop:
    node_key = node->field_10;
    next_node = node->next;
    if (node_key >= 0) {
        goto cont;
    }
    if (node->flags & 0x400) {
        goto cont;
    }
    node_data = (NodeData *)((u8 *)node + 0x20);
    if ((node_key == required_node_key) && (node_data->field_48 == requested_value)) {
        result = node;
        goto done;
    }
cont:
    node = next_node;
    if (node != 0) {
        goto loop;
    }
not_found:
    result = 0;
done:
    return result;
}
