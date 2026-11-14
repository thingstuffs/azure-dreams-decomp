#include "town/player/position_handlers.h"
#include "common.h"
#include "town/player/object_initialization_g00546.h"
#include "m2c_compat.h"
#include "town/player.h"
#include "town/player/object.h"

#include "town/player/object/entity_record_fields.h"                     /* extern */

typedef struct S_80098B70_0 {
    u8 pad_00[0x4];
    void (*unk_04)();
} S_80098B70_0;   /* arg0 in bind_default_data_and_clear_record */

/* Sets the object's data pointer and forwards the argument to clear_object_velocity. */
void bind_default_data_and_clear_record(S_80098B70_0 *object, ObjectPosition *forwarded_arg) {
    object->unk_04 = tick_countdown_and_initialize_target;
    clear_object_velocity((forwarded_arg));
}
