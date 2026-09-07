#include "common.h"

/* Copies the global D_8002E5D8 struct (4 words) into each entry's target
 * sub-struct, for `arg1` entries pointed to by the pointer-to-pointer array
 * `arg0`. Each entry is a node whose field at offset 4 is a pointer to the
 * destination struct. */
/* Struct for the global D_8002E5D8: a 16-byte record copied field-by-field
   into each entry's target sub-struct. */
typedef struct S_8002E5D8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} S_8002E5D8;

extern S_8002E5D8 D_8002E5D8;

/* Entry type: arg0 points to an array of pointers to these nodes.
   unk4 is a pointer to a 16-byte record that gets overwritten with
   the contents of D_8002E5D8. */
typedef struct S_8004CC38_Node {
    void *unk0;
    S_8002E5D8 *unk4;
} S_8004CC38_Node;

void func_8004CC38(S_8004CC38_Node **arg0, s32 arg1) {
    s32 i;

    i = 0;
    if (arg1 > 0) {
        do {
            (*arg0)->unk4->unk0 = D_8002E5D8.unk0;
            (*arg0)->unk4->unk4 = D_8002E5D8.unk4;
            (*arg0)->unk4->unk8 = D_8002E5D8.unk8;
            i += 1;
            (*arg0)->unk4->unkC = D_8002E5D8.unkC;
            arg0 += 1;
        } while (i < arg1);
    }
}
