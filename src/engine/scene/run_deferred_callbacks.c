#include "common.h"

#include "common.h"

typedef struct S_8003AEF8_1 {
    s32 (*unk_00)(s32, s32, s32, s32);
} S_8003AEF8_1;   /* var_v0 in run_deferred_callbacks */


typedef struct S_8003AEF8_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    void * unk_14;
} S_8003AEF8_0;   /* var_v0 in run_deferred_callbacks */


/* Walks the callback list, clearing each next link and invoking each non-null callback. */
void run_deferred_callbacks(void *head) {
    s32 (*callback)(s32, s32, s32, s32);
    void *next_node;
    S_8003AEF8_0 *node;

    node = head;
    if (node != 0) {
        do {
            next_node = node->unk_14;
            callback = ((S_8003AEF8_1 *)node)->unk_00;
            node->unk_14 = 0;
            if (callback != 0) {
                callback(node->unk_04, node->unk_08, node->unk_0C, node->unk_10);
            }
            node = next_node;
        } while (node != 0);
    }
}
