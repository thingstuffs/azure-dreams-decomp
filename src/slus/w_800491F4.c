#include "common.h"

typedef struct S_800491F4 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    struct S_800491F4 *unkC;
} S_800491F4;

/* Builds a reversed list of indexed nodes until an index reaches the limit and returns its head. */
S_800491F4 *func_800491F4(S_800491F4 **node_table, u8 *indices, s32 index_limit) {
    S_800491F4 *head = 0;

    if (*indices < index_limit) {
        do {
            node_table[*indices]->unkC = head;
            head = node_table[*indices];
            indices++;
        } while (*indices < index_limit);
    }

    return head;
}
