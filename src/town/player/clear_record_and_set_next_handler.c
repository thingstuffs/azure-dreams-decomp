#include "common.h"

#include "town/player/object/entity_record_fields.h"                     /* extern */
void refresh_object_position_and_initialize(void *context, void *object, s32 mode);

typedef struct S_80098F10_0 {
    u8 pad_00[0x4];
    void (*unk_04)(void *, void *, s32);
} S_80098F10_0;   /* arg0 in clear_record_and_set_next_handler */

/* Run object setup and assign its next handler. */
void clear_record_and_set_next_handler(S_80098F10_0 *object, s32 setup_arg) {
    clear_entity_record_fields((struct EntityRec *)(setup_arg));
    object->unk_04 = &refresh_object_position_and_initialize;
}
