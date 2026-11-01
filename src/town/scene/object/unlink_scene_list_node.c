#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/scene/object.h"


typedef struct S_8008F134_1 {
    u8 pad_00[0x4];
    void ** unk_04;
} S_8008F134_1;

/* Unlink a linked node and clear its neighbor pointers. */
void unlink_scene_list_node(TownObjectRecord *node) {
    S_8008F134_1 *prev_node;

    prev_node = node->unk_00.as_pv;
    if (prev_node != NULL) {
        prev_node->unk_04 = node->unk_04.as_ppv;
        *node->unk_04.as_ppv = node->unk_00.as_pv;
        node->unk_00.as_pv = NULL;
        node->unk_04.as_ppv = NULL;
    }
}
