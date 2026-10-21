#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80174CD8.h"


extern Rec_D_80174CD8 *ghosh_boss_node;

/* Returns whether the current record's unk_D2 field is zero. */
s32 is_boss_record_empty(void) {
    return ghosh_boss_node->unk_D2 == 0;
}
