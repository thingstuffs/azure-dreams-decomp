#include "frontend/settings.h"
#include "shared/object_flags.h"

/* Remove this effect node once its owner is marked for removal. */
void remove_effect_with_marked_owner(ColorEffect *body) {
    void *body_address = body;
    /* The object-node flag halfword precedes its callback body. */
    u16 *body_words = body_address;
    if (body->owner->flags & NODE_REMOVE) {
        body_words[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
