/* cfail-repair: true-space rowbase definition */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_80082E80.h"

#include "town/system/person_idle_dispatch.h"
s32 get_facing_sector();

/* Store the value table, apply the selected value to the target, and clear its status byte. */
void store_value_table_and_reset_target(Rec_func_80094268_arg0 *object, SpriteFrameState *target, s32 *value_table) {
    object->unk_78 = value_table;
    clear_object_status_and_dispatch_target(object, target, object->unk_78[get_facing_sector(object->unk_72.as_s16)], 0);
    target->frame_ticks = 0;
}
