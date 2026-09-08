#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_8008F134_1 {
    u8 pad_00[0x4];
    void ** unk_04;
} S_8008F134_1;   /* temp_v1 in func_8008F134 */

/* Unlink a linked node and clear its neighbor pointers. */
void func_8008F134(Rec_func_80094268_arg0 *node) {
    S_8008F134_1 *prev_node;

    prev_node = node->unk_00.as_pv;
    if (prev_node != NULL) {
        prev_node->unk_04 = (void **) node->unk_04.as_ppv;
        *node->unk_04.as_ppv = node->unk_00.as_pv;
        node->unk_00.as_pv = NULL;
        node->unk_04.as_ppv = NULL;
    }
}
