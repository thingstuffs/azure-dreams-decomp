#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003AEF8_1 {
    M2C_UNK (*unk_00)(s32, s32, s32, s32);
} S_8003AEF8_1;   /* var_v0 in func_8003AEF8 */


typedef struct S_8003AEF8_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    void * unk_14;
} S_8003AEF8_0;   /* var_v0 in func_8003AEF8 */


/* Walks the callback list, clearing each next link and invoking each non-null callback. */
void func_8003AEF8(void *head) {
    M2C_UNK (*callback)(s32, s32, s32, s32);
    void *next_node;
    S_8003AEF8_0 *node;

    node = head;
    if (node != NULL) {
        do {
            next_node = node->unk_14;
            callback = ((S_8003AEF8_1 *)node)->unk_00;
            node->unk_14 = NULL;
            if (callback != NULL) {
                callback(node->unk_04, node->unk_08, node->unk_0C, node->unk_10);
            }
            node = next_node;
        } while (node != NULL);
    }
}
