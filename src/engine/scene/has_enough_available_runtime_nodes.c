#include "common.h"

typedef struct S_80081490 {
    /* 0x00 */ struct S_80081490 *next;
    /* 0x04 */ u8 pad[0x1E - 0x04];
    /* 0x1E */ u16 unk1E;
} S_80081490;

extern S_80081490 *free_node_list_head;
extern S_80081490 *D_80081498;

/* Returns whether free nodes plus active nodes flagged 0x200 reach the limit. */
s32 has_enough_available_runtime_nodes(s32 limit) {
    S_80081490 *node;
    s32 count;

    count = 0;
    node = free_node_list_head;
    while (node != 0) {
        count++;
        if (!(count < limit)) {
            return 1;
        }
        node = node->next;
    }

    node = D_80081498;
    if (node != 0) {
        do {
            if (node->unk1E & 0x200) {
                count++;
                if (!(count < limit)) {
                    return 1;
                }
            }
            node = node->next;
        } while (node != 0);
    }
    return 0;
}
