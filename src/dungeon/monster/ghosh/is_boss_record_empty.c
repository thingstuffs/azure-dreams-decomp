#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "m2c_compat.h"
#include "records/Rec_D_80174CD8.h"



/* Returns whether the current record's unk_D2 field is zero. */
s32 is_boss_record_empty(void) {
    void *node_data = ghosh_boss_node;
    Rec_D_80174CD8 *node = node_data;

    return node->unk_D2 == 0;
}
