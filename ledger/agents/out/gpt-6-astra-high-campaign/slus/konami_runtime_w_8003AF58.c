#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003AF58_0 {
    u8 pad_00[0x14];
    union { s32 s; void * u; } unk_14;   /* accessed as both */
} S_8003AF58_0;   /* var_a0 in func_8003AF58 */

typedef struct S_8003AF58_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8003AF58_1;   /* arg1 in func_8003AF58 */


/* Appends a node to the end of the linked list. */
void func_8003AF58(void *list_head, S_8003AF58_1 *new_node) {
    S_8003AF58_0 *tail;

    tail = list_head;
    if (tail->unk_14.s != 0) {
        do {
            tail = tail->unk_14.u;
        } while (tail->unk_14.s != 0);
    }
    tail->unk_14.u = new_node;
    new_node->unk_14 = 0;
}
