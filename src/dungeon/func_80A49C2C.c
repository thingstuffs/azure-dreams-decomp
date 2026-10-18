#include "modules/dungeon_resource06_slot0.h"

void reset_record_motion_field_b(Rec_func_800AB538_arg0 *record, void *motion, void *scale, void *render) {
    update_actor_hop_and_shrink(record, motion, scale, render);
    record->unk_B6 = 0;
}
