#include "town/player/position_handlers.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "town/player.h"
#include "town/player/position.h"
#include "town/player/object.h"

#include "town/player/object/entity_record_fields.h"                     /* extern */

typedef struct S_80098F10_0 {
    u8 pad_00[0x4];
    void (*unk_04)(void *, ObjectPosition *, SpriteFrameState *);
} S_80098F10_0;   /* arg0 in clear_record_and_set_next_handler */

/* Run object setup and assign its next handler. */
void clear_record_and_set_next_handler(S_80098F10_0 *object, ObjectPosition *setup_arg) {
    clear_object_velocity((setup_arg));
    object->unk_04 = &refresh_object_position_and_initialize;
}
