#include "frontend/settings.h"
#include "frontend/settings/owner_linked_body.h"
#include "shared/object_flags.h"

typedef struct MenuOwner {
    u8 pad_00[0x16];
    s16 flags;
} MenuOwner;

/* Remove this record node once its owner is marked for removal. */
void remove_record_with_marked_owner(void *body) {
    SettingsOwnerLinkedBody *record = body;
    MenuOwner *owner = record->owner;
    /* The object-node flag halfword precedes its callback body. */
    u16 *body_words = body;
    if (owner->flags & NODE_REMOVE) {
        body_words[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
