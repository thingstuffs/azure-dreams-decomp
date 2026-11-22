#include "common.h"
#include "m2c_compat.h"
#include "town/scene/secondary_object_list_g00528.h"
#include "town/player.h"
#include "town/scene.h"

/* Updates the record's overlap link using find_overlapping_active_node. */
void update_record_overlap_node(TownMotionListNode *record) {
    record->overlap = find_overlapping_active_node(record);
}
