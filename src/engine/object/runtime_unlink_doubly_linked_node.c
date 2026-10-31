#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "shared/object_links.h"
#include "engine/object.h"

typedef struct S_80035090_1 {
    u8 pad_00[0x4];
    void * unk_04;
    void * unk_08;
} S_80035090_1;   /* arg0 in runtime_unlink_doubly_linked_node */

   /* ((S_80035090_1 *)arg0)->unk_04 in runtime_unlink_doubly_linked_node */

typedef struct S_80035090_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80035090_3;   /* ((S_80035090_1 *)arg0)->unk_08 in runtime_unlink_doubly_linked_node */


typedef struct S_80035090_0 {
    u8 pad_00[0x4];
    void * unk_04;
    void * unk_08;
} S_80035090_0;   /* arg0 in runtime_unlink_doubly_linked_node */


/* Unlink a node from a doubly linked list by connecting its neighbors. */
void runtime_unlink_doubly_linked_node(void *node_data) {
    S_80035090_0 *node = node_data;
    ((ListBacklinkView *)node->unk_04)->unk_08 = node->unk_08;
    ((S_80035090_3 *)node->unk_08)->unk_04 = node->unk_04;
}
