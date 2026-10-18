#include "common.h"
#include "m2c_compat.h"

void process_object_data_by_mode();                      /* extern */
void process_handled_entry_types();                         /* extern */
s32 invalidate_cached_state_and_queue_read();                      /* extern */

typedef struct S_800B6C30_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s16 unk_08;
    u8 pad_0A[0x8E];
    s32 unk_98;
} S_800B6C30_0;

/* Updates the embedded object state and runs its associated helpers. */
void change_monster_status_display_target(s32 objectAddress, s32 field04Value, s16 field08Value) {
    S_800B6C30_0 *objectState;

    if (objectAddress != 0) {
        objectState = objectAddress + 0x20;
        process_handled_entry_types(objectState->unk_98);
        objectState->unk_08 = field08Value;
        objectState->unk_04 = field04Value;
        process_object_data_by_mode(objectState);
        invalidate_cached_state_and_queue_read(objectState);
    }
}
