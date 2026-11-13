#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800FE490.h"
#include "town/player.h"
#include "town/scene.h"

/* Updates the record's unk_10 value using find_overlapping_active_node. */
void update_record_overlap_node(Rec_D_800FE490 *record) {
    record->unk_10 = find_overlapping_active_node(record);
}
