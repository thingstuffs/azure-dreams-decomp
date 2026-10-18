#include "common.h"
#include "m2c_compat.h"

M2C_UNK restore_actor_stats_from_snapshot();              /* extern */
M2C_UNK build_entity_slot_snapshot();              /* extern */
void reset_person_object_entries();                   /* extern */
extern M2C_UNK D_80100A10;

/* Load a record into the shared buffer, process it, and write it back. */
void load_a_shared_buffer_process_write_back(s32 record_ref) {
    restore_actor_stats_from_snapshot(&D_80100A10, record_ref);
    reset_person_object_entries(&D_80100A10);
    build_entity_slot_snapshot(record_ref, &D_80100A10);
}
