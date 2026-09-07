#include "common.h"

typedef struct Node { s32 unk0; void *data; void *anchor; s32 unkC; } Node;
extern s32 D_8002E5D8[4];

void func_800B1B70(void *arg0)
{
    s32 i;
    s32 data_offset;
    s32 node_offset;
    s32 first;
    void *anchor;
    s32 *src;
    s32 *row;
    Node **slot;
    Node *node;

    i = 0;
    anchor = (u8 *)arg0 + 0x20;
    do {
        src = D_8002E5D8;
        slot = (Node **)((u8 *)arg0 + i * 4);
        node_offset = 0x58 + i * 0x10;
        data_offset = 0x98 + i * 0x10;
        row = (s32 *)((u8 *)arg0 + i * 0x10);
        node = (Node *)((u8 *)arg0 + node_offset);
        slot[0x12] = node;
        node->data = (u8 *)arg0 + data_offset;
        slot[0x12]->anchor = (first = D_8002E5D8[0], anchor);
        row[0x26] = first;
        row[0x27] = src[1];
        row[0x28] = src[2];
        row[0x29] = src[3];
        i++;
    } while (i < 4);
}
