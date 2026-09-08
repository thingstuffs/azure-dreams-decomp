#include "common.h"

#include "common.h"

typedef struct S_80081490 {
    struct S_80081490 *next;    /* 0x00 */
    struct S_80081490 **pprev;  /* 0x04 - address of the slot pointing at this node */
    void *field_0x8;            /* 0x08 */
    void *field_0xC;            /* 0x0C */
    u8 pad_0x10[0x1E - 0x10];
    u16 field_0x1E;             /* 0x1E */
    u8 pad_0x20[0x124 - 0x20];
} S_80081490;

typedef struct S_80013714 {
    u16 flags;      /* 0x0 */
    u8 pad[8];      /* keep size > 8 to force %hi/%lo addressing */
} S_80013714;

extern S_80013714 D_80013714;

extern void func_8003DB4C(int *p, int n);
extern void *func_8003FB98(s32 a0, void *a1);

/* Allocates and initializes a node with the requested flags and links it at the list head. */
void *func_8003FD64(s32 flags, S_80081490 **list_head)
{
    S_80081490 *node;
    S_80081490 *free_node;
    u8 *payload_cursor;

    if ((D_80013714.flags & 0x2) && (flags & 0x200)) {
        return 0;
    }

    {
        extern S_80081490 *D_80081490;
        free_node = D_80081490;
    }
    if (free_node != 0) {
        node = free_node;
        {
            extern struct { S_80081490 *head; s32 pad[2]; } D_80081490;
            D_80081490.head = node->next;
        }
        func_8003DB4C((int *)node, 0x49);

        node->next = *list_head;
        *list_head = node;
        node->pprev = list_head;
        if (node->next != 0) {
            node->next->pprev = (S_80081490 **)node;
        }

        node->field_0x1E = (u16)(flags | 0x4000);

        payload_cursor = (u8 *)node + 0x124;
        if (flags & 0x100) {
            payload_cursor = (u8 *)node + 0xF4;
            goto store_buffer;
        }
        if (flags & 0x6) {
            payload_cursor = (u8 *)node + 0x100;
            goto store_buffer;
        }
        if (flags & 0x41) {
            payload_cursor = (u8 *)node + 0x10C;
        store_buffer:
            node->field_0xC = payload_cursor;
        }

        if (flags & 0x157) {
            payload_cursor = payload_cursor - 0x18;
            node->field_0x8 = payload_cursor;
        }

        return node;
    }

    if (flags & 0x200) {
        return 0;
    }
    return func_8003FB98(flags, list_head);
}
