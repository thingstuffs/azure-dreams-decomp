#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B683C_arg0.h"

s32 get_monster_status_type_data(s32);                             /* extern */
s32 invalidate_cached_state_and_queue_read(void *);                      /* extern */
extern M2C_UNK D_800B66E8;


/* Initializes the record, resolves its type data, and runs its setup routine. */
void initialize_monster_status_state(Rec_func_800B683C_arg0 *record, s32 context, s16 type_id) {
    record->unk_08 = type_id;
    record->unk_04 = context;
    record->unk_0C = 0;
    record->unk_0E = 0;
    record->unk_00 = &D_800B66E8;
    record->unk_14 = get_monster_status_type_data(record->unk_08);
    invalidate_cached_state_and_queue_read(record);
}
