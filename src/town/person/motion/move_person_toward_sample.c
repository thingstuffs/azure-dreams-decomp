#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AAE98_arg0.h"
#include "town/person/person_record_history_g00592.h"
#include "town/person/lookup_motion.h"
#include "town/person.h"
#include "town/person/motion.h"

/* Move the position halfway toward the adjusted target and update the object state. */
void move_person_toward_sample(TownObjectRecord *object, ObjectPosition *position) {
    Fixed1616 target_entries[6];
    s32 offset;
    s16 total_offset;
    u16 target_z;

    load_position_history_entry(target_entries, 4);
    offset = get_map_cell_step_size(position);
    total_offset = offset;
    offset = advance_person_sine_offset(object);
    target_z = target_entries[2].w.i;
    total_offset += offset;
    target_entries[2].w.i = target_z - total_offset;
    position->x.w.i = (s16) ((s32) (position->x.w.i + target_entries[0].w.i) / 2);
    position->y.w.i = (s16) ((s32) (position->y.w.i + target_entries[1].w.i) / 2);
    position->z.w.i = (s16) ((s32) (position->z.w.i + target_entries[2].w.i) / 2);
    copy_history_entry_heading(object, 4);
    if (object->unk_90 >= 0x64) {
        object->state_callback.as_pm = approach_person_sample;
        object->heading = 0;
        object->timer = 0xA;
    }
}
