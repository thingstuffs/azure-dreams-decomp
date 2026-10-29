#include "common.h"
#include "town/player/object_initialization_g00546.h"
#include "m2c_compat.h"
#include "town/player.h"

#include "town/player/object/entity_record_fields.h"                     /* extern */

typedef struct S_80098B70_0 {
    u8 pad_00[0x4];
    void (*unk_04)();
} S_80098B70_0;   /* arg0 in bind_default_data_and_clear_record */

/* Sets the object's data pointer and forwards the argument to clear_entity_record_fields. */
void bind_default_data_and_clear_record(S_80098B70_0 *object, s32 forwarded_arg) {
    object->unk_04 = &target_action_update_address;
    clear_entity_record_fields((struct EntityRec *)(forwarded_arg));
}
