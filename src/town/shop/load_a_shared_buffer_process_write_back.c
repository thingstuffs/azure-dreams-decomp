#include "common.h"
typedef struct S_80041E28_Dst S_80041E28_Dst;
typedef struct S_80041E28_Src S_80041E28_Src;
void restore_actor_stats_from_snapshot(S_80041E28_Dst *dst, S_80041E28_Src *src);              /* extern */
typedef struct S_800422DC_Other S_800422DC_Other;
typedef struct S_800422DC_Self S_800422DC_Self;
void build_entity_slot_snapshot(S_800422DC_Self *snapshot, S_800422DC_Other *source);              /* extern */
void reset_person_object_entries(void *);                   /* extern */
extern s32 D_80100A10;

/* Load a record into the shared buffer, process it, and write it back. */
void load_a_shared_buffer_process_write_back(s32 record_ref) {
    restore_actor_stats_from_snapshot(&D_80100A10, record_ref);
    reset_person_object_entries(&D_80100A10);
    build_entity_slot_snapshot(record_ref, &D_80100A10);
}
