#include "modules/town_door.h"

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
    if (node != 0) {
        required_node_key = (s32)&func_800A0708;
        do {
            node_key = node->field_10;
            next_node = node->next;
            if (node_key < 0) {
                if (!(node->flags & 0x400)) {
                    node_data = (NodeData *)((u8 *)node + 0x20);
                    if ((node_key == required_node_key) && (node_data->field_48 == requested_value)) {
                        result = node;
                        return result;
                    }
                }
            }
            node = next_node;
        } while (node != 0);
    }
    result = 0;
    return result;
}
