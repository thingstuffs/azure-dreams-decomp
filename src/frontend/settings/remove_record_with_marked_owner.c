#include "frontend/settings.h"
#include "shared/object_flags.h"

typedef struct MenuOwner {
    u8 pad_00[0x16];
    s16 flags;
} MenuOwner;

typedef struct MenuLinkedRecord {
    MenuOwner *owner;
} MenuLinkedRecord;

/* Remove this record node once its owner is marked for removal. */
void remove_record_with_marked_owner(void *body) {
    MenuLinkedRecord *record = body;
    /* The object-node flag halfword precedes its callback body. */
    u16 *body_words = body;
    if (record->owner->flags & NODE_REMOVE) {
        body_words[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
