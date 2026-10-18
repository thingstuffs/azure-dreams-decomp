#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void clear_entity_record_fields();                      /* extern */
extern M2C_UNK D_80097F9C;

typedef struct S_80098B30_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_80098B30_0;   /* arg0 in bind_handler_and_initialize_entity */


/* Assign the state table, initialize the record, and set its secondary value to -0x40000. */
void bind_handler_and_initialize_entity(S_80098B30_0 *state, EntityRec *record) {
    state->unk_04 = &D_80097F9C;
    clear_entity_record_fields(record);
    record->flags14 = 0xFFFC0000;
}
