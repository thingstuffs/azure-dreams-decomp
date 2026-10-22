#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AAE98_arg0.h"
#include "records/Rec_func_800AB014_arg0.h"
#include "town/person/person_record_history_g00592.h"

s32 get_person_lookup_step();                          /* extern */
s32 advance_person_lookup_value();                          /* extern */
extern M2C_UNK D_800AB5C0;

typedef struct {
    s16 unk0;
    u16 value;
} LocalEntry;


/* Move the position halfway toward the adjusted target and update the object state. */
void move_person_toward_sample(Rec_func_800AB014_arg0 *object, Rec_func_800AAE98_arg0 *position) {
    LocalEntry target_entries[6];
    void *object_arg;
    s32 offset;
    s16 total_offset;
    u16 target_z;

    load_record_halfwords_3(target_entries, 4);
    offset = get_person_lookup_step(position);
    object_arg = object;
    total_offset = offset;
    offset = advance_person_lookup_value(object_arg);
    target_z = target_entries[2].value;
    total_offset += offset;
    target_entries[2].value = target_z - total_offset;
    position->unk_02 = (s16) ((s32) (position->unk_02 + (s16) target_entries[0].value) / 2);
    position->unk_06 = (s16) ((s32) (position->unk_06 + (s16) target_entries[1].value) / 2);
    position->unk_0A = (s16) ((s32) (position->unk_0A + (s16) target_entries[2].value) / 2);
    copy_person_table_value(object, 4);
    if (object->unk_90 >= 0x64) {
        object->unk_50 = &D_800AB5C0;
        object->unk_72.as_s16 = 0;
        object->unk_6C = 0xA;
    }
}
