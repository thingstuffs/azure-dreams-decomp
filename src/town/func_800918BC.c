#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"

s32 prepend_scene_list_node(Rec_D_800CFCB4 *);                                /* extern */


/* Insert a record and initialize its two values and status flags. */
void handle_insert_initialize_two_values_status_flags(Rec_D_800CFCB4 *node, s32 value_08, s32 value_0c) {
    if (prepend_scene_list_node(node) != 0) {
        node->unk_08 = value_08;
        node->unk_0C = value_0c;
        node->unk_15 = 1;
        node->unk_14 = 0;
    }
}
