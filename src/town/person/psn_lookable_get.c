#include "common.h"

typedef struct Node Node;

struct Node {
    Node *next;
    u8 pad_04[0x0C];
    s32 kind;
    u8 pad_14[0x0A];
    u16 flags;
    u8 data[0x64];
};

extern struct {
    Node *head;
    s32 pad[2];
} active_node_list_head;
extern u8 message_motion_type_a[];
extern u8 message_motion_type_b[];

extern s32 runtime_is_record_field_set(void *);

/* psn_lookable_get: find the first eligible person node with the requested ID. */
Node *psn_lookable_get(s16 target_id)
{
    Node *node;
    Node *next;
    s32 kind;
    u8 *data;
    u8 *kind_a;
    u8 *kind_b;

    node = active_node_list_head.head;
    if (node != 0) {
        kind_a = message_motion_type_a;
        kind_b = message_motion_type_b;
        do {
            kind = node->kind;
            next = node->next;
            if (kind < 0 && !(node->flags & 0x400)) {
                data = node->data;
                if ((kind == (s32)kind_a || kind == (s32)kind_b) &&
                    *(s32 *)(data + 0x60) == target_id &&
                    runtime_is_record_field_set(data) != 0) {
                    return node;
                }
            }
            node = next;
        } while (node != 0);
    }
    return 0;
}
