#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800FE490.h"
#include "town/player.h"
#include "town/scene.h"

/* Updates the record's unk_10 value using handle_finds_first_eligible_active_node_in_circular_list. */
void update_the_s_field_10_using_callee_8008_fe_90(Rec_D_800FE490 *record) {
    record->unk_10 = handle_finds_first_eligible_active_node_in_circular_list(record);
}
