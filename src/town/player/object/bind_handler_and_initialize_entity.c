#include "common.h"
#include "shared/entity.h"

#include "town/player/object/entity_record_fields.h"                      /* extern */
void adjust_object_motion_at_threshold(s32 context, EntityRec *record, s32 action_data);

typedef struct S_80098B30_0 {
    u8 pad_00[0x4];
    s32 * unk_04;
} S_80098B30_0;   /* arg0 in bind_handler_and_initialize_entity */


/* Assign the state table, initialize the record, and set its secondary value to -0x40000. */
void bind_handler_and_initialize_entity(S_80098B30_0 *state, EntityRec *record) {
    state->unk_04 = &adjust_object_motion_at_threshold;
    clear_entity_record_fields(record);
    record->flags14 = 0xFFFC0000;
}
