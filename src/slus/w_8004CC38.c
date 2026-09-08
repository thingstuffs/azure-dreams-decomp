#include "common.h"

/* Struct for the global D_8002E5D8: a 16-byte record copied field-by-field
   into each entry's target sub-struct. */
typedef struct S_8002E5D8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} S_8002E5D8;

extern S_8002E5D8 D_8002E5D8;

/* Entry type: nodes points to an array of pointers to these nodes.
   unk4 is a pointer to a 16-byte record that gets overwritten with
   the contents of D_8002E5D8. */
typedef struct S_8004CC38_Node {
    void *unk0;
    S_8002E5D8 *unk4;
} S_8004CC38_Node;

/* Copies D_8002E5D8 into each node's target record. */
void func_8004CC38(S_8004CC38_Node **nodes, s32 node_count) {
    s32 node_index;

    node_index = 0;
    if (node_count > 0) {
        do {
            (*nodes)->unk4->unk0 = D_8002E5D8.unk0;
            (*nodes)->unk4->unk4 = D_8002E5D8.unk4;
            (*nodes)->unk4->unk8 = D_8002E5D8.unk8;
            node_index += 1;
            (*nodes)->unk4->unkC = D_8002E5D8.unkC;
            nodes += 1;
        } while (node_index < node_count);
    }
}
