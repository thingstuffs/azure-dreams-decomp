#include "common.h"
#include "m2c_compat.h"

void clear_entity_record_fields();                     /* extern */
extern M2C_UNK D_80098078;

typedef struct S_80098B70_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_80098B70_0;   /* arg0 in bind_default_data_and_clear_record */

/* Sets the object's data pointer and forwards the argument to clear_entity_record_fields. */
void bind_default_data_and_clear_record(S_80098B70_0 *object, M2C_UNK forwarded_arg) {
    object->unk_04 = &D_80098078;
    clear_entity_record_fields(forwarded_arg);
}
