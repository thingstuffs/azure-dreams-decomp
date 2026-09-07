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

void *func_800A0988(s32 arg0)
{
    Node *node;
    Node *next;
    s32 key;
    s32 wanted_key;
    NodeData *data;
    void *result;

    node = D_80081498.head;
    if (node == 0) {
        goto not_found;
    }
    wanted_key = (s32)&D_800A0708;
loop:
    key = node->field_10;
    next = node->next;
    if (key >= 0) {
        goto cont;
    }
    if (node->flags & 0x400) {
        goto cont;
    }
    data = (NodeData *)((u8 *)node + 0x20);
    if ((key == wanted_key) && (data->field_48 == arg0)) {
        result = node;
        goto done;
    }
cont:
    node = next;
    if (node != 0) {
        goto loop;
    }
not_found:
    result = 0;
done:
    return result;
}

/* MECHANISM: The retail leaf has no frame or saved registers; the head, node,
   next, key, and held global address occupy v1/a2/a1/a3 naturally.
   A typed node+0x20 subobject preserves the staged addiu/lw access. */
